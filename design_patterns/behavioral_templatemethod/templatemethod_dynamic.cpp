#include <iostream>
#include <memory>

// -----------------------------------------------------------------------------
//   PATTERN
// -----------------------------------------------------------------------------

struct pipeline {
    virtual ~pipeline() {}

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

    virtual void stage2_specific() = 0;

    void stage3_generic() {
        std::cout << " > Stage #3 (generic)" << std::endl;
    }

    virtual void stage4_specific() {
        std::cout << " > Stage #4 (specific - default)" << std::endl;
    }
};

struct custom_pipeline : pipeline {
    void stage2_specific() {
        std::cout << " > Stage #2 (specific - override)" << std::endl;
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    std::unique_ptr<pipeline> cp{new custom_pipeline};
    cp->pass();
}
