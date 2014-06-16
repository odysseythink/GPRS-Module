/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : evl_board.h
Author      : ranwei    
Version     : 
Date        : 2014/6/16 19:42:12
Description : 
Others      : 
*************************************************************************/
#ifndef __EVL_BOARD_H__
#define __EVL_BOARD_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifdef EVL_BOARD_GLOBAL
#define EVL_BOARD_EXT
#else
#define EVL_BOARD_EXT extern 
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
void EVL_Board_Init(void);


#ifdef __cplusplus
}
#endif

#endif 
