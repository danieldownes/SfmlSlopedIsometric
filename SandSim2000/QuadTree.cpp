#include "QuadTree.h"

QuadTree::QuadTree(const sf::IntRect& rect, const unsigned int& depth)
    : depth(depth), quadRect(rect) {
}

QuadTreeInternal::QuadTreeInternal(const sf::IntRect& rect, const unsigned int& depth)
    : QuadTree(rect, depth), children{ nullptr, nullptr, nullptr, nullptr } {
}

QuadTreeInternal::~QuadTreeInternal() {
    for (QuadTree* child : children)
        delete[] child;
    delete this;
}

QuadTreeLeaf::QuadTreeLeaf(const sf::IntRect& rect, const unsigned int& depth, std::vector<BattlefieldCell>::iterator& _iter)
    : QuadTree(rect, depth), iter(_iter) {}

QuadTreeLeaf::~QuadTreeLeaf() {
    delete this;
}