#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char mName[32];
    int  mAge;
} Data;

int main()
{
    char *sPtr;
    Data *rData;

    char sIname[32];
    int  sIage;  
    int  rowCount = 0;
    int  j;
    char *iQuit = "quit";

 

    sPtr = (char *)malloc(sizeof(Data) * 10);
    
    while(1)
    {
        printf("Type Data!\n");
        scanf("%s %d", sIname, &sIage);

        if( strcmp( sIname, iQuit ) == 0 )
        {
            printf("result:\n");
 
            for( j = 0; j < rowCount; j++)
            {
                rData = (Data *)(sPtr + sizeof(Data) * j);
                printf("%s, %d\n", rData->mName, rData->mAge);
            } 
            break;
        }
        rData = (Data *)(sPtr + sizeof(Data) * rowCount);
        memcpy(rData->mName, sIname, strlen(sIname));
        rData->mAge = sIage;

        rowCount++;

    }    
    return 0;
}
