#include "../../lib/utils/str_utils.h"

int strcmp(char* first, char* second, int length)
{
    for(int i = 0; i < length; ++i)
    {
        if(first[i] != second[i])
        {
            return 0;
        }
    }
    return 1;
}