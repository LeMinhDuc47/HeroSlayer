#include "MapParser.h"

#include <SDL.h>
#include <SDL_image.h>
using namespace std;
MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load()
{
    return Parse("MAP", "assets\\maps\\map1.tmx");
}

bool MapParser::Parse(string id,string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
    {
        cerr << "Failed to load: " << source << endl;
        return false;
    }

    SDL_Log("Parse XML...");

    TiXmlElement* root = xml.RootElement();
    int rowCount, colCount, tileSize = 0;

    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
    root->Attribute("tilewidth", &tileSize);

    SDL_Log("colCount = %d, rowCount = %d, tileSize = %d", colCount, rowCount, tileSize);

    TilesetList tilesets;
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == string("tileset"))
        {
            tilesets.push_back(ParseTileset(e));
        }
    }

    SDL_Log("tilesets = %d", (int)tilesets.size());

    GameMap* gamemap = new GameMap();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }

    }

    SDL_Log("maplayers = %d", (int)gamemap->m_MapLayers.size());

    m_MapDict[id] = gamemap;

    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)
{
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");

    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement *xmlLayer, TilesetList tilesets, int tileSize, int rowCount, int colCount)
{
    TiXmlElement* data;

    for(TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == string("data"))
        {
            data = e;
            break;
        }
    }


    string matrix(data->GetText());
    istringstream iss(matrix);
    string id;

    TileMap tilemap(rowCount, vector<int>(colCount, 0));

    for(int row = 0; row < rowCount; row++)
    {
        for(int col = 0; col < colCount; col++)
        {
            getline(iss, id, ',');
            stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good())
            {
                break;
            }
        }
    }

    return (new TileLayer(tileSize, rowCount, colCount, tilemap, tilesets));
}

void MapParser::Clean()
{
    map<string, GameMap*>::iterator it;
    for(it = m_MapDict.begin(); it != m_MapDict.end(); it++)
    {
        it->second = nullptr;
    }
    m_MapDict.clear();
}
