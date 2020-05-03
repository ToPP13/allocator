#include "lib.h"
#include "version.h"
#include <algorithm>    // std::copy_if

int version()
{
    return PROJECT_VERSION_PATCH;
}

long int fact(int N)
{
    if(N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}
