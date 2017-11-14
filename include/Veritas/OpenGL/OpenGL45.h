#pragma once

#include "glcorearb.h"

// This code is cool but it needs reorganization :)

#include <Veritas/OpenGL/OpenGLContext.h>
#include <gl/GL.h>

#ifdef OPENGL_IMPLEMENTATION
    #define OPENGL_FUNCDEF(DEF, NAME) DEF NAME = 0
#else
    #define OPENGL_FUNCDEF(DEF, NAME) extern DEF NAME
#endif

#define OPENGL_FUNC OPENGL_FUNCDEF

#include "OpenGL45Functions.h"

#ifdef OPENGL_IMPLEMENTATION

#undef OPENGL_FUNC

#define OPENGL_FUNCLOAD(DEF, NAME) if (!NAME) NAME = (DEF) OpenGLContext::getProcAddress(#NAME)
#define OPENGL_FUNC OPENGL_FUNCLOAD

void GLInitialize45() {
    using namespace Veritas::OpenGL;
    static bool notInitialized = true;
    if (notInitialized) {
        #include "OpenGL45Functions.h"
        notInitialized = false;
    }
}
#endif
