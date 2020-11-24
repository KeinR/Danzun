#ifndef DANZUN_ABSRENDERCONF_H_INCLUDED
#define DANZUN_ABSRENDERCONF_H_INCLUDED

namespace dan {
    class Context;
}

namespace dan {
    class AbsRenderConf {
    public:
        virtual ~AbsRenderConf() = 0;
        // Bind shader, etc
        virtual void setup(Context &c) = 0;
        // Render content, with the precondition that all
        // bindings from setup() are still active
        virtual void render(Context &c) = 0;
    };
}

#endif
