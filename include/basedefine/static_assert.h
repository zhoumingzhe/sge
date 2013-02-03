#define sge_static_assert(expr, msg) int _sge_static_assert_##msg[(!!(expr)*2 - 1)]
