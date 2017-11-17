#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/OpenGL/IOpenGLContext.h>

namespace Veritas {
    namespace OpenGL {
        class OpenGLContext : public IOpenGLContext {
            public:
                OpenGLContext(uint64 window, uint32 major, uint32 minor);
                ~OpenGLContext();

                void swapBuffers();
                void makeCurrent();

                static void* getProcAddress(const char* name);
            private:
                uint64 gl, dc;
                uint64 window;
        };
    }
}
