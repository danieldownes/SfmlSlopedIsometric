#pragma once
#include <vector>
#include <array>

#include "SFML/Graphics/Rect.hpp"
#include "BattlefieldCell.h"

class GameState {
public:
    class QuadTree {
    public:
        virtual void f() {};

        QuadTree(const sf::IntRect& rect, const unsigned int& depth)
            : depth(depth), quadRect(rect), children{ nullptr, nullptr, nullptr, nullptr } {}
        ~QuadTree() {
            for (QuadTree* child : children)
                delete[] child;
            delete this;
        }

        unsigned int getDepth() const { return depth; }
        sf::IntRect getQuadRect() const { return quadRect; }

        void setChildren(std::array<QuadTree*, 4> _children) { children = _children; }
        std::array<QuadTree*, 4> getChildren() const { return children; }
    protected:
        unsigned int depth;
        sf::IntRect quadRect;
        std::array<QuadTree*, 4> children;
    };

    class QuadTreeLeaf : public QuadTree {
    public:
        virtual void f() {};

        QuadTreeLeaf(const sf::IntRect& rect, const unsigned int& depth, std::vector<BattlefieldCell>::iterator& _iter)
            : QuadTree(rect, depth), iter(_iter) {}

        std::vector<BattlefieldCell>::iterator getIterator() { return iter; };
    private:
        std::vector<BattlefieldCell>::iterator iter;
    };

public:
    std::vector<BattlefieldCell> BattlefieldVector;
    QuadTree* quadTree = nullptr;
};



