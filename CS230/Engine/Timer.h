#pragma once
#include "Component.h"

namespace CS230 {
    class Timer : public Component {
    public:
        Timer(double start_time) : current_time(start_time) {}

        void Update(double dt) override {
            current_time -= dt;
            if (current_time < 0.0) {
                current_time = 0.0;
            }
        }

        double GetTime() const { return current_time; }
        void Reset(double time) {
            current_time = time;
        }

    private:
        double current_time;
    };
}