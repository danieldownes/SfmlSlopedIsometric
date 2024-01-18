#include "QuadTreeInitialiser.h"

namespace sf {
    bool rectContains(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
        return (rect2.getPosition().x >= rect1.getPosition().x) &&
            (rect2.getPosition().x + rect2.getSize().x <= rect1.getPosition().x + rect1.getSize().x) &&
            (rect2.getPosition().y >= rect1.getPosition().y) &&
            (rect2.getPosition().y + rect2.getSize().y <= rect1.getPosition().y + rect1.getSize().y);
    }
}

QuadTreeInitialiser::QuadTreeInitialiser(sf::FloatRect size, unsigned int Depth) : depth(Depth), quadRect(size) {}

void QuadTreeInitialiser::clear() {
    quadItems.clear();
    for (auto& child : childQuad) {
        if (child) {
            child->clear();
        }
        child.reset();
    }
}

void QuadTreeInitialiser::insert(const TerrainTile& item, sf::FloatRect itemSize) {
    if (depth + 1 < MAX_DEPTH) {
        for (int i = 0; i < 4; ++i) {
            if (sf::rectContains(childQuadRect[i], itemSize)) {
                if (!childQuad[i]) {
                    childQuad[i] = std::make_shared<QuadTreeInitialiser>(childQuadRect[i], depth + 1);
                }
                childQuad[i]->insert(item, itemSize);
                return;
            }
        }
    }
    quadItems.push_back(item);
}

std::list<TerrainTile> QuadTreeInitialiser::items() const {
    std::list<TerrainTile> listItems;
    listItems.insert(listItems.end(), quadItems.begin(), quadItems.end());

    for (const auto& child : childQuad) {
        if (child) {
            std::list<TerrainTile> childItems = child->items();
            listItems.insert(listItems.end(), childItems.begin(), childItems.end());
        }
    }

    return listItems;
}
