//
// Created by Jon Stephens on 8/28/22.
//

#ifndef VANGUARD_CONTAINER_H
#define VANGUARD_CONTAINER_H

#include <vector>

namespace vanguard {
    template<typename Contained> class Container {
    public:
        explicit Container(std::vector<Contained *> contains) : contained(contains) {};

        const std::vector<Contained *> &contains() const {
            return contained;
        }

    protected:
        std::vector<Contained *> contained;
    };
}


#endif //VANGUARD_CONTAINER_H
