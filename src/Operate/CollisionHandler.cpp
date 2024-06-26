#include "CollisionHandler.h"
#include "Engine.h"
#include <bits/stdc++.h>
using namespace std;
CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetLayers()[0];
	m_CollisionTilemap = m_CollisionLayer->GetTileMap();
}

void CollisionHandler::Update() {
    TileLayer* temp_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetLayers()[0];
    m_CollisionLayer = temp_CollisionLayer;
    m_CollisionTilemap = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
	bool x_overlaps = (a.x <= b.x + b.w) && (a.x + a.w >= b.x);
	bool y_overlaps = (a.y <= b.y + b.h) && (a.y + a.h >= b.y);
	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a, int tileSize, int RowCount, int ColCount) {
    int left_tile = static_cast<int> (round(static_cast<float>(a.x / tileSize)));
    int right_tile = static_cast<int> (round(static_cast<float>((a.x + a.w) / tileSize)));

    int top_tile = static_cast<int> (round(static_cast<float>(a.y / tileSize)));
    int bottom_tile = static_cast<int> (round(static_cast<float>((a.y + a.h) / tileSize)));

    if (left_tile <= 0) left_tile = 0;
    if (right_tile >= ColCount) right_tile = ColCount;

    if (top_tile <= 0) top_tile = 0;
    if (bottom_tile >= RowCount) bottom_tile = RowCount;

    for (int i = left_tile; i <= right_tile; ++i) {
        for (int j = top_tile; j <= bottom_tile; ++j) {
            if (m_CollisionTilemap[j][i] > 0 ) {
                return true;
            }
        }
    }
    return false;
}
