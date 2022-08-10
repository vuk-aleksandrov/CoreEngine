#include "CoreEngine.h"

namespace core
{
    int pow(int x, int y)
    {
        int ans = 1;
        for (int i = 0; i < y; i++)
            ans *= x;
        return ans;
    }

    int sq(int x)
    {
        return x * x;
    }
}
