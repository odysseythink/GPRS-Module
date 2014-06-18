/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : flash.h
Author      : ranwei    
Version     : 
Date        : 2014/6/18 15:04:59
Description : 
Others      : 
*************************************************************************/
#ifndef __FLASH_H__
#define __FLASH_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef FLASH_GLOBAL
#define FLASH_EXT
#else 
#define FLASH_EXT extern 
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "types.h"

/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/
#define FLASH_NET_ADDR

/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/

/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
void Flash_Save(u32_t addr,u8_t *pucData,u16_t ucLen);


#ifdef __cplusplus
}
#endif

#endif 
