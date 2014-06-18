/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : assert.c
Author      : ranwei    
Version     : 
Date        : 2014/6/18 10:16:37
Description : 
Others      : 
*************************************************************************/

#define ASSERT_GLOBAL

#include "assert.h"

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
void Sys_Prompt(u32_t ulLine,u8_t *pucFileName,u8_t format,...)
{
    u8_t ucLen;
    u8_t aucBuff[PROMPT_BUFF_SIZE];
    sprintf(aucBuff,"%s [%d]:",pucFileName,ulLine);
    ucLen = strlen(aucBuff);
    sprintf(aucBuff+ucLen,format,...);
    MyPrint(aucBuff);
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
void MyPrint(u8_t *pucData)
{
#if SYS_DEBUG

#endif
}


