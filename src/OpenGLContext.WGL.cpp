#include <Veritas/OpenGL/Definitions.h>
#ifdef OPENGLCONTEXT_WGL

#include <Veritas/OpenGL/Definitions.h>
#include <Veritas/OpenGL/OpenGL.h>

#include <Windows.h>

using namespace Veritas::OpenGL;

#define OPENGL_IMPLEMENTATION
#include <Veritas/OpenGL/OpenGL45.h>

// We are not selecting core versions yet, Windows gets the latest automatically
OpenGLContext::OpenGLContext(uint64 window, uint32 major, uint32 minor) : window(window) {
    static PIXELFORMATDESCRIPTOR pfd = {
       sizeof(pfd),
       1,
       PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
       PFD_TYPE_RGBA,
       32,0,0,0,0,0,0,
       0,0,0,0,0,0,0,
       32,0,0,
       PFD_MAIN_PLANE,0,0,0,0};

    dc = (uint64) GetDC((HWND) window);
    SetPixelFormat((HDC) dc, ChoosePixelFormat((HDC) dc, &pfd), &pfd);
    gl = (uint64) wglCreateContext((HDC) dc);

    push();
    makeCurrent();
    GLInitialize45();
    pop();
}

OpenGLContext::~OpenGLContext() {
    wglDeleteContext((HGLRC) gl);
}

void OpenGLContext::makeCurrent() {
    wglMakeCurrent((HDC) dc, (HGLRC) gl);
}

void OpenGLContext::swapBuffers() {
    SwapBuffers((HDC) dc);
}

void* OpenGLContext::getProcAddress(const char *name) { return wglGetProcAddress(name); }

#endif
