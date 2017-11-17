#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/OpenGL/IOpenGLContext.h>
#include <stack>

namespace Veritas {
    namespace OpenGL {
        class OpenGLESContext : public IOpenGLContext {
            public:
                OpenGLESContext(uint64 window, uint32 major, uint32 minor);
                ~OpenGLESContext();

                void swapBuffers();
                void makeCurrent();
            private:
                void* display;
                void* surface;
                void* context;
                uint64 window;
        };
    }
}
