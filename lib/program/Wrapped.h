//
// Created by Jon Stephens on 9/2/22.
//

#ifndef VANGUARD_WRAPPED_H
#define VANGUARD_WRAPPED_H

#include <utility>

namespace vanguard {

    template<typename Base, typename Wrap>
    class Wrapped : public Base {
    public:
        template<typename ...Args>
        explicit Wrapped(const Wrap &w, Args&&... args) : wrapped(w), Base(std::forward<Args>(args)...) {};

        Wrap &unwrap() { return wrapped; }
    protected:
        const Wrap &wrapped;
    };
}

#endif //VANGUARD_WRAPPED_H
