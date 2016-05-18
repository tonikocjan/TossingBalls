#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_
#include <string>
#include <map>
#include <iostream>
#include "SOIL.h"

typedef unsigned int uint32;

class TextureLoader {
	public:
		static uint32 LoadTex(const std::string& path);

	private:
		typedef std::map<std::string, uint32> texture;
		typedef std::map<std::string, uint32>::iterator tex_iter;

		static texture textures;
};

#endif /* TEXTURELOADER_H_ */
