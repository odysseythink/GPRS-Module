/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : buff.c
Author      : ranwei    
Version     : 
Date        : 2014/6/12 14:42:36
Description : 
Others      : 
*************************************************************************/


#include  "buff.h"

/*********************************************************************
** @fn     : 
**
** @brief  : 
**
** @param  :
**
** @return :
*********************************************************************/
void BuffPool_Init(void)
{
    pLOCALBuffHdr = gLOCALBuffPool;
    pLOCALBuffHdr->hdr.len = 0;
    pLOCALBuffHdr->hdr.inUse = BUFF_INUSED; 
    
    pNWKBuffHdr = gNWKBuffPool;
	pNWKBuffHdr->hdr.len = 0;
    pNWKBuffHdr->hdr.inUse = BUFF_INUSED; 
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
void LocalBuffPool_It(unsigned char ucData)
{
    if(pLOCALBuffHdr->hdr.len < (BUFFPOOL_SZ-1))
    {
        gLOCALBuffPool[1+pLOCALBuffHdr->hdr.len] = ucData;
        pLOCALBuffHdr->hdr.len++;
    }
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
void NWKBuffPool_It(unsigned char ucData)
{
    if(pNWKBuffHdr->hdr.len < (BUFFPOOL_SZ-1))
    {
        gNWKBuffPool[1+pLOCALBuffHdr->hdr.len] = ucData;
        pNWKBuffHdr->hdr.len++; 
    }
}


