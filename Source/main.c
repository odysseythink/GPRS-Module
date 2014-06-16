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

#define EVENT_FREE      0x0000 /* free */
#define EVENT_LOCALDATA 0x0001 /* 数据通道数据 */
#define EVENT_NWKDATA   0x0002
#define EVENT_PANG      0x0004 /* 专为TCP心跳设置的时间 */

#define FREE_TASK_EVENT(a) {tasksEvent[a] &= EVENT_FREE;}
#define SET_TASK_EVENT(a,event) {tasksEvent[a] |= event;}

#define BUFF_LOCAL 1
#define BUFF_NWK   2


typedef unsigned short (* pTaskHandlerFn)(unsigned char ucTaskID,unsigned short usEvent);

const pTaskHandlerFn tasksArr[TASK_CNT]={
    Task_Heart,
    Task_DataRouter1,/* 接收到要发送的网络数据，将数据发给GPRS模块，这个任务负责监视这一条通道 */
    Task_DataRouter2,/* 接收到服务器发过来的数据，将数据转发给外部功能模块，这个任务负责监视这一条通道 */
    Task_TCPPang,/* 如果建立的是TCP连接，维持TCP的心跳 */
    Task_DataRouter3/* 收到外部功能模块请求GPS数据的请求，将GPS数据转发给外部功能模块，这个数据通道负责监视这一条通道 */
};

unsigned short tasksEvent[TASK_CNT]; 

unsigned char g_ucTaskHeartID;
unsigned char g_ucTaskDataRouter1ID;
unsigned char g_ucTaskDataRouter2ID;
unsigned char g_ucTaskTCPPangID;
unsigned char g_ucTaskDataRouter3ID;


static void Module_Init(void);
static void System_Run(void);
static void System_Start(void);
static void Task_Init(void);
static unsigned short Task_Heart(unsigned char ucTaskID,unsigned short usEvent);
static unsigned short Task_DataRouter1(unsigned char ucTaskID,unsigned short usEvent);
static unsigned short Task_DataRouter2(unsigned char ucTaskID,unsigned short usEvent);
static unsigned short Task_TCPPang(unsigned char ucTaskID,unsigned short usEvent);
static unsigned short Task_DataRouter3(unsigned char ucTaskID,unsigned short usEvent);
static void Task_Heart_Init(unsigned char taskID);
static void Task_DataRouter1_Init(unsigned char taskID);
static void Task_DataRouter2_Init(unsigned char taskID);
static void Task_TCPPang_Init(unsigned char taskID);
static void Task_DataRouter3_Init(unsigned char taskID);
static unsigned char Read_Buff(unsigned char buffType,unsigned char *pucStartAddr,unsigned char *pucLen);






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
    Task_Init();
    GPRS_Init();    
    GPS_Init();
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
    unsigned char i = 0;
    
    Task_Heart_Init(i++);
    Task_DataRouter1_Init(i++);
    Task_DataRouter2_Init(i++);
    Task_TCPPang_Init(i++);
    Task_DataRouter3_Init(i++);    

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
    unsigned char i;
    unsigned short temp;
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
static unsigned short Task_Heart(unsigned char ucTaskID,unsigned short usEvent)
{
    unsigned char ucStartAddr = 0;
    switch(usEvent)
    {
        case EVENT_LOCALDATA:
            Read_Buff(BUFF_LOCAL,);
            break;
        case EVENT_NWKDATA:
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
static unsigned short Task_DataRouter1(unsigned char ucTaskID,unsigned short usEvent)
{
    unsigned short res = 
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
static unsigned short Task_DataRouter2(unsigned char ucTaskID,unsigned short usEvent)
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
static unsigned short Task_TCPPang(unsigned char ucTaskID,unsigned short usEvent)
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
static unsigned short Task_DataRouter3(unsigned char ucTaskID,unsigned short usEvent)
{
}

#define __TASK_INIT__
static void Task_Heart_Init(unsigned char taskID)
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
static void Task_DataRouter1_Init(unsigned char taskID)
{
    g_ucTaskDataRouter1ID = taskID;
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
static void Task_DataRouter2_Init(unsigned char taskID)
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
static void Task_TCPPang_Init(unsigned char taskID)
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
static void Task_DataRouter3_Init(unsigned char taskID)
{
    g_ucTaskDataRouter3ID = taskID;
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
static unsigned char Read_Buff(unsigned char buffType,unsigned char *pucStartAddr,unsigned char *pucLen)
{
    if((buffType != BUFF_LOCAL)||(buffType != BUFF_NWK))
    {
        return 1;
    }
    if((NULL == pucStartAddr)||(NULL == pucLen))
    {
        return 1;
    }
    return 0;
}



