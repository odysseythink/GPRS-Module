/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : netframe.c
Author      : ranwei    
Version     : 
Date        : 2014/6/17 10:02:23
Description : 
Others      : 
*************************************************************************/

#define NETFRAME_GLOBAL

#include "netframe.h"

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
void NetFrame_Init(void)
{
    *ucFrameStructure[0] = 0xAA;
    *(ucFrameStructure[0]+1) = 0x55;
    *ucFrameStructure[1] = 0xBB;
    *(ucFrameStructure[1]+1) = 0x66;   
    g_ucNETFrameFilter = FALSE;/* initialize the  g_ucNETFrameFilter*/
    g_ucFrameLen = 0; /* initialize the lenth of frame */
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
u8_t NETFrame_Filter(u8_t **ppucData,u8_t ucLen)
{
    u8_t ucHeadLen = strlen(ucFrameStructure[0]);
    u8_t ucTailLen = strlen(ucFrameStructure[1]);


        
    return ERRO_FRAME_NONE;
}


