#include "interface_c.h"
int add(int x, int y)
{
return x + y;
}
int sub(int x, int y)
{
return x - y;
}

test_type getresult(test_type v)
{
    return v;
}

test_type* getresultptr( test_type* v )
{
    return v;
}

