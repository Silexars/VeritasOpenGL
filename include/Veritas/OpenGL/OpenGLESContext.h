#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Veritas {
    namespace OpenGL {
        class OpenGLESContext {
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
