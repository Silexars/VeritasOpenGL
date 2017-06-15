#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <stack>

namespace Veritas {
    namespace OpenGL {
        class OpenGLESContext {
            public:
                OpenGLESContext(uint64 window, uint32 major, uint32 minor);
                ~OpenGLESContext();

                void swapBuffers();
                void makeCurrent();

                static void push();
                static void pop();
            private:
                void* display;
                void* surface;
                void* context;
                uint64 window;
        };
    }
}
