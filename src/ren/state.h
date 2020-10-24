#ifndef DANZUN_STATE_H_INCLUDED
#define DANZUN_STATE_H_INCLUDED

#include "../lib/opengl.h"

namespace dan::st {
    class framebuffer {
        GLint read;
        GLint write;
    public:
        inline framebuffer() {
            glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &read);
            glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &write);
        }
        inline ~framebuffer() {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, read);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, write);
        }
    };
    class viewport {
        GLint bounds[4];
    public:
        inline viewport() {
            glGetIntegerv(GL_VIEWPORT, bounds);
        }
        inline ~viewport() {
            glViewport(bounds[0], bounds[1], bounds[2], bounds[3]);
        }
    };
    class depthTest {
        GLboolean yes;
    public:
        inline depthTest() {
            glGetBooleanv(GL_DEPTH_TEST, &yes);
        }
        inline ~depthTest() {
            if (yes) {
                glEnable(GL_DEPTH_TEST);
            } else {
                glDisable(GL_DEPTH_TEST);
            }
        }
    };
    class blend {
        GLboolean yes;
    public:
        inline blend() {
            glGetBooleanv(GL_BLEND, &yes);
        }
        inline ~blend() {
            if (yes) {
                glEnable(GL_BLEND);
            } else {
                glDisable(GL_BLEND);
            }
        }
    };
    class faceCull {
        GLboolean yes;
    public:
        inline faceCull() {
            glGetBooleanv(GL_CULL_FACE, &yes);
        }
        inline ~faceCull() {
            if (yes) {
                glEnable(GL_CULL_FACE);
            } else {
                glDisable(GL_CULL_FACE);
            }
        }
    };
    class clearColor {
        GLfloat color[4];
    public:
        inline clearColor() {
            glGetFloatv(GL_COLOR_CLEAR_VALUE, color);
        }
        inline ~clearColor() {
            glClearColor(color[0], color[1], color[2], color[3]);
        }
    };
    class program {
        GLint p;
    public:
        inline program() {
            glGetIntegerv(GL_CURRENT_PROGRAM, &p);
        }
        inline ~program() {
            glUseProgram(p);
        }
    };
}

#endif
