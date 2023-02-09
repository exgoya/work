#include <stdio.h>


void func()
{
    char *sPtr = malloc(1024 * 1024);
}

main()
{
    char *sPtr = malloc(1024 * 1024);

    func();

}
