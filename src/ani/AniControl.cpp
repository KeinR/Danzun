#include "AniControl.h"

dan::AniControl::AniControl() {
}
void dan::AniControl::add(const wInstance_t &inst) {
    instances.push_back(inst);
}
void dan::AniControl::advance(float deltaTime) {
    for (instances_t::iterator it = instances.begin(); it < instances.end();) {
        instance_t inst = it->lock();
        if (inst) {
            inst->advance(deltaTime);
            ++it;
        } else {
            it = instances.erase(it);
        }
    }
}
