#include "MapParser.h"
#include<bits/stdc++.h>
#include "Engine.h"
#include "Menustage.h"
using namespace std;
MapParser* MapParser::s_Instance = nullptr;

void MapParser::Load() {
	if (Engine::GetInstance()->GetMenu()->GetStory()) {
		if (Engine::GetInstance()->GetMap1()) loadmap = ListMap[0];
		else if (Engine::GetInstance()->GetMap2()) loadmap = ListMap[1];

	}
	if (Engine::GetInstance()->GetMenu()->GetPK()) {
		loadmap = ListMap[2];
	}
	if (!Parse("MAP", "assets/maps/" + loadmap)) {
		cout << "Failed to load" << endl;
	}
}

bool MapParser::Parse(string id, string source) {

	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		cerr << "Failed to Load: " << source << endl;
		return false;
	}
	TiXmlElement* root = xml.RootElement();
	int rowcount, colcount, tilesize = 0;

	root->Attribute("width", &colcount);
	root->Attribute("height", &rowcount);
	root->Attribute("tilewidth", &tilesize);

	//Paser Tilesets
	TilesetList tilesets;

	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}

	// Paser Layer
	GameMap* gamemap= new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("layer")) {
			TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayers.push_back(tilelayer);
		}
	}

	m_MapDict[id] = gamemap;
	return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
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

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {

	TiXmlElement* data  = nullptr;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == string("data")) {
			data = e;
			break;
		}
	}

	//Parse Layer tile map
	string matrix(data->GetText());
	stringstream iss(matrix);
	string id;

	TileMap tilemap(rowcount, vector <int>(colcount, 0));
	for (int row = 0; row < rowcount; row++) {
		for (int col = 0; col < colcount; col++) {
			getline(iss, id, ',');
			stringstream convertor(id);
			convertor >> tilemap[row][col];
			if (!iss.good()) break;
		}
	}

	return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

void MapParser::Clean() {
	map<string, GameMap*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
		it->second = nullptr;
	}
	m_MapDict.clear();
}
