#include <iostream>
#include "IO.h"
using namespace std;
using namespace rapidxml;

bool IO::loadGUIFromXML(vector<gEntity*>& gui, const string& path, Camera* camera, float scaleFactor) {
	xml_document<> doc;
	xml_node<> * root_node;

	ifstream xml (path.c_str());
	string ext = path.substr(path.size() - 3, 3);
	if(!xml.is_open() ||  ext != "xml") return false;

	vector<char> buffer((istreambuf_iterator<char>(xml)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("Level");

	// iteracija �ez objekte
	for(xml_node<> * object = root_node->first_node("Object"); object; object = object->next_sibling()) {
		int x = atoi(object->first_attribute("Position-x")->value()) * scaleFactor;
		int y = atoi(object->first_attribute("Position-y")->value());
		int z = 5;
		if(object->first_attribute("Position-z") != 0)
			z = atoi(object->first_attribute("Position-z")->value());

		y = 600 - y;

		int w = atoi(object->first_attribute("Width")->value()) * scaleFactor;
		int h = atoi(object->first_attribute("Height")->value()) * scaleFactor;

		b2Vec2 pos(x, y)/*  = camera->screenToWorld(x, y)*/;
		b2Vec2 size(w, h)/* = camera->screenToWorld(w, h)*/;

		string t = object->first_attribute("Image")->value();
		uint32 tex = TextureLoader::LoadTex("data/images/" + t);

		int type = atoi(object->first_attribute("ObjectType")->value());

		gEntity* e;
		if(type == 6)
			e = new gButton(pos.x, pos.y, z, size.x, size.y, tex);
		else if (type == 3) {
			e = new TBSprite(pos.x, pos.y, z, size.x, size.y, tex);
		}
		if(e) {
			gui.push_back(e);
		}
	}

	return true;
}

bool IO::loadLevelFromXML(TBWorld& world, const string& path, Camera* camera, int& c) {
	xml_document<> doc;
	xml_node<> * root_node;

	ifstream xml (path.c_str());

	string ext = path.substr(path.size() - 3, 3);
	if(!xml.is_open() ||  ext != "xml") return false;

	vector<char> buffer((istreambuf_iterator<char>(xml)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("Level");

	// iteracija �ez objekte
	for(xml_node<> * object = root_node->first_node("Object"); object; object = object->next_sibling()) {
		int x = atoi(object->first_attribute("Position-x")->value());
		int y = atoi(object->first_attribute("Position-y")->value());

		y = 700 - y;
		x = x + 1000;

		int w = atoi(object->first_attribute("Width")->value());
		int h = atoi(object->first_attribute("Height")->value());

		b2Vec2 pos  = camera->screenToWorld(x, y);
		b2Vec2 size = camera->screenToWorld(w, h);

		int type = atoi(object->first_attribute("ObjectType")->value());
		int shape = atoi(object->first_attribute("ShapeType")->value());

		string t = object->first_attribute("Image")->value();
		string t2 = object->first_attribute("CollisionImage")->value();

		bool dynamic = (object->first_attribute("Dynamic")->value() == "False") ? false : true;

		string sound = "";
		xml_attribute<>* a = object->first_attribute("OnImpactSound");
		// nalo�imo zvok v ram
		if(a) {
			sound = string(a->value());
//			SoundSample::LoadSound("data/sounds/" + sound);
		}

		uint32 tex  = TextureLoader::LoadTex("data/images/" + t);
		uint32 tex2 = TextureLoader::LoadTex("data/images/" + t2);

		if(type == EBT_sprite) {
			world.createSprite(x, y, 2, w, h, 0, tex);
		}
		else if(shape == EST_rect) {
			TBBody* b = world.createBox(pos.x, pos.y, 2, size.x, size.y, type, tex, tex2, dynamic);
			b->setOnImpactSound(sound);
		}
		else if(shape == EST_circle) {
			TBBody* b = world.createSphere(pos.x, pos.y, 2, size.x, size.y, type, tex, tex2, dynamic);
			b->setOnImpactSound(sound);
		}
	}

	return true;
}

void IO::CreateLogFile() {
	ofstream fs;
	fs.open("log.html", ios_base::out);
	fs << "<html>" << endl <<
	"<head>" << endl <<
	"<title>Tossing Balls - Log</title><link rel=\"stylesheet\" type\"text/css\" href=\"style/log.css\">" << endl <<
	"<link href=\"http://fonts.googleapis.com/css?family=Droid+Serif\" rel=\"stylesheet\" type=\"text/css\">" << endl <<
	"<link href=\"http://fonts.googleapis.com/css?family=Droid+Sans\" rel=\"stylesheet\" type=\"text/css\">" << endl <<
	"</head>" << endl <<
	"<body>" << endl <<
	"<h1>Tossing Balls - log: </h1>" << endl
	<< CurrentTimeAndDate() << endl <<
	"<br />" << endl;
	fs.close();
}

void IO::AppendToLogFile(const string& text) {
	ofstream fs;
	fs.open("log.html", ios_base::app);
	fs << "<li>" << text << "</li>\n";
	fs.close();
}

void IO::DeleteLogFile() {
	ofstream fs;
	fs.open("log.html", ios_base::app);
	fs << "<hr>" << endl << "</body>" << endl << "</html>";
	//remove("log.html");
}

map<string, float> IO::LoadCfg() {
	ifstream is("config.ini");
	map<string, float> cfg;

	if(is.is_open()) {
		while(!is.eof()) {
			string line;
			getline(is, line);
			vector<string> data = split(line, '=');
			cfg[data[0]] = atof(data[1].c_str());
		}
	}

	return cfg;
}

