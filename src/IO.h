#pragma once

#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <exception>

#include "utility.h"
#include "entities/TBButton.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "TBWorld.h"
//#include "SoundLoader.h"
#include "TextureLoader.h"

typedef std::map<std::string, float> t_cfg;
class gEntity;

class IO {
	public:
		// nalo�i grafi�ni vmesnik iz xml
		static bool loadGUIFromXML(vector<gEntity*>& gui, const std::string& path, Camera* camera, float scaleFactor);
		// nalo�i xml level
		static bool loadLevelFromXML(TBWorld& world, const std::string& path, Camera* camera, int& c);
		// ustvari "log" datoteko
		static void CreateLogFile();
		// dodaj text na konec log datoteke
		static void AppendToLogFile(const std::string& text);
		// izbri�i log datoteko
		static void DeleteLogFile();
		// nalo�i configuracijo iz datoteke
		static std::map<std::string, float> LoadCfg();
};

