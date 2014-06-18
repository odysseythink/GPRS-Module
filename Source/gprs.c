/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : gprs.c
Author      : ranwei    
Version     : 
Date        : 2014/6/16 19:17:58
Description : 
Others      : 
*************************************************************************/

#define GPRS_GLOBAL

#include "gprs.h"

/*
  @global viarables
*/
static const unsigned char * GSM_FinalResponsesError[] = {
    "ERROR",
    "+CMS ERROR:",
    "+CME ERROR:",
    "NO ANSWER",
    "NO DIALTONE",
    "+CPIN: SIM ERROR",
    "+CREG: 0,2",
    "BUSY",
    "+CME ERROR: unknown",
    "+CME ERROR: operation not allowed"    
};


/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
void GPRS_Init(void)
{
    memset(g_gprsCB,0,sizeof(g_gprsCB));
    strcpy(g_gprsCB.aucConnectType,"\"UDP\"");
    strcpy(g_gprsCB.aucIpAddr,"\"255.255.255.255\"");
    strcpy(g_gprsCB.aucServerPort,"65535");
    g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
    g_gprsCB.signal.ucBer = 0;
    g_gprsCB.signal.ucRssi = 0;
    g_gprsCB.timeoutNode.ulTimeout = 0;
    g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;
    g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
    g_gprsCB.tcpPang.ucTCPPangFlag = FALSE;
    g_gprsCB.tcpPang.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;
    g_gprsCB.tcpPang.timeoutNode.ulTimeout = 0;
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
u8_t Get_NWK_Info(u8_t *pucData,u8_t ucLen)
{
    u8_t len;
    u8_t temp;
    u8_t aucBuff[ucLen];
    u8_t *p = aucBuff;
    u8_t *q = pucData;
    u8_t ucCommaCNT = 0;
    u8_t aucCommaAddr[5];

    memset(aucCommaAddr,0,sizeof(aucCommaAddr));
    memset(aucBuff,0,sizeof(aucBuff));
    
    if(NULL == pucData)
    {
        return ERRO_CFGINFO_NULL;
    }
    while(*q != NULL)
    {
        if(*q == 0x20)
        {
            
        }
        else
        {
            *p = *q;
            if(*p = ',')
            {
                aucCommaAddr[ucCommaCNT] = len
                ucCommaCNT++;
            }
            p++;
            len++;
        }
        q++;
    }
    p = aucBuff;
    if(2 == ucCommaCNT)
    {
        if(0 == aucCommaAddr[0])
        {
            
        }
        else if(5 == aucCommaAddr[0])
        {
            if(strncpy(p,"\"TCP\"",5))
            {
                strcpy(g_gprsCB.aucConnectType,"\"TCP\"");
            }
            else if(strncpy(p,"\"UDP\"",5))
            {
                strcpy(g_gprsCB.aucConnectType,"\"UDP\"");
            }
            else
            {
                return ERRO_CFGINFO_CECT_TYPE;
            }
        }
        else
        {
            return ERRO_CFGINFO_CECT_TYPE;
        }
        
        if(('\"' == aucBuff[aucCommaAddr[0]+1])&&('\"' == aucBuff[aucCommaAddr[1] - 1))
        {
            if(IS_IP_Addr(&aucBuff[aucCommaAddr[0]+2],aucCommaAddr[1]-aucCommaAddr[0]-1-2)
            {
                strncpy(g_gprsCB.aucIpAddr,&aucBuff[aucCommaAddr[0]+1],aucCommaAddr[1]-aucCommaAddr[0]-1);
            }
            else
            {
                return ERRO_CFGINFO_IP;
            }
        }
        else
        {
            return ERRO_CFGINFO_IP;
        }
        
        if((ucLen - aucCommaAddr[1] - 1) > 5)
        {
            return ERRO_CFGINFO_PORT;
        }
        else
        {
            strncpy(g_gprsCB.aucServerPort,&aucBuff[aucCommaAddr[1]+1],ucLen - aucCommaAddr[1] - 1);
        }
        Save_NETEnv();
        return ERRO_CFGINFO_NONE;
    }
    else /* error command format */
    {
        return ERRO_CFGINFO_CMD_FORMAT;
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
u8_t IS_IP_Addr(u8_t *pucData,u8_t ucLen)
{
    u8_t aucCommaAddr[3];
    u8_t ucCommaCNT = 0;
    u8_t *p = pucData;
    u8_t i = 0;

    if(NULL == pucData)
    {
        return FALSE;
    }
    while(*p != NULL)
    {
        if(*p == '.')
        {
            if(ucCommaCNT >= 3) /* '.' appear more than three times, not a IP address */
            {
                return FALSE;
            }
            else
            {
                aucCommaAddr[ucCommaCNT] = i;
                ucCommaCNT++;
            }
        }
        i++;
        
    }
    if(ucCommaCNT != 3)
    {
        return FALSE;
    }

    if(0 == aucCommaAddr[0])
    {
        return FALSE;
    }
    if(((aucCommaAddr[1]-aucCommaAddr[0]) == 1)||((aucCommaAddr[2]-aucCommaAddr[1]) == 1))
    {
        return FALSE;
    }
    
    return TRUE;
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
void Save_NETEnv(void)
{
    Flash_Save_NetConnectType(FLASH_CONNECT_TYPE_ADDR,g_gprsCB.aucConnectType,strlen(g_gprsCB.aucConnectType));
    Flash_Save_IPAddr(FLASH_IP_ADDR,g_gprsCB.aucIpAddr,strlen(g_gprsCB.aucIpAddr));    
    Flash_Save_ServerPort(FLASH_CONNECT_TYPE_ADDR,g_gprsCB.aucServerPort,strlen(g_gprsCB.aucServerPort));
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
void GPRS_Module_Reset(void)
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
void GPRS_Connect_NWK(void)
{
    u8_t aucBuff[GSM_BUFF_SIZE];
    u8_t *p = aucBuff;
    u8_t *q;
    u8_t ucLen;
    u8_t ucResult;
    usLen = 0;

    if(g_gprsCB.timeoutNode.ucTimeoutFlag != EN_TIMEOUT_INIT)
    {
        if(OS_Get_SysTimeTick() >= g_gprsCB.timeoutNode.ulTimeout)
        {
            g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_OK;
        }
    }
    
    if(EN_STAGE_AT == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_AT,(unsigned char *)0,&usLen);
                GSM_AddReq(GSMDRV_REQUEST_AT,NULL,&usLen);
                GSM_SetTimeout(usLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;
                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                        if(ucResult != EN_RESULT_BUTT)
                        {
                            g_gprsCB.ucConnectingStage = EN_STAGE_CPIN;
                            break;
                        }
                    }
                }            
                break;  
             default:
                break;
        }  
    }
    else if(EN_STAGE_CPIN == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_GET_SIM_STATUS,(unsigned char *)0,&ucLen);
                GSM_AddReq(GSMDRV_REQUEST_GET_SIM_STATUS,NULL,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;
                
                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                        if(ucResult != EN_RESULT_BUTT)
                        {
                            
                            break;
                        }
                    }
                    if(EN_RESULT_WAIT_SIM_STATUS_OK == ucResult)
                    {
                        g_gprsCB.ucConnectingStage = EN_STAGE_CSQ;
                    }
                    else
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                        g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                    }
                }     
                break;  
             default:
                break;
        }        
    }
    else if(EN_STAGE_CSQ == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_GET_SQR,(unsigned char *)0,&ucLen);
                GSM_AddReq(GSMDRV_REQUEST_GET_SQR,NULL,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;

                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                        if(ucResult != EN_RESULT_BUTT)
                        {
                            break;
                        }
                    }
                    if(EN_RESULT_CSQ_VALUE == ucResult)
                    {
                        g_gprsCB.ucConnectingStage = EN_STAGE_CREG;
                    }                    
                    else
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                        g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                    }
                }     
                break;  
             default:
                break;
        }
    }   
    else if(EN_STAGE_CREG == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_REGISTRATION_STATE,(unsigned char *)0,&ucLen);
                GSM_AddReq(GSMDRV_REQUEST_REGISTRATION_STATE,NULL,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;

                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                        if(ucResult != EN_RESULT_BUTT)
                        {
                            break;
                        }
                    }

                    if(EN_RESULT_CSQ_VALUE == ucResult)
                    {
                        g_gprsCB.ucConnectingStage = EN_STAGE_CGATT;
                    }                    
                    else
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                        g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                    }
                }     
                break;  
             default:
                break;
        }
    }  
    else if(EN_STAGE_CGATT == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_GET_GRRS_STATE,(unsigned char *)0,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;

                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                        if(ucResult != EN_RESULT_BUTT)
                        {
                            break;
                        }
                    }

                    if(EN_RESULT_CSQ_VALUE == ucResult)
                    {
                        g_gprsCB.ucConnectingStage = EN_STAGE_CSTT;
                    }                    
                    else
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                        g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                    }
                }     
                break;  
             default:
                break;
        }
    } 
    else if(EN_STAGE_CSTT == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_SET_APN,"\"CMNET\"",&ucLen);
                GSM_AddReq(GSMDRV_REQUEST_GET_GRRS_STATE,NULL,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;

                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                    }

                    if(ucResult != EN_RESULT_BUTT)
                    {
                        g_gprsCB.ucConnectingStage = EN_STAGE_CIICR;
                    }
                    else
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                        g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                    }
                }     
                break;  
             default:
                break;
        }
    }   
    else if(EN_STAGE_CIICR == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_SET_MOBILE_ENV,(unsigned char *)0,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;

                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                    }


                    if(ucResult != EN_RESULT_BUTT)
                    {
                        g_gprsCB.ucConnectingStage = EN_STAGE_CIFSR;
                    }
                    else
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                        g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                    }
                }     
                break;  
             default:
                break;
        }
    }
    else if(EN_STAGE_CIFSR == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                GSM_AddReq(GSMDRV_REQUEST_GET_IP,(unsigned char *)0,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;

                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    g_gprsCB.ucConnectingStage = EN_STAGE_CIPSTART;
                } 
                else
                {
                    g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                    g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                }
                break;  
             default:
                break;
        }
    } 
    else if(EN_STAGE_CIPSTART == g_gprsCB.ucConnectingStage)
    {
        switch(g_gprsCB.timeoutNode.ucTimeoutFlag)
        {
            case EN_TIMEOUT_INIT:
                memset(aucBuff,0,sizeof(aucBuff));
                strcpy(aucBuff,g_gprsCB.aucConnectType);
                aucBuff[strlen(aucBuff)] = ',';
                strcat(aucBuff,g_gprsCB.aucIpAddr);
                aucBuff[strlen(aucBuff)] = ',';
                strcat(aucBuff,g_gprsCB.aucServerPort);
                ucLen = strlen(aucBuff);
                GSM_AddReq(GSMDRV_REQUEST_CREATE_NET_CONNECT,aucBuff,&ucLen);
                GSM_SetTimeout(ucLen);
                memset(aucBuff,0,sizeof(aucBuff));
                break;
            case EN_TIMEOUT_NO:
                break;
            case EN_TIMEOUT_OK:
                g_gprsCB.timeoutNode.ulTimeout = 0;
                g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;

                if(SUCCESS == Read_Buff(BUFF_NWK,aucBuff,&ucLen))
                {
                    for(p = aucBuff;p != NULL;q = strsep((char **)&p,"\r\n"))
                    {
                        while(strstripstart(&q,'\r'));
                        while(strstripstart(&q,'\n'));
                        GSM_Reponse_Proc((unsigned char *)q,&ucResult);
                        if(ucResult != EN_RESULT_BUTT)
                        {
                            g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                            g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                        }
                    }
                    g_gprsCB.ucConnectingStage = EN_STAGE_CIPSTART;
                } 
                
                if(EN_RESULT_CONNECT == ucResult)
                {
                    g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                    if(0 == strcmp(g_gprsCB.aucConnectType,"TCP"))
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_TCP;
                        g_gprsCB.tcpPang.ucTCPPangFlag = TRUE;
                    }
                    else
                    {
                        g_gprsCB.ucNWKStatus = GPRS_NWK_UDP;
                    }
                }                    
                else
                {
                    g_gprsCB.ucNWKStatus = GPRS_NWK_NO;
                    g_gprsCB.ucConnectingStage = EN_STAGE_INIT;
                }

                break;  
             default:
                break;
        }
    }    
    else
    {
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
void GPRS_TCP_Pang(void)
{
    u8_t aucBuff[4];
    aucBuff[0] = 0xAA;
    aucBuff[1] = 0x55;
    aucBuff[2] = 0xBB;
    aucBuff[3] = 0x66;
    switch(g_gprsCB.tcpPang.timeoutNode.ucTimeoutFlag)
    {
        case EN_TIMEOUT_INIT:
            break;
        case EN_TIMEOUT_NO:
            break;
        case EN_TIMEOUT_OK:
            g_gprsCB.timeoutNode.ulTimeout = 0;
            g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_INIT;
    
            UART_Send_MultiString(ROUTER_NWK,aucBuff,4)
            break;  
         default:
            break;
    }
}


#define __GSM_INTERFACE__
/*******************************************************************************************
@fn     : GSM_AddReq

@brief  : 添加命令

@param  : 

@return : EN_GSM_RET_SUC  -- 添加成功
          EN_GSM_RET_FAIL -- 添加失败
********************************************************************************************/
unsigned char GSM_AddReq(unsigned char ucReq,unsigned char *pData,unsigned short *pusLen)
{
    unsigned char aucCmd[GSM_BUFF_SIZE];
    unsigned short usCmdLen = 0;

    memset(aucCmd, 0, sizeof(aucCmd));

    if(IS_REQ_Invalid(ucReq))
    {
        GSM_Prompt(__FILE__,__LINE__,"REQ is invalid");
        return FALSE;
    }
    
    GSM_ConstructCmd(ucReq, pData, aucCmd);

    /* 加上\r\n */
    usCmdLen = strlen((char *)aucCmd);
    aucCmd[usCmdLen] = '\r';
    aucCmd[usCmdLen+1] = '\n';  
    usCmdLen = usCmdLen + 2;
    *pusLen = usCmdLen;
    GSM_SEND_MSG(aucCmd,usCmdLen);
    
    return SUCCESS;
}

/*******************************************************************************************
@fn     : IS_REQ_Valid

@brief  : 校验ucReq是否在范围内

@param  : 
  input : ucReq -- 传入要校验的ucReq

@return : 0 -- 参数在范围内
          1 -- 参数不在范围内
********************************************************************************************/
unsigned char IS_REQ_Invalid(const unsigned char ucReq)
{
    if((ucReq < GSMDRV_REQUEST_GET_SIM_STATUS)||(ucReq > GSMDRV_REQUEST_SEND_SMS_DATA))
    {
        return 1;
    }
    return 0;
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
void GSM_Prompt(char *pucFileName,long ulLineNum,char * pcFormat)
{
#if GSM_DEBUG > 0 
    char aucBuff[GSM_PROMPT_BUFF_LEN];
    unsigned char ucLen;
    char *p;
    ucLen = strlen(pucFileName);
    memset(aucBuff,0,sizeof(aucBuff));
    strcpy(aucBuff,pucFileName);
    
    aucBuff[ucLen++] = ':';
    p = &aucBuff[ucLen];
    ucLen += ltos((unsigned long)ulLineNum,p);
    aucBuff[ucLen++] = ':';
    strcat(aucBuff,pcFormat);
    ucLen = strlen(aucBuff);
    aucBuff[ucLen] = '\r';
    UartTX_Send_MultiByte(UART_1,(unsigned char *)aucBuff,strlen(aucBuff));
#endif
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return : 0 -- 
          1 -- 
********************************************************************************************/
unsigned char GSM_ConstructCmd(unsigned char ucReq,void *pData,  unsigned char *pucCommand)
{
    unsigned char *pucCmd;
    pucCmd = pucCommand;

    switch (ucReq)
    {
        case GSMDRV_REQUEST_AT:
            sprintf((char *)pucCmd, "AT");
            break;        
        case GSMDRV_REQUEST_GET_SIM_STATUS:
            sprintf((char *)pucCmd, "AT+CPIN?");
            break;
        case GSMDRV_REQUEST_GET_CURRENT_CALLS:
            sprintf((char *)pucCmd, "AT+CLCC");
            break;
        case GSMDRV_REQUEST_HANGUP:
            sprintf((char *)pucCmd, "ATH");
            break;
        case GSMDRV_REQUEST_REGISTRATION_STATE:
            sprintf((char *)pucCmd, "AT+CREG?");
            break;
        case GSMDRV_REQUEST_GET_GRRS_STATE:
            sprintf((char *)pucCmd, "AT+CGATT?");
            break;
        case GSMDRV_REQUEST_SET_GRRS_STATE:
            sprintf((char *)pucCmd, "AT+CGATT=%s",(unsigned char *)pData);
            break;        
        case GSMDRV_REQUEST_GET_APN:
            sprintf((char *)pucCmd, "AT+CSTT?");
            break;
        case GSMDRV_REQUEST_SET_APN:
            sprintf((char *)pucCmd, "AT+CSTT=%s",(unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_SET_MOBILE_ENV:
            sprintf((char *)pucCmd, "AT+CIICR");
            break;
        case GSMDRV_REQUEST_GET_IP:
            sprintf((char *)pucCmd, "AT+CIFSR");
            break;
        case GSMDRV_REQUEST_CREATE_NET_CONNECT:
            sprintf((char *)pucCmd, "AT+CIPSTART=%s",(unsigned char *)pData);
            break; 
        case GSMDRV_REQUEST_SEND_START:
            sprintf((char *)pucCmd, "AT+CIPSEND");
            break;
        
        case GSMDRV_REQUEST_SEND_NET_PACKET:
            sprintf((char *)pucCmd, "%s" , (unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_CLOSE_NET_CONNECT:
            sprintf((char *)pucCmd, "AT+CIPCLOSE");
            break;
        case GSMDRV_REQUEST_CLOSE_MOBILE_ENV:
            sprintf((char *)pucCmd, "AT+CIPSHUT");
            break; 
        case GSMDRV_REQUEST_NET_REGISTER_AND_SIM_REPORT:
            sprintf((char *)pucCmd, "AT+CREG=1;+CSMINS=1");
            break;
        case GSMDRV_REQUEST_ANSWER:
            sprintf((char *)pucCmd, "ATA");
            break;
        case GSMDRV_REQUEST_DIAL:
            sprintf((char *)pucCmd, "ATD%s;", (unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_GET_ECHO:
            sprintf((char *)pucCmd, "AT+ECHO=%s", (unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_SET_CLIP:
            sprintf((char *)pucCmd, "AT+CLIP=1");
            break;
        case GSMDRV_REQUEST_GET_SQR:
            sprintf((char *)pucCmd, "AT+CSQ");
            break;
        case GSMDRV_REQUEST_SET_CMIC:
            sprintf((char *)pucCmd, "AT+CMIC=%s", (unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_SET_CLVL:
            sprintf((char *)pucCmd, "AT+CLVL=%s", (unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_SET_SIDET:
            sprintf((char *)pucCmd, "AT+SIDET=%s", (unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_SET_AUDIO_CHANGE:
            sprintf((char *)pucCmd, "AT+CHFA=%s;+CHFA?", (unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_GET_SOFTWARE_VER:
            sprintf((char *)pucCmd, "AT+CGMR");
            break;
        case GSMDRV_REQUEST_GET_IFC:
            sprintf((char *)pucCmd, "AT+IFC?");
            break;
        case GSMDRV_REQUEST_SET_IFC:
            sprintf((char *)pucCmd, "AT+IFC=%s",(unsigned char *)pData);
            break;
        case GSMDRV_REQUEST_SET_CFUN:
            sprintf((char *)pucCmd, "AT+CFUN?");
            break;
        case GSMDRV_REQUEST_GET_CFUN:
            sprintf((char *)pucCmd, "AT+CFUN?");
            break;    
        case GSMDRV_REQUEST_GET_CSCLK:
            sprintf((char *)pucCmd, "AT+CSCLK?");
            break;

        case GSMDRV_REQUEST_OPERATOR:
            sprintf((char *)pucCmd, "AT+COPS=0");
            break;

        case GSMDRV_REQUEST_SET_SMS_FORMAT:
            sprintf((char *)pucCmd, "AT+CMGF=%s" , (unsigned char *)pData);
            break;

        case GSMDRV_REQUEST_DELETE_ALL_SMS_ON_SIM:
            sprintf((char *)pucCmd, "AT+CMGDA=%s" ,(unsigned char *)pData);
            break;

        case GSMDRV_REQUEST_DELETE_SMS_ON_SIM:
            sprintf((char *)pucCmd, "AT+CMGD=%s" , (unsigned char *)pData);
            break;

        /*获取短信中心号码*/
        case GSMDRV_REQUEST_GET_SMSCA:
            sprintf((char *)pucCmd, "AT+CSCA?");
            break;

        case GSMDRV_REQUEST_SEND_SMS:
            sprintf((char *)pucCmd, "AT+CMGS=%s" , (unsigned char *)pData);
            break;

        case GSMDRV_REQUEST_RECV_SMS:
            sprintf((char *)pucCmd, "AT+CMGR=%s" , (unsigned char *)pData);
            break;

        case GSMDRV_REQUEST_SEND_SMS_DATA:
            sprintf((char *)pucCmd, "%s" , (unsigned char *)pData);
            break;

        /* 建立TCP连接 */
        default:
            break;
        
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
void GSM_SetTimeout(u32_t usTimeout)
{
    u32_t usTemp ;
    usTemp = OS_Get_SysTimeTick();
    usTemp += 200;
    g_gprsCB.timeoutNode.ulTimeout = usTemp;
    g_gprsCB.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_NO;
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
void GSM_SetTCPTimeout(u32_t usTimeout)
{
    u32_t usTemp ;
    usTemp = OS_Get_SysTimeTick();
    usTemp += usTimeout;
    g_gprsCB.tcpPang.timeoutNode.ulTimeout = usTemp;
    g_gprsCB.tcpPang.timeoutNode.ucTimeoutFlag = EN_TIMEOUT_NO;
}


/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
unsigned char GSM_Reponse_Proc(unsigned char *s,unsigned char *pucResult)
{
    unsigned char err;
    unsigned char *line = s;
    unsigned long ulTemp0,ulTemp1;
    
    if(NULL == s)
    {
        GSM_Prompt(__FILE__,__LINE__,"s is NULL pointer");
        *pucResult = EN_RESULT_BUTT;
        return 1;
    }
    if(NULL == pucResult)
    {
        GSM_Prompt(__FILE__,__LINE__,"pucResult is NULL pointer");
        *pucResult = EN_RESULT_BUTT;
        return 1;
    }
    
    if (IsStrPrefix((char *)s, "OK"))
    {
        *pucResult = EN_RESULT_OK;
        return 0;
    }
    else if(IsStrPrefix((char *)s, "CONNECT OK"))
    {
       *pucResult = EN_RESULT_CONNECT;
       return 0;

    }
    else if (GSM_FinalResponseError(s))
    {
        *pucResult = EN_RESULT_ERROR;
        return 0;
    }
    else if((IsStrPrefix((char *)s, "+CSMINS: 1,0"))
          ||(IsStrPrefix((char *)s, "+CSMINS: 0,0"))
          ||(IsStrPrefix((char *)s, "+CPIN: NOT INSERTED")))
    {
        *pucResult = EN_RESULT_SIM_NOT_INSERTED;
        return 0;
    }
    else if(IsStrPrefix((char *)s, "NO CARRIER"))
    {
        *pucResult = EN_RESULT_NO_CARRIER;
        return 0;
    }
    else if(IsStrPrefix((char *)s, "+CPIN: READY") )
    {
        *pucResult = EN_RESULT_WAIT_SIM_STATUS_OK;
        return 0;
    }
    else if(IsStrPrefix((char *)s, "+CREG:") )
    {
        if(( 0 == strcmp ((char *)s, "+CREG: 0,1"))||( 0 == strcmp ((char *)s, "+CREG: 1,1")))
        {
            *pucResult = EN_RESULT_WAIT_SIM_REG_OK;
            return 0;
        }
        else if( 0 == strcmp((char *)s, "+CREG: 3"))
        {
            /*网络注册被拒接*/
            *pucResult = EN_RESULT_WAIT_NETWORK_UNREGISTER;
            GSM_Prompt(__FILE__,__LINE__,"The Network registration denied!");
            return 1;
        }
        else if( 0 == strcmp ((char *)s, "+CREG: 0"))
        {
            /*网络未注册,MT没有寻找一个新的运营商去注册*/
            *pucResult = EN_RESULT_WAIT_NETWORK_UNREGISTER;
            GSM_Prompt(__FILE__,__LINE__,"The Network isn't registered,MT isn't currently searching a new operator to register to!");
            return 1;
        }
        else if( 0 == strcmp ((char *)s, "+CREG: 2"))
        {
            /*网络未注册,但是MT在寻找一个新的运营商去注册*/
            *pucResult = EN_RESULT_WAIT_NETWORK_UNREGISTER;
            GSM_Prompt(__FILE__,__LINE__,"The Network isn't registered,But MT is currently searching a new operator to register to!");
            return 1;
        }
        else if( 0 == strcmp ((char *)s, "+CREG: 4"))
        {
            /*未知网络*/
            *pucResult = EN_RESULT_WAIT_NETWORK_UNKOWN;
            GSM_Prompt(__FILE__,__LINE__,"The Unknown Network!");
            return 1;
        }
        else if( 0 == strcmp ((char *)s, "+CREG: 5"))
        {
            /*网络已经注册,处于漫游*/
            *pucResult = EN_RESULT_WAIT_NETWORK_ROAM;
            GSM_Prompt(__FILE__,__LINE__,"The Network is registered,and roaming!");
            return 1;
        }
        return 1;
    }
    else if( IsStrPrefix((char *)s, "+CGATT: 1") )
    {
        *pucResult = EN_RESULT_WAIT_MMS_SET_ATTACH_GPRS_OK;
        return 0;
    }
    else if( IsStrPrefix((char *)s, "+CSQ: ") )
    {
        err = GSM_at_tok_start(&line);
        if(1 == err)
        {
            *pucResult = EN_RESULT_BUTT;
            return 1;
        }

        /*获取rssi*/
        err = GSM_at_tok_nextint(&line, &ulTemp0);
        if(1 == err)
        {
            GSM_Prompt(__FILE__,__LINE__,"Get GSM_at_tok_nextint Fail!");
            *pucResult = EN_RESULT_BUTT;
            return 1;
        }
        signal.ucRssi = (unsigned char) ulTemp0;

        /*获取ber*/
        err = GSM_at_tok_nextint(&line, &ulTemp1);
        if(1 == err)
        {
            GSM_Prompt(__FILE__,__LINE__,"Get GSM_at_tok_nextint Fail!");
            *pucResult = EN_RESULT_BUTT;
            return 1;
        }
        GSM_Prompt(__FILE__,__LINE__,"Signal Quality");
        signal.ucBer = (unsigned char) ulTemp1;
        *pucResult = EN_RESULT_CSQ_VALUE;
        return 0;

    }
    *pucResult = EN_RESULT_BUTT;
    return 1;
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
unsigned char GSM_FinalResponseError(const unsigned char *s)
{
    int i;

    if(NULL == s)
    {
        GSM_Prompt(__FILE__,__LINE__,"GSM GSM_FinalResponseError  NULL point!");
        return 0;
    }

    for (i = 0 ; i < GSMDRV_NUM_ELEMS(GSM_FinalResponsesError) ; i++)
    {
        if (IsStrPrefix((char *)s, (char *)GSM_FinalResponsesError[i]))
        {
            return 1;
        }
    }

    return 0;
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
unsigned char GSM_at_tok_start(unsigned char **p_cur)
{
    char *psym = NULL;

    if (*p_cur == NULL)
    {
        return 1;
    }

    psym = strchr((char *)*p_cur, ':');

    if (psym == NULL)
    {
        return 1;
    }

    (*p_cur) = (unsigned char *)psym + 1;

    return 0;
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
unsigned char GSM_at_tok_nextint(unsigned char **p_cur, unsigned long *p_out)
{
    unsigned char *ret;

    if ((*p_cur == NULL)||(p_out == NULL))
    {
        GSM_Prompt(__FILE__,__LINE__,"GSM_at_tok_nextint NULL point!");
        return 1;
    }

    ret = GSM_NextTok(p_cur);

    if (ret == NULL)
    {
        return 1;
    }
    else
    {
        unsigned long l;
        unsigned char *end;

        l = strtol((char *)ret, (char **)&end, 10);

        *p_out = (unsigned long)l;

        if (end == ret)
        {
            return 1;
        }
        return 0;
    }
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
unsigned char * GSM_NextTok(unsigned char **p_cur)
{
    char *ret = NULL;

    GSM_SkipWhiteSpace(p_cur);

    if (*p_cur == NULL)
    {
        ret = NULL;
    }
    else if (**p_cur == '"')
    {
        (*p_cur)++;
        ret = strsep((char **)p_cur, "\"");
        GSM_SkipNextComma(p_cur);
    }
    else
    {
        ret = strsep((char **)p_cur, ",");
    }

    return (unsigned char *)ret;
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
void GSM_SkipWhiteSpace(unsigned char **p_cur)
{
    if (*p_cur == NULL)
        return;

    while (**p_cur != '\0' && isspace(**p_cur))
    {
        (*p_cur)++;
    }
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :           
********************************************************************************************/
void GSM_SkipNextComma(unsigned char **p_cur)
{
    if (*p_cur == NULL)
        return;

    while (**p_cur != '\0' && **p_cur != ',')
    {
        (*p_cur)++;
    }

    if (**p_cur == ',')
    {
        (*p_cur)++;
    }
}







