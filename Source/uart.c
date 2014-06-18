/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : uart.c
Author      : ranwei    
Version     : 
Date        : 2014/6/17 11:39:33
Description : 
Others      : 
*************************************************************************/

#define UART_GLOBAL

#include "uart.h"

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
void UART_Init(void)
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
u8_t UART_Send_MultiString(u8_t ucUARTType,u8_t *pucData,u8_t ucLen)
{
    if(UART_1 == ucUARTType)
    {
       return ; 
    }
    if(UART_2 == ucUARTType)
    {
        return;
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
u8_t UART_Send_OneByte(u8_t ucUARTType,u8_t ucCh)
{
    if(UART_1 == ucUARTType)
    {
       return TRUE; 
    }
    if(UART_2 == ucUARTType)
    {
        return TRUE;
    }    
    return FALSE;
}




