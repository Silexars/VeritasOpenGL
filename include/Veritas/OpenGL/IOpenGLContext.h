#pragma once

namespace Veritas {
    namespace OpenGL {
        class IOpenGLContext {
            public:
                virtual ~IOpenGLContext() = default;

                virtual void makeCurrent() = 0;
                virtual void swapBuffers() = 0;

                static void push();
                static void pop();
        };
    }
}
