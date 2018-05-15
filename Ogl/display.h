#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



class Display
{
public:
	Display();
	~Display();
	GLFWwindow* CreateNewDisplay();
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	
protected:
private:
	
	
};

#endif //DISPLAY_H

