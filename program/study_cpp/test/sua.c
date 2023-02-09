#include<stdio.h>

int main(int argc,char *argv[])
{
    char c;
    int c1, c2;
    
    if(argc > 3)
    {
        c1 = atoi(argv[1]);
        c2 = atoi(argv[2]);
        c = argv[3][0];
    }
    else
    {
        printf( "usage] %s c1 c2\n", argv[0] );
    }


    if(c == '+')
    {
        printf("%d + %d = %d\n" , c1,c2,(c1+c2));
    }
    if(c == '-')
    {
        printf("%d - %d = %d\n" , c1,c2,(c1-c2));
    }

    if(c == '*')
    {
        printf("%d * %d = %d\n" , c1,c2,(c1*c2));
    }

    if(c == '/')
    {
        if(c2 == 0)
        {
            printf("cannot divide 0\n");
        }
        else
        {
            printf("%d / %d = %d\n" , c1,c2,(c1/c2));
        }
    }


}
