/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : netframe.h
Author      : ranwei    
Version     : 
Date        : 2014/6/17 10:02:54
Description : 
Others      : 
*************************************************************************/
#ifndef __NETFRAME_H__
#define __NETFRAME_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef NETFRAME_GLOBAL
#define NETFRAME_EXT
#else
#define NETFRAME_EXT extern 
#endif 

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "types.h"

/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/
#define ERRO_FRAME_NONE 0
#define ERRO_FRAME_HEAD 1
#define ERRO_FRAME_TAIL 2
#define ERRO_FRAME_LEN  3

/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/

/*================================================================*/
/*                      @GLOBAL VARIABLES                         */
/*================================================================*/
NETFRAME_EXT u8_t* ucFrameStructure[2];
NETFRAME_EXT bool g_ucNETFrameFilter; /* 是否进行网络帧过滤 */
NETFRAME_EXT u8_t g_ucFrameLen;/* the length of frame */


/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
void NetFrame_Init(void);
u8_t NETFrame_Filter(u8_t **ppucData,u8_t ucLen);


#ifdef __cplusplus
}
#endif

#endif 
