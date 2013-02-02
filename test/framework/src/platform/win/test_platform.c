#include <crtdbg.h>
#include <windows.h>
#include "test_platform.h"
void setup_test_enviroment()
{
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

    SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);
}

