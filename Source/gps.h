/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : gps.h
Author      : ranwei    
Version     : 
Date        : 2014/6/16 19:39:01
Description : 
Others      : 
*************************************************************************/
#ifndef __GPS_H__
#define __GPS_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef GPS_GLOBAL
#define GPS_EXT
#else
#define GPS_EXT extern 
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
typedef struct {
    
}GPS_Info_t;


/*================================================================*/
/*                           @FUNCS                               */
/*================================================================*/
void GPS_Init(void);
GPS_Info_t Get_GPS_Info(void);


#ifdef __cplusplus
}
#endif

#endif 
