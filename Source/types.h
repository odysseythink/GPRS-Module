/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : types.h
Author      : ranwei    
Version     : 
Date        : 2014/6/17 9:54:14
Description : 
Others      : 
*************************************************************************/
#ifndef __TYPES_H__
#define __TYPES_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef TYPES_GLOBAL
#define TYPES_EXT
#else
#define TYPES_EXT extern
#endif


/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/
#define TRUE    1
#define FALSE   0

#define SUCCESS 1
#define FAILURE 0

/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/
typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned long u32_t;

typedef unsigned char bool;



#ifdef __cplusplus
}
#endif

#endif 
