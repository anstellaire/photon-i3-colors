#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct default_pipeline {
    static void stage2_specific() {
        std::cout << " > Stage #2 (specific - default)" << std::endl;
    }

    static void stage4_specific() {
        std::cout << " > Stage #4 (specific - default)" << std::endl;
    }
};

template<typename Impl>
struct pipeline {
    Impl impl;

    void pass() {
        std::cout << "Starting pipeline" << std::endl;
        stage1_generic();
        stage2_specific();
        stage3_generic();
        stage4_specific();
    }

    void stage1_generic() {
        std::cout << " > Stage #1 (generic)" << std::endl;
    }

    void stage2_specific() {
        impl.stage2_specific();
    }

    void stage3_generic() {
        std::cout << " > Stage #3 (generic)" << std::endl;
    }

    void stage4_specific() {
        impl.stage4_specific();
    }
};

struct custom_pipeline {
    void stage2_specific() {
        std::cout << " > Stage #2 (specific - override)" << std::endl;
    }

    void stage4_specific() {
        default_pipeline::stage4_specific();
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    pipeline<custom_pipeline> cp;
    cp.pass();
}
