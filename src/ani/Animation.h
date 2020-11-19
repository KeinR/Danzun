#ifndef DANZUN_ANIMAITON_H_INLCUDED
#define DANZUN_ANIMAITON_H_INLCUDED

#include <memory>
#include <vector>
#include <functional>

#include "../sprite/AbsTexture.h"
#include "../sprite/AbsRenderConf.h"
#include "Frame.h"
#include "../render/Matrix.h"

namespace dan {
    class AniControl;
}

namespace dan {
    class Animation {
    public:
        class Instance: public AbsRenderConf {
            Animation *parent;
            // In seconds / game time 
            float timeToFlip;
            unsigned int index;
        public:
            // Ill formed
            Instance();
            Instance(Animation &parent);
            void restart();
            void advance(float deltaTime);

            void setup(Context &c) override;
            void render(Context &c) override;
        };

        typedef std::function<void(Instance &inst)> callback_t;
        typedef std::shared_ptr<Instance> instance_t;
    private:
        std::vector<Frame> frames;
        callback_t callback;
    public:

        Animation();

        instance_t newInstance();
        void setCallback(const callback_t &func);
        void callCallback(Instance &inst);

        void pushFrame(const Frame &frame);
        Frame &getFrame(unsigned int index);
        unsigned int countFrames();
    };
}

#endif
