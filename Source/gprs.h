/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : gprs.h
Author      : ranwei    
Version     : 
Date        : 2014/6/16 19:18:04
Description : 
Others      : 
*************************************************************************/
#ifndef __GPRS_H__
#define __GPRS_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef GPRS_GLOBAL
#define GPRS_EXT
#else
#define GPRS_EXT extern 
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "types.h"
#include "includes.h"

/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/
#define GSM_BUFF_SIZE 256


#define ERRO_CFGINFO_NONE       0
#define ERRO_CFGINFO_NULL       1
#define ERRO_CFGINFO_CECT_TYPE  2
#define ERRO_CFGINFO_CMD_FORMAT 3
#define ERRO_CFGINFO_IP         4
#define ERRO_CFGINFO_PORT       5

#define EN_TIMEOUT_INIT  0
#define EN_TIMEOUT_NO    1
#define EN_TIMEOUT_OK    2

/* 请求 */
enum{
    GSMDRV_REQUEST_AT = 1,                      /* AT */
    GSMDRV_REQUEST_GET_SIM_STATUS ,             /* AT+CPIN? */
    GSMDRV_REQUEST_GET_CURRENT_CALLS,           /* AT+CLCC */ 
    GSMDRV_REQUEST_HANGUP,                      /* ATH */
    GSMDRV_REQUEST_REGISTRATION_STATE,          /* AT+CREG? */
    GSMDRV_REQUEST_GET_GRRS_STATE,              /* AT+CGATT? */
    GSMDRV_REQUEST_SET_GRRS_STATE,              /* AT+CGATT=<state> */
    GSMDRV_REQUEST_SET_MOBILE_ENV,              /* AT+CIICR */
    GSMDRV_REQUEST_GET_IP,                      /* AT+CIFSR */
    GSMDRV_REQUEST_CREATE_NET_CONNECT,          /* AT+CIPSTART="TCP","120.237.116.3",4700 */
    GSMDRV_REQUEST_SEND_START,                  /* AT+CIPSEND */
    GSMDRV_REQUEST_SEND_NET_PACKET,             /* send net packet */
    GSMDRV_REQUEST_CLOSE_NET_CONNECT,           /* close TCP or UDP connect */
    GSMDRV_REQUEST_CLOSE_MOBILE_ENV,            /* AT+CIPSHUT,关闭移动场景 */         
    GSMDRV_REQUEST_GET_APN,                     /* AT+CSTT? */
    GSMDRV_REQUEST_SET_APN,                     /* AT+CSTT=<apn>,<username>,<password> */          
    GSMDRV_REQUEST_NET_REGISTER_AND_SIM_REPORT, /* AT+CREG=1;+CSMINS=1 */
    GSMDRV_REQUEST_ANSWER,                      /* ATA */
    GSMDRV_REQUEST_DIAL,                        /* ATD<n>[<mgsm][;] */
    GSMDRV_REQUEST_GET_ECHO,                    /* AT+ECHO=%s */
    GSMDRV_REQUEST_GET_SQR,                     /* AT+CSQ? */
    GSMDRV_REQUEST_SET_CMIC,                    /* AT+CMIC=<channel>,<gainlevel> */        
    GSMDRV_REQUEST_SET_CLVL,                    /* AT+CLVL=<level> */        
    GSMDRV_REQUEST_SET_SIDET,                   /* AT+SIDET=<channel>,<gainlevel> */       
    GSMDRV_REQUEST_SET_AUDIO_CHANGE,            /* AT+CHFA=<n> */
    GSMDRV_REQUEST_GET_SOFTWARE_VER,            /* AT+CGMR */      
    GSMDRV_REQUEST_GET_IFC,                     /* AT+IFC? */         
    GSMDRV_REQUEST_SET_IFC,                     /* AT+IFC=[<dce_by_dte>[,<dte_by_dce>]] */         
    GSMDRV_REQUEST_SET_CFUN,                    /* AT+CFUN? */
    GSMDRV_REQUEST_GET_CFUN,                    /* AT+CFUN? */
    GSMDRV_REQUEST_GET_CSCLK,                   /* AT+CSCLK? */       
    GSMDRV_REQUEST_SET_CLIP,                    /* AT+CLIP=1 */
    GSMDRV_REQUEST_OPERATOR,                    /* AT+COPS=0 */
    GSMDRV_REQUEST_SET_SMS_FORMAT,              /* AT+CMGF=[<mode>],短信 */  
    GSMDRV_REQUEST_DELETE_ALL_SMS_ON_SIM,       /* AT+CMGDA=<type> */
    GSMDRV_REQUEST_DELETE_SMS_ON_SIM,           /* AT+CMGD=<index>[,<delflag>] */
    GSMDRV_REQUEST_GET_SMSCA,                   /* AT+CSCA? */ 
    GSMDRV_REQUEST_SEND_SMS,                    /* AT+CMGS=%s */
    GSMDRV_REQUEST_RECV_SMS,                    /* AT+CMGR=%s */        
    GSMDRV_REQUEST_SEND_SMS_DATA,               /* send SMS data */   
    GSMDRV_REQUEST_BUTT
};

enum{
    EN_RESULT_OK = 1,
    EN_RESULT_CONNECT,
    EN_RESULT_ERROR,
    EN_RESULT_SIM_NOT_INSERTED,
    EN_RESULT_NO_CARRIER,
    EN_RESULT_WAIT_SIM_STATUS_OK,
    EN_RESULT_WAIT_SIM_REG_OK,
    EN_RESULT_WAIT_NETWORK_UNREGISTER,
    EN_RESULT_WAIT_NETWORK_UNKOWN,
    EN_RESULT_WAIT_NETWORK_ROAM,
    EN_RESULT_WAIT_MMS_SET_ATTACH_GPRS_OK,
    EN_RESULT_CSQ_VALUE,
    EN_RESULT_BUTT
};


/* 向GSM接口发送数据*/
#define GSM_SEND_MSG(str,len) 

#define GSMDRV_NUM_ELEMS(x) (sizeof(x)/sizeof(x[0]))


/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/

/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/
typedef enum{
    EN_STAGE_AT = 1,
    EN_STAGE_CPIN,
    EN_STAGE_CSQ,
    EN_STAGE_CREG,
    EN_STAGE_CGATT,
    EN_STAGE_CSTT,
    EN_STAGE_CIICR,
    EN_STAGE_CIFSR,
    EN_STAGE_CIPSTART
}NWK_Connect_Stage_t;

typedef struct{
    u32_t ulTimeout;
    u8_t  ucTimeoutFlag;
}GSM_TimeoutNode_t;

typedef struct{
    u8_t ucRssi;
    u8_t ucBer;
}Signal_t;

typedef struct{
    u8_t ucNWKStatus;
    GSM_TimeoutNode_t timeoutNode;
    Signal_t signal;
}GPRS_CB_t;


/*================================================================*/
/*                      @GLOBAL VARIABLES                         */
/*================================================================*/

GPRS_EXT u8_t g_aucNETEnv[3][20];
GPRS_EXT NWK_Connect_Stage_t g_ConnectStage;
GPRS_EXT GSM_TimeoutNode_t g_TimeoutNode;
GPRS_EXT Signal_t signal;
GPRS_EXT GPRS_CB_t g_gprsCB;

/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
void GPRS_Init(void);
u8_t IS_IP_Addr(u8_t *pucData,u8_t ucLen);
u8_t Get_NWK_Info(u8_t *pucData,u8_t ucLen);
void Save_NETEnv(void);
void GPRS_Module_Reset(void);
void GPRS_Connect_NWK(void);




#ifdef __cplusplus
}
#endif

#endif 
