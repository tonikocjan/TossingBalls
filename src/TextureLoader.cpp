#include "TextureLoader.h"

#include <OpenGl/gl.h>
#include <IL/devil_cpp_wrapper.hpp>

using namespace std;

TextureLoader::texture TextureLoader::textures;

uint32 TextureLoader::LoadTex(const string& path) {
	// �e je ta tekstura �e nalo�ena vrne njen id
	for(tex_iter i = textures.begin(); i != textures.end(); ++i) {
		if((*i).first == path) return (*i).second;
	}

	ILuint imageID;				// Create an image ID as a ULuint
	GLuint textureID;			// Create a texture ID as a GLuint
	ILboolean success;		// Create a flag to keep track of success/failure
	ILenum error;			// Create a flag to keep track of the IL error state
	ilGenImages(1, &imageID); 		// Generate the image ID
	ilBindImage(imageID); 			// Bind the image
	success = ilLoadImage(path.c_str()); 	// Load the image file
	// If we managed to load the image, then we can start to do things with it...
	if (success) {
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
			iluFlipImage();
		}

		// Convert the image into a suitable format to work with
		// NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		// Quit out if we failed the conversion
		if (!success) {
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error
					<< " - " << iluErrorString(error) << std::endl;
			return -1;
		}

		// Generate a new texture
		glGenTextures(1, &textureID);

		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
				0,		// Pyramid level (for mip-mapping) - 0 is the top level
				ilGetInteger(IL_IMAGE_FORMAT),// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
				ilGetInteger(IL_IMAGE_WIDTH),	// Image width
				ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
				0,				// Border width in pixels (can either be 1 or 0)
				ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
				GL_UNSIGNED_BYTE,		// Image data type
				ilGetData());			// The actual image data itself
	} else // If we failed to open the image file in the first place...
	{
		error = ilGetError();
		std::cout << "Image load failed - IL reports error: " << error << " - "
				<< iluErrorString(error) << " File: " << path << std::endl;
		return -1;
	}

	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

	std::cout << "Texture: " << path << " successfuly loaded!" << std::endl;

	textures[path] = textureID;

	return textureID; // Return the GLuint to the texture so you can use it!
}
