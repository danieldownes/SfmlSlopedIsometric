#pragma once
#include <array>
#include <memory>
#include <vector>
#include <list>
#include "SFML/Graphics/Rect.hpp"
#include "TerrainTile.h"

#define MAX_DEPTH 5

class QuadTreeInitialiser {
public:
    QuadTreeInitialiser(sf::FloatRect size, unsigned int Depth);
    void insert(const TerrainTile& item, sf::FloatRect itemSize); 
    std::list<TerrainTile> items() const; 

    //std::list<TerrainTile> search(sf::FloatRect searchArea); 
    //std::list<TerrainTile> items() const;  

    //sf::FloatRect getQuadRect() const { return quadRect; } 

private:
    void clear();
    //void resize(sf::FloatRect size); 
    //void searchQuad(sf::FloatRect searchArea, std::list<TerrainTile>& coveredItems) const;  

    unsigned int depth = 0;
    sf::FloatRect quadRect;
    std::vector<TerrainTile> quadItems; 
    std::array<sf::FloatRect, 4> childQuadRect{};
    std::array<std::shared_ptr<QuadTreeInitialiser>, 4> childQuad;
};
