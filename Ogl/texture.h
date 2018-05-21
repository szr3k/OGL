#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
 


class Texture
{
public:
	// Program ID
	unsigned int texture;


//../res/container.png


	// constructor reads and bulds the shader
	Texture::Texture(const char* filename, const bool flip)
	{

		
	
		unsigned int texture1;
		int width, height, nrChannels;

		// Generate Textures
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// load and generate the texture
		stbi_set_flip_vertically_on_load(flip);
		unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data); 
		texture = texture1;
	}
	



};


#endif