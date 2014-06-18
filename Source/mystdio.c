/*************************************************************************
        (c) COPYRIGHT 2010-2018 by USC Systems, Inc.    
                          All rights reserved.
    
       This software is confidential and proprietary to USC 
     Systems, Inc.  No part of this software may be reproduced,    
     stored, transmitted, disclosed or used in any form or by any means
     other than as expressly provided by the written license agreement    
     between USC Systems and its licensee.
    
FileName    : mystdio.c
Author      : ranwei    
Version     : 
Date        : 2014/5/13 20:42:13
Description : 
Others      : 
*************************************************************************/


#include "mystdio.h" 


/*******************************************************************************************
@fn     : ltos

@brief  : long��Ϊ�ַ���

@param  : 

@return : 0 -- 
          1 -- 
********************************************************************************************/
unsigned char ltos(const unsigned long ulData,char *pucOutput)
{
    unsigned long ulTemp;
    ulTemp = ulData;
    unsigned char ucLen;
    unsigned char aucBuff[10];
    char *p = pucOutput;
    unsigned char i = 0;
    
    while(ulTemp != 0)
    {
        aucBuff[i] = ulTemp % 10 + '0';
        ulTemp = ulTemp / 10;
        i++;
    }
    ucLen = i;
    while(i)
    {
        i--;
        *p = aucBuff[i];
        p++;
    }
    return ucLen;
}


/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :            
********************************************************************************************/
unsigned char IsStrPrefix(char *cStr,char *prefix)
{
    char *pSrc,*pre;
    pSrc = cStr;
    pre = prefix;
    if((cStr == (char *)0)||(prefix == (char *)0))
    {
        return 0;
    }

    for ( ; *pSrc != '\0' && *pre != '\0' ; pSrc++, pre++)
    {
        if (*pSrc != *pre)
        {
            return 0;
        }
    }

    return *pre == '\0';
}

/*******************************************************************************************
@fn     : 

@brief  : ����ַ���s���ַ�c��ͷ����ɾ��������1;���򷵻�0

@param  : 

@return :            
********************************************************************************************/
unsigned char strstripstart(char **s, const char c)
{
    
    char *p = *s;
    if(p == (char *)0)
    {
        return 0;
    }
    if(*p == c)
    {
        p++;
        (*s)++;
        return 1;
    }
    return 0;
}




/*******************************************************************************************
@fn     : 

@brief  : �ֽ��ַ���Ϊһ���ַ�������sָ���λ�������ɨ�裬����ctָ����ַ����е���
          ���󣬽����ַ��滻ΪNULL������sָ��ĵ�ַ���������ڷָ�ؼ��֡��������ַ���
          ֮��ֻ���ϸ����һ�Ρ��������

@param  : 

@return :            
********************************************************************************************/
char *strsep(char **s, const char *ct)
{
	char *sbegin = *s;
	char *end;

	if (sbegin == (char *)0)
		return (char *)0;

	end = strpbrk(sbegin, ct);
	if (end)
		*end++ = '\0';
	*s = end;
	return sbegin;
}

/*******************************************************************************************
@fn     : 

@brief  : 

@param  : 

@return :            
********************************************************************************************/
char *strpbrk(const char *cs, const char *ct)
{
	const char *sc1, *sc2;

    if((cs == (char *)0)||((ct == (char *)0))) 
    {
        return (char *)0;
    }
    
	for (sc1 = cs; *sc1 != '\0'; ++sc1) {
		for (sc2 = ct; *sc2 != '\0'; ++sc2) {
			if (*sc1 == *sc2)
				return (char *)sc1;
		}
	}
	return (char *)0;
}



