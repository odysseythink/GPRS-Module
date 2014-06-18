/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : systick.c
Author      : ranwei    
Version     : 
Date        : 2014/6/18 15:17:19
Description : 
Others      : 
*************************************************************************/

#define SYSTICK_GLOBAL

#include "systick.h" 

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
void Systick_Init(void)
{
    g_ulSysTick = 0;
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
void Systick_IRQ_Handler(void)
{
    g_ulSysTick++;
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
u32_t OS_Get_SysTimeTick(void)
{
    return g_ulSysTick;     
}


