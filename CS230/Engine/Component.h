#pragma once

namespace CS230 {
    class Component {
    public:
        virtual ~Component() {};
        virtual void Update([[maybe_unused]] double dt) {};
    };
}
