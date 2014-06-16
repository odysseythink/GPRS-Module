/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : includes.h
Author      : ranwei    
Version     : 
Date        : 2014/6/16 19:47:11
Description : 
Others      : 
*************************************************************************/
#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef INCLUDES_GLOBAL
#define INCLUDES_EXT
#else
#define INCLUDES_EXT extern
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "evl_board.h"
#include "gprs.h"
#include "gps.h"
#include "it.h"
#include "buff.h"

#ifdef __cplusplus
}
#endif

#endif 
