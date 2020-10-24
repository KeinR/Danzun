#ifndef DANZUN_WINDOWEVENT_H_INCLUDED
#define DANZUN_WINDOWEVENT_H_INCLUDED

namespace ne {
    class WindowEvent {
    public:
        virtual ~WindowEvent() = 0;
        virtual void keyPressed(int key, int action, int mods);
        virtual void mouseMoved(float mouseX, float mouseY);
        virtual void mouseClicked(int button, bool pressed, int mods);
        virtual void mouseScrolled(double xOffset, double yOffset);
        virtual void charInput(unsigned int codepoint);
    };
}

#endif
