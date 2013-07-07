// Header files of frequent usage

#include <windows.h>

#include <queue>

using namespace std;
#define GLEW_STATIC
#include <gl/glew.h>
#include <gl/wglew.h>
#include "mathlib/matrix.h"

// Some useful defines

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

#define ESZ(elem) (int)elem.size()
