#ifndef DANZUN_NODE_H_INCLUDED
#define DANZUN_NODE_H_INCLUDED

namespace dan {
    class Node {
    public:
        virtual ~Node() = 0;
        virtual void render(Engine &c) = 0;
    };
}

#endif
