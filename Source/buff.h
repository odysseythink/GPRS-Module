/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : buff.h
Author      : ranwei    
Version     : 
Date        : 2014/6/12 14:42:40
Description : 
Others      : 
*************************************************************************/
#ifndef __BUFF_H__
#define __BUFF_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef BUFF_GLOBAL
    #define BUFF_EXT
#else
    #define BUFF_EXT extern
#endif

/*================================================================*/
/*                          @INCLUDES                             */
/*================================================================*/
#include "app_cfg.h"

/*================================================================*/
/*                           @MACROS                              */
/*================================================================*/
#define BuffHdr_SZ sizeof(BuffHdr_t)
#define BUFFPOOL_SZ (BuffHdr_SZ * BUFFPOOL_SIZE)
#define BUFF_USED    1
#define BUFF_NOTUSED 0

/*================================================================*/
/*                         @TYPEDEFS                              */
/*================================================================*/
typedef struct {
  // The 15 LSB's of 'val' indicate the total item size, including the header, in 8-bit bytes.
  unsigned len : 7;
  // The 1 MSB of 'val' is used as a boolean to indicate in-use or freed.
  unsigned inUse : 1;
} BuffHdrHdr_t;

typedef union{
    unsigned char val;
    BuffHdrHdr_t hdr;
}BuffHdr_t;

/*================================================================*/
/*                      @GLOBAL VAVIABLES                         */
/*================================================================*/
BUFF_EXT BuffHdr_t gUART1BuffPool[BUFFPOOL_SIZE];
BUFF_EXT BuffHdr_t *pUART1FFL;/* 指向当前存放数据处 */
BUFF_EXT BuffHdr_t pUART1BuffHdr;

BUFF_EXT BuffHdr_t gUART2BuffPool[BUFFPOOL_SIZE];
BUFF_EXT BuffHdr_t *pUART2FFL;/* 指向当前存放数据处 */
BUFF_EXT BuffHdr_t pUART2BuffHdr;



/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
extern void BuffPool_Init(void);

#ifdef __cplusplus
}
#endif

#endif 
