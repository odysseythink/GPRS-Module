/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : assert.h
Author      : ranwei    
Version     : 
Date        : 2014/6/18 10:16:43
Description : 
Others      : 
*************************************************************************/
#ifndef __ASSERT_H__
#define __ASSERT_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef ASSERT_GLOBAL
#define ASSERT_EXT
#else
#define ASSERT_EXT extern 
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "types.h"
#include "string.h"

/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/
#define SYS_DEBUG 0 /* not debug */

#define PROMPT_BUFF_SIZE 100 



/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/

/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
extern void Sys_Prompt(u32_t ulLine,u8_t *pucFileName,u8_t format,...);

extern void MyPrint(u8_t *pucData);


#ifdef __cplusplus
}
#endif

#endif 
