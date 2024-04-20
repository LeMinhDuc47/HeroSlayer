#ifndef TILELAYER_H
#define TILELAYER_H
#include<bits/stdc++.h>
#include "Layer.h"
using namespace std;

struct Tileset
{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    string Name, Source;

    void Log() {

    }
};

using TilesetList = vector<Tileset>;
using TileMap = vector<vector<int>>;

class TileLayer : public Layer
{
    public:
        TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TilesetList tilesets);
        virtual void Render();
        virtual void Update();
        TileMap GetTilemap() { return m_TileMap; }

    private:
        int m_TileSize;
        int m_RowCount, m_ColCount;

        TileMap m_TileMap;
        TilesetList m_Tilesets;
};

#endif
