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
    gUART1BuffPool->hdr.len = BUFFPOOL_SZ;
    gUART1BuffPool->hdr.inUse = BUFF_NOTUSED; 
	pUART1FFL = gUART1BuffPool;
    

	gUART2BuffPool->hdr.len = BUFFPOOL_SZ;
    gUART2BuffPool->hdr.inUse = BUFF_NOTUSED; 
	pUART2FFL = (BuffHdr_t *)0;
}


