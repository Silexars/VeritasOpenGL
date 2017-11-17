#pragma once

#include <Veritas/Definitions/Definitions.h>

#if defined(PLATFORM_WINDOWS)
    #define OPENGLCONTEXT_WGL "WGL Context"
    #define OPENGLCONTEXT_BACKEND OPENGLCONTEXT_WGL
#elif defined(PLATFORM_UNIX)
    #define OPENGLCONTEXT_EGL "EGL Context"
    #define OPENGLCONTEXT_BACKEND OPENGLCONTEXT_EGL
#endif
