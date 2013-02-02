//#define sge_static_assert(expr) static int should_be_true[(expr)!=0];
#define sge_static_assert(expr) static int sge_static_assert##__LINE__[(expr)!=0];
