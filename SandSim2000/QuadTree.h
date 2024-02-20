#pragma once
#include <array>
#include "SFML/Graphics/Rect.hpp"
#include <vector>
#include <iostream>

struct QuadTree {
    virtual void f() {};

    unsigned int depth;
    sf::IntRect quadRect;
    std::array<QuadTree*, 4> children;


    virtual std::vector<BattlefieldCell>::iterator insert(BattlefieldCell* cell, int multiplier)
    {
        std::cout << quadRect.left << ":" << quadRect.top << ":" << quadRect.width << ":" << quadRect.height << std::endl;
        for (int i = 0; i < 4; i++)
        {
            if (children[i] != nullptr)
            {
                if (children[i]->quadRect.contains(sf::Vector2i(cell->x * multiplier, cell->y * multiplier)))
                {
                    return children[i]->insert(cell, multiplier);
                }
            }
        }
        std::vector<BattlefieldCell>::iterator fail;
        return fail;
    }

    virtual std::vector<BattlefieldCell>::iterator insertOverride(BattlefieldCell* cell, int multiplier)
    {
        std::vector<BattlefieldCell>::iterator fail;
        return fail;
    }


    QuadTree(const sf::IntRect& rect, const unsigned int& depth)
        : depth(depth), quadRect(rect), children{ nullptr, nullptr, nullptr, nullptr } {}

    ~QuadTree() {
        for (QuadTree* child : children)
            delete[] child;
    }
};

struct QuadTreeLeaf : public QuadTree {
    std::vector<BattlefieldCell>::iterator iter;

    std::vector<BattlefieldCell>::iterator insert(BattlefieldCell* cell, int multiplier) override
    {
        std::cout << "Child leaf" << std::endl;
        

        for (int i = 0; i < 4; ++i) {
            sf::IntRect childRect = calculateChildRect(i);
            children[i] = new QuadTreeLeaf(childRect, depth + 1, iter);
        }

        for (int i = 0; i < 4; ++i) {
            if (children[i]->quadRect.contains(sf::Vector2i(cell->x * multiplier, cell->y * multiplier))) {
                return children[i]->insertOverride(cell, multiplier);
            }
        }

        std::vector<BattlefieldCell>::iterator fail;
        return fail;
    }

    std::vector<BattlefieldCell>::iterator insertOverride(BattlefieldCell* cell, int multiplier) override
    {
        *iter = *cell;
        return iter;
    }

    QuadTreeLeaf(const sf::IntRect& rect, const unsigned int& depth, std::vector<BattlefieldCell>::iterator& _iter)
        : QuadTree(rect, depth), iter(_iter) {}

private:
    sf::IntRect calculateChildRect(int index) const
    {
        int halfWidth = quadRect.width / 2;
        int halfHeight = quadRect.height / 2;
        int childLeft = quadRect.left + (index % 2) * halfWidth;
        int childTop = quadRect.top + (index / 2) * halfHeight;
        return sf::IntRect(childLeft, childTop, halfWidth, halfHeight);
    }
};