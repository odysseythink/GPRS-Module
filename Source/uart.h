/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : uart.h
Author      : ranwei    
Version     : 
Date        : 2014/6/17 11:39:40
Description : 
Others      : 
*************************************************************************/
#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef UART_GLOBAL
#define UART_EXT
#else
#define UART_EXT extern
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "types.h"


/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/
#define UART_1  1
#define UART_2  2
#define UART_3  3

/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/

/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
void UART_Init(void);
u8_t UART_Send_MultiString(u8_t ucUARTType,u8_t *pucData,u8_t ucLen);
u8_t UART_Send_OneByte(u8_t ucUARTType,u8_t ucCh);



#ifdef __cplusplus
}
#endif

#endif 
