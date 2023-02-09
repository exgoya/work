#ifndef __COMM_LIB
#define __COMM_LIB  1


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


int createSocket( int * aSock );


int bindSocket( int aSock,
                int aPort );


int listenSocket( int aSock,
                  int aBackLogSz );


int acceptSocket( int aSock,
                  int *aNewSock );


void closeSocket( int aSock );

int connectHost( char * aAddr,
                 int    aPortNo,
                 int  * aSock );

int sendData( int     aSock,
              char  * aData,
              int     aDataSz );


int recvData( int     aSock,
              char  * aData,
              int   * aDataSz );


#endif
