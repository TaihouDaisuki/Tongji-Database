#include <cstring>
#include <new>

#include "array_input.h"

using namespace std;

array_input::array_input()
{
    A = new(nothrow) int[default_len];
    if(A == NULL)
        exit(-1);
    n = 0; len = default_len;
}
array_input::~array_input()
{
    if(A != NULL)
        delete[]A;
}

int array_input::remake()
{
    int* tmp=new(nothrow) int[len << 1];
    if(tmp==NULL)
        return 0;
    memcpy(tmp,A,len*sizeof(int));
    delete[]A;
    A = tmp;
    len <<= 1;
    return 1;
}

int array_input::clear()
{
    n = 0;
    return 1;
}

int array_input::add(const int x)
{
    int done = 1;
    if(n == len)
        done = remake();

    if(!done)
        return ERROR;

    A[n++] = x;
    return OK;
}
