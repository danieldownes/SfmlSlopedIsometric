#pragma once
#include <array>
#include <vector>
#include <iostream>
#include "SFML/Graphics/Rect.hpp"
#include "BattlefieldCell.h"

class QuadTree {
public:
    virtual void f() = 0;

    QuadTree(const sf::IntRect& rect, const unsigned int& depth);

    unsigned int getDepth() const { return depth; }
    sf::IntRect getQuadRect() const { return quadRect; }
protected:
    unsigned int depth;
    sf::IntRect quadRect;
};

class QuadTreeInternal : public QuadTree {
public:
    virtual void f() {};

    QuadTreeInternal(const sf::IntRect& rect, const unsigned int& depth);
    ~QuadTreeInternal();

    //std::vector<Agent*> getAgents() const override;

    /*std::array<QuadTree*, 4> createChildren(std::array<bool, 4> childldrenIsLeaf);
    std::array<QuadTree*, 4> createChildren(std::array<TerrainTile*, 4> childrenTerrain);
    std::array<QuadTree*, 4> createChildren() { return createChildren({ nullptr, nullptr, nullptr, nullptr }); }*/

    void setChildren(std::array<QuadTree*, 4> _children) { children = _children; }
    std::array<QuadTree*, 4> getChildren() const { return children; }
private:
    std::array<QuadTree*, 4> children;
};

class QuadTreeLeaf : public QuadTree {
public:
    virtual void f() {};

    QuadTreeLeaf(const sf::IntRect& rect, const unsigned int& depth, std::vector<BattlefieldCell>::iterator& _iter);
    ~QuadTreeLeaf();

    //void setTerrainInfo(const TerrainTile terrain) { terrainInfo = terrain; }

    //TerrainTile getTerrainInfo() const { return terrainInfo; }
    //std::vector<Agent*> getAgents() const override { return agents; }

    std::vector<BattlefieldCell>::iterator getIterator() { return iter; };
private:
    //TerrainTile terrainInfo;
    /*std::vector<Agent*> agents;*/

    std::vector<BattlefieldCell>::iterator iter;
};