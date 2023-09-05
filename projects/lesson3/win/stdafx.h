// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#ifdef WIN32
#include "windows.h"
#include "gl/glew.h"		//window library for OpenGL
#include "targetver.h"
#endif

#ifdef LINUX
#include "X11/X.h"
#include "X11/GLX.h"
#endif

#define GL_GLEXT_PROTOTYPES

//OpenGL implemenataion
#include "GL/glut.h"	//gl utility library
#include "GL/glu.h"		//gl utility library
#include "GL/gl.h"
#include "GL/glext.h"

// TODO: reference additional headers your program requires here
