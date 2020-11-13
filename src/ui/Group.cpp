#include "Group.h"

dan::Group::Group() {
}
void dan::Group::render(Context &c) {
    for (n_t n : nodes) {
        n->render(c);
    }
}
