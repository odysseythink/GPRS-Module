/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : mystdio.h
Author      : ranwei    
Version     : 
Date        : 2014/5/13 20:41:49
Description : 该模块用于定义一些c标准库函数，函数的实现在mystdio.h�?
Others      : 
*************************************************************************/
#ifndef __MYSTDIO_H__
#define __MYSTDIO_H__

#ifdef __cplusplus
extern "C"{
#endif

/*  
        @define
*/


/* �ض���һ��ָ���������� */
//typedef void *va_list[1];

/*  */
//#define va_start(ap,parmN) (ap[0] = ((char *) &parmN) - 1)

/*
        @func
*/
unsigned char ltos(const unsigned long ulData,char *pucOutput);
unsigned char IsStrPrefix(char *cStr,char *prefix);
char *strsep(char **s, const char *ct);
char *strpbrk(const char *cs, const char *ct);
unsigned char strstripstart(char **s, const char c);




#ifdef __cplusplus
}
#endif

#endif 
