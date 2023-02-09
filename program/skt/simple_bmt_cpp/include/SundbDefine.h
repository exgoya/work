#ifndef __CBSS_POC_DEF_H__
#define __CBSS_POC_DEF_H__

/****************************************************************************** 
* Name : Common Header
******************************************************************************/


#define _T_PRT(a,...)       { printf("> "); printf( a, ##__VA_ARGS__); fflush(stdout); }
#define _PRT    _T_PRT

#endif
