#include <memory>
#include <vector>
#include <iostream>

// -----------------------------------------------------------------------------
//   HELPER ENTITIES
// -----------------------------------------------------------------------------

struct vec3 {
    float x,y,z;
};

// -----------------------------------------------------------------------------
//   WITHOUT FLYWEIGHT
// -----------------------------------------------------------------------------

struct fat_tree {
    char const* name_;
    unsigned char tex_[1024];
    vec3 pos_;

    fat_tree(char const* name, vec3 pos) : name_(name), pos_(pos) {}

    char const* name() { return name_; }
};

// -----------------------------------------------------------------------------
//   WITH FLYWEIGHT
// -----------------------------------------------------------------------------

struct tree_asset {
    char const* name_;
    unsigned char tex_[1024];

    tree_asset(char const* name) : name_(name) {}

    char const* name() { return name_; }
};

struct tree {
    vec3 pos_;
    std::shared_ptr<tree_asset> asset;

    tree(vec3 pos, std::shared_ptr<tree_asset> asset) :
        pos_(pos), asset(std::move(asset)) {}

    char const* name() { return asset->name(); }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    std::size_t forest_size = 1000000;

    // without flyweight

    std::vector<fat_tree> fat_forest(forest_size, fat_tree("Oak", {0,0,0}));

    std::printf("Fat forest size: %lu MB\n",
        (sizeof(fat_tree) * fat_forest.size()) / (1024 * 1024));

    // with flyweight

    std::shared_ptr<tree_asset> oak_tree_asset{new tree_asset("Oak")};
    std::vector<tree> flw_forest(forest_size, tree({0,0,0}, oak_tree_asset));

    std::printf("Flyweight forest size: %lu MB\n",
        (sizeof(tree_asset) + sizeof(tree) * flw_forest.size()) / (1024 * 1024));
}
