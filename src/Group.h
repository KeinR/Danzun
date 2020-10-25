#ifndef DANZUN_GROUP_H_INCLUDED
#define DANZUN_GROUP_H_INCLUDED

#include <memory>
#include <vector>

#include "Node.h"

namespace dan {
    class Context;
}

namespace dan {
    class Group: public Node {
    public:
        typedef std::shared_ptr<Node> n_t;
        typedef std::vector<n_t> nodes_t;
        nodes_t nodes;
        Group();
        void render(Context &c) override;
    };
}

#endif
