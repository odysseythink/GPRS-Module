/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : gprs.h
Author      : ranwei    
Version     : 
Date        : 2014/6/16 19:18:04
Description : 
Others      : 
*************************************************************************/
#ifndef __GPRS_H__
#define __GPRS_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef GPRS_GLOBAL
#define GPRS_EXT
#else
#define GPRS_EXT extern 
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/

/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/

/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/

/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
void GPRS_Init(void);


#ifdef __cplusplus
}
#endif

#endif 
