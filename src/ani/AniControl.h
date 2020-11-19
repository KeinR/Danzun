#ifndef DANZUN_ANICONTROL_H_INCLUDED
#define DANZUN_ANICONTROL_H_INCLUDED

#include <vector>
#include <memory>

#include "Animation.h"

namespace dan {
    class AniControl {
    public:
        typedef std::shared_ptr<Animation::Instance> instance_t;
        typedef std::weak_ptr<Animation::Instance> wInstance_t;
        typedef std::vector<wInstance_t> instances_t;
    private:
        instances_t instances;
    public:
        AniControl();
        instance_t add(Animation &a);
        void add(const wInstance_t &inst);
        void advance(float deltaTime);
    };
}

#endif
