#include <Veritas/OpenGL/OpenGLESContext.h>
#include <EGL/egl.h>
#include <iostream>

using namespace Veritas;
using namespace OpenGL;

OpenGLESContext::OpenGLESContext(uint64 window, uint32 major, uint32 minor)
    : window(window)
{
    display = eglGetDisplay(0);
    eglInitialize(display, 0, 0);

    EGLint attr[] = {       // some attributes to set up our egl-interface
       EGL_BUFFER_SIZE, 32,
       EGL_DEPTH_SIZE, 16,
       EGL_RENDERABLE_TYPE,
       EGL_OPENGL_ES2_BIT,
       EGL_NONE
    };

    EGLConfig  ecfg;
    EGLint     num_config;
    if ( !eglChooseConfig(display, attr, &ecfg, 1, &num_config ) ) {
       std::cerr << "Failed to choose config (eglError: " << eglGetError() << ")" << std::endl;
    }

    if ( num_config != 1 ) {
       std::cerr << "Didn't get exactly one config, but " << num_config << std::endl;
    }

    surface = eglCreateWindowSurface (display, ecfg, window, NULL );
    if (surface == EGL_NO_SURFACE ) {
       std::cerr << "Unable to create EGL surface (eglError: " << eglGetError() << ")" << std::endl;
    }

    //// egl-contexts collect all state descriptions needed required for operation
    EGLint ctxattr[] = {
       EGL_CONTEXT_MAJOR_VERSION, (int32) major,
       EGL_CONTEXT_MINOR_VERSION, (int32) minor,
       EGL_NONE
    };
    context = eglCreateContext (display, ecfg, EGL_NO_CONTEXT, ctxattr );
    if (context == EGL_NO_CONTEXT ) {
       std::cerr << "Unable to create EGL context (eglError: " << eglGetError() << ")" << std::endl;
    }
}

OpenGLESContext::~OpenGLESContext() {
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);    
}

void OpenGLESContext::makeCurrent() { eglMakeCurrent(display, surface, surface, context); }
void OpenGLESContext::swapBuffers() { eglSwapBuffers(display, surface); }

thread_local std::stack<void*> contextes;

void OpenGLESContext::push() {
    contextes.push(eglGetCurrentContext());
    contextes.push(eglGetCurrentDisplay());
    contextes.push(eglGetCurrentSurface(EGL_DRAW));
    contextes.push(eglGetCurrentSurface(EGL_READ));
}

void OpenGLESContext::pop() {
    EGLSurface read = contextes.top(); contextes.pop();
    EGLSurface draw = contextes.top(); contextes.pop();
    EGLDisplay display = contextes.top(); contextes.pop();
    EGLContext context = contextes.top(); contextes.pop();
    eglMakeCurrent(display, draw, read, context);
}
