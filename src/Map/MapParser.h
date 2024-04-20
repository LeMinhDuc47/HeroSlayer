#ifndef MAPPARSER_H
#define MAPPARSER_H
#include<bits/stdc++.h>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"
using namespace std;
class MapParser
{
    public:
        bool Load();
        void Clean();
         GameMap* GetMap(string id) { return m_MapDict[id]; }
         static MapParser* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
        }

    private:
        bool Parse(string id, string source);
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement *xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount);

    private:
        MapParser() {};
        static MapParser* s_Instance;
        map<string, GameMap*> m_MapDict;
};

#endif
