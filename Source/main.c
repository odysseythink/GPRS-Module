/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : main.c
Author      : ranwei    
Version     : 
Date        : 2014/6/16 19:17:33
Description : 
Others      : 
*************************************************************************/

#define MAIN_GLOBAL

#include "includes.h"

#define TASK_CNT 5

#define EVENT_FREE                0x0000 /* free */
#define EVENT_LOCALDATA           0x0001 /* 数据通道数据 */
#define EVENT_NWKDATA             0x0002
#define EVENT_PANG                0x0004 /* 专为TCP心跳设置的时间 */
#define EVENT_GPS_ACTIVE          0x0008
#define EVENT_GPRS_CFG            0x0010
#define EVENT_GPRS_NWK_CONNECTING 0x0020

#define DATA_GPS_REQUEST     1
#define DATA_GPRS_CFG        2   
#define DATA_Frame_DESCRIBLE 3
#define DATA_NET_FRAME       4
#define DATA_UNKOWN          5

#define SEND_STAT_OK            0
#define SEND_STAT_UNKOWN_ROUTER 1
#define SEND_STAT_DATA_NULL     2
#define SEND_STAT_DATA_LEN_ZERO 3

#define ROUTER_LOCAL    1
#define ROUTER_NWK      2

#define FREE_TASK_EVENT(a) {tasksEvent[a] &= EVENT_FREE;}
#define SET_TASK_EVENT(a,event) {tasksEvent[a] |= event;}
#define GET_TASK_EVENT(a) tasksEvent[a]
#define CLR_TASK_EVENT(a,event) {tasksEvent[a] &= (~event);}

#define BUFF_LOCAL 1
#define BUFF_NWK   2

#define TEMP_BUFF_SIZE 100


typedef u16_t (* pTaskHandlerFn)(u8_t ucTaskID,u16_t usEvent);

const pTaskHandlerFn tasksArr[TASK_CNT]={
    Task_Heart,
    Task_GPRS,/* 接收到要发送的网络数据，将数据发给GPRS模块，这个任务负责监视这一条通道 */
    Task_DataRouter2,/* 接收到服务器发过来的数据，将数据转发给外部功能模块，这个任务负责监视这一条通道 */
    Task_TCPPang,/* 如果建立的是TCP连接，维持TCP的心跳 */
    Task_GPS/* 收到外部功能模块请求GPS数据的请求，将GPS数据转发给外部功能模块，这个数据通道负责监视这一条通道 */
};

u16_t tasksEvent[TASK_CNT]; 

u8_t g_ucTaskHeartID;
u8_t g_ucTaskGPRSID;
u8_t g_ucTaskDataRouter2ID;
u8_t g_ucTaskTCPPangID;
u8_t g_ucTaskGPSID;


static void Module_Init(void);
static void System_Run(void);
static void System_Start(void);
static void Task_Init(void);
static u16_t Task_Heart(u8_t ucTaskID,u16_t usEvent);
static u16_t Task_GPRS(u8_t ucTaskID,u16_t usEvent);
static u16_t Task_DataRouter2(u8_t ucTaskID,u16_t usEvent);
static u16_t Task_TCPPang(u8_t ucTaskID,u16_t usEvent);
static u16_t Task_GPS(u8_t ucTaskID,u16_t usEvent);
static void Task_Heart_Init(u8_t taskID);
static void Task_GPRS_Init(u8_t taskID);
static void Task_DataRouter2_Init(u8_t taskID);
static void Task_TCPPang_Init(u8_t taskID);
static void Task_GPS_Init(u8_t taskID);
static u8_t Read_Buff(u8_t buffType,u8_t *pucStartAddr,u8_t *pucLen);
static u8_t Data_Filter(u8_t **ppucData,u8_t ucLen);
static u8_t Send_Data(u8_t ucRouterType,u8_t *pucData);



#define __FUNC__
/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
void main(void)
{
    Module_Init();
    System_Run();
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void Module_Init(void)
{
    EVL_Board_Init();
    UART_Init();
    Task_Init();
    BuffPool_Init();
    GPRS_Init();    
    GPS_Init();
    NetFrame_Init();
    Systick_Init();
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void Task_Init(void)
{
    u8_t i = 0;
    
    Task_Heart_Init(i++);
    Task_GPRS_Init(i++);
    Task_DataRouter2_Init(i++);
    Task_TCPPang_Init(i++);
    Task_GPS_Init(i++);    

    for(i=0;i<TASK_CNT;i++)
    {
        FREE_TASK_EVENT(a);
    }
}


/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void System_Start(void)
{
    while(1)
    {
        System_Run();
    }
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void System_Run(void)
{
    u8_t i;
    u16_t temp;
    for(i=0;i<TASK_CNT;i++)
    {
        temp = tasksEvent[i];
        if(temp)
        {
            break;
        }
    }
    tasksArr[i](i,temp);
}


/*
** @tasks
*/
#define __TASKS__
/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static u16_t Task_Heart(u8_t ucTaskID,u16_t usEvent)
{
    u8_t ucStartAddr = 0;
    u8_t aucTempBuff[TEMP_BUFF_SIZE];
    u8_t ucLen;
    u8_t flag;
    switch(usEvent)
    {
        case EVENT_LOCALDATA:
            Read_Buff(BUFF_LOCAL,aucTempBuff,&ucLen);
            flag = Data_Filter(aucTempBuff,ucLen);
            break;
        case EVENT_NWKDATA:
            break;
        default:
            break;
    }
    switch(flag)
    {
        case DATA_GPS_REQUEST:
            SET_TASK_EVENT(g_ucTaskGPSID,EVENT_GPS_ACTIVE);
            break;
        case DATA_GPRS_CFG:
            SET_TASK_EVENT(g_ucTaskGPRSID,EVENT_GPRS_CFG);
            break;
        case DATA_Frame_DESCRIBLE:
            break;
        case DATA_NET_FRAME:
            break;
        default:
            break;
    }
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static u8_t Data_Filter(u8_t **ppucData,u8_t ucLen)
{
    u8_t *p;
    if(0 == strcmp(*ppucData,"gps.request"))
    {
        return DATA_GPS_REQUEST;
    }
    if(0 == strncmp(*ppucData,"gprs-cfg.request:",17))
    {
        p = (*ppucData)+17;
        Get_NWK_Info(p,ucLen-17);
        return DATA_GPRS_CFG;
    }
    if(0 == strncmp(*ppucData,"netdata-frame.describe:",22))
    {
        return DATA_Frame_DESCRIBLE;
    }
    if(TRUE == g_ucNETFrameFilter)
    {
        if(ERRO_FRAME_NONE == NETFrame_Filter(ppucData,ucLen))
        {
            return DATA_NET_FRAME;
        }
        else
        {
            return DATA_UNKOWN;
        }
    }
    return DATA_NET_FRAME;
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static u16_t Task_GRRS(u8_t ucTaskID,u16_t usEvent)
{
    if(usEvent & EVENT_GPRS_CFG)
    {
        GPRS_Module_Reset();
        GPRS_Connect_NWK();
        CLR_TASK_EVENT(g_ucTaskGPRSID,EVENT_GPRS_CFG);
        SET_TASK_EVENT(g_ucTaskGPRSID,EVENT_GPRS_NWK_CONNECTING);
    }
    
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static u16_t Task_DataRouter2(u8_t ucTaskID,u16_t usEvent)
{
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static u16_t Task_TCPPang(u8_t ucTaskID,u16_t usEvent)
{
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static u16_t Task_GPS(u8_t ucTaskID,u16_t usEvent)
{
    if(usEvent & EVENT_GPS_ACTIVE)
    {
        GPS_Info_t gpsInfo;
        Get_GPS_Info(&gpsInfo);
        Send_Data(ROUTER_LOCAL,(u8_t *)&gpsInfo,sizeof(gpsInfo));
        CLR_TASK_EVENT(g_ucTaskGPSID,usEvent)
    }
    return GET_TASK_EVENT(g_ucTaskGPSID);
}

#define __TASK_INIT__
/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void Task_Heart_Init(u8_t taskID)
{
    g_ucTaskHeartID = taskID;
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void Task_GPRS_Init(u8_t taskID)
{
    g_ucTaskGPRSID = taskID;
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void Task_DataRouter2_Init(u8_t taskID)
{
    g_ucTaskDataRouter2ID = taskID;
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void Task_TCPPang_Init(u8_t taskID)
{
    g_ucTaskTCPPangID = taskID;
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static void Task_GPS_Init(u8_t taskID)
{
    g_ucTaskGPSID = taskID;
}

#define __SURPORT_FUNC__
/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**   input : buffType -- type of buff,BUFF_LOCAL or BUFF_NWK
**
**   output: pucStartAddr -- 数据开始地址
**           pucLen       -- 数据长度
**          
** @return : 成功返回0，失败返回1
*********************************************************************/
static u8_t Read_Buff(u8_t buffType,u8_t *pucStartAddr,u8_t *pucLen)
{
    u8_t len;
    if((buffType != BUFF_LOCAL)||(buffType != BUFF_NWK))
    {
        return FAILURE;
    }
    if((NULL == pucStartAddr)||(NULL == pucLen))
    {
        return FAILURE;
    }
    if(BUFF_LOCAL == buffType)
    {
        len = pLOCALBuffHdr->hdr.len
        if(0 == len)
        {
            return FAILURE;
        }
        else
        {
            *pucLen = len;
            memcpy(pucStartAddr,pLOCALBuffHdr+1,len);
            memset(pLOCALBuffHdr+1,0,len);
            pLOCALBuffHdr->hdr.len = 0;
        }
    }
    else
    {
        len = pNWKBuffHdr->hdr.len
        if(0 == len)
        {
            return FAILURE;
        }
        else
        {
            *pucLen = len;
            memcpy(pucStartAddr,pNWKBuffHdr+1,len);
            memset(pNWKBuffHdr+1,0,len);
            pNWKBuffHdr->hdr.len = 0;
        }        
    }
    return SUCCESS;
}

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
static u8_t Send_Data(u8_t ucRouterType,u8_t *pucData,u8_t ucLen)
{
    if((ucRouterType != ROUTER_LOCAL)&&(ucRouterType != ROUTER_NWK))
    {
        return SEND_STAT_UNKOWN_ROUTER;
    }
    if(NULL == pucData)
    {
        return SEND_STAT_DATA_NULL;
    }
    if(0 == ucLen)
    {
        return SEND_STAT_DATA_LEN_ZERO;
    }
    if(ROUTER_LOCAL == ucRouterType)
    {
        UART_Send_MultiString(UART_1,pucData,ucLen);
    }
    else
    {
        UART_Send_MultiString(UART_2,pucData,ucLen);
    }
    return SEND_STAT_OK;
}

