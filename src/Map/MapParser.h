#ifndef MAPPARSER_H
#define MAPPARSER_H
#include<bits/stdc++.h>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"
using namespace std;
class MapParser {
	public:
		void Load();
		void Clean();

		inline GameMap* GetMap(string id) { return m_MapDict[id]; };
		inline static MapParser* GetInstance() {
			if (s_Instance != nullptr)
				return s_Instance;
			else
				return s_Instance = new MapParser();
		}

	private:
		bool Parse(string id, string source);
		Tileset ParseTileset(TiXmlElement* xmlTileset);
		TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

	private:
		MapParser() {
			ListMap.push_back("map1.tmx");
			ListMap.push_back("map2.tmx");
			ListMap.push_back("map3.tmx");
			Completemap1 = false;
		};
		static MapParser* s_Instance;
		map<string, GameMap*> m_MapDict;
		vector<string> ListMap;
		bool Completemap1;
		string loadmap;
};

#endif
