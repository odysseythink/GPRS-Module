/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : systick.h
Author      : ranwei    
Version     : 
Date        : 2014/6/18 15:17:51
Description : 
Others      : 
*************************************************************************/
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef SYSTICK_GLOBAL
#define SYSTICK_EXT
#else
#define SYSTICK_EXT extern 
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "types.h"

/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/



/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/

/*================================================================*/
/*                      @GLOBAL VARIABLES                         */
/*================================================================*/
SYSTICK_EXT u32_t g_ulSysTick;


/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
void Systick_Init(void);
void Systick_IRQ_Handler(void);
u32_t OS_Get_SysTimeTick(void);



#ifdef __cplusplus
}
#endif

#endif 
