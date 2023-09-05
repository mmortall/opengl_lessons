// Copyright (C) 2011-2012 Sergey Taraban

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <string.h>
#include <ctime>
#include <math.h>
#include <assert.h>
#include <vector>
#include <string>

#include "cml\cml.h"
#define matrix4f cml::matrix44f_r

#ifdef WIN32
#include "windows.h"
#include "gl/glew.h"		//window library for OpenGL
#endif

#ifdef LINUX
#include "X11/X.h"

#define GL_GLEXT_PROTOTYPES
#endif

//OpenGL implemenataion
#include "GL/glut.h"	//gl utility library
#include "GL/glu.h"		//gl utility library
#include "GL/gl.h"
#include "GL/glext.h"

// TODO: reference additional headers your program requires here
