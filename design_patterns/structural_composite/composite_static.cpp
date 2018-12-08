#include <string>
#include <iostream>

// -----------------------------------------------------------------------------
//   PATTERN (static polymorphism + composition)
// -----------------------------------------------------------------------------

template<typename Impl>
struct component {
    Impl impl;

    std::string get() { return impl.get(); }
};

struct leaf {
    std::string get() {
        return "leaf";
    }
};

template<typename Left, typename Right>
struct node {
    component<Left> left;
    component<Right> right;

    std::string get() {
        return "node(" + left.get() + "," + right.get() + ")";
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    node<node<node<leaf, leaf>, node<leaf, leaf>>, node<leaf, leaf>> tree{
        node<node<leaf, leaf>, node<leaf, leaf>>{
            node<leaf, leaf>{
                leaf{},
                leaf{}
            },
            node<leaf, leaf>{
                leaf{},
                leaf{}
            }
        },
        node<leaf, leaf>{
            leaf{},
            leaf{}
        }
    };

    std::cout << tree.get() << std::endl;
}
