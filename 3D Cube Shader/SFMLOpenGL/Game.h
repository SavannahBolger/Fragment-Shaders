#ifndef GAME_H
#define GAME_H

#include <Debug.h>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

#include "Vector3D.h"
#include "Matrix3.h"

using namespace std;
using namespace sf;
//using namespace gpp;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	bool load();
	const YAML::Node getNode();
	const char updateVertexShaders(const YAML::Node base) const;
	const char updateFragmentShaders(const YAML::Node base) const;

	Clock clock;
	Time elapsed;

	unsigned i = 0;
	Vector3D currentPosition[36];
	float rotationAngle = 0.0f;
	Matrix3 xRotation;//x axis rotation
	Matrix3 yRotation;//y axis rotation
	Matrix3 zRotation;//z axis rotation
	Vector3D activeTranslation{ 0,0,0 };
	/*std::string m_vertexShader1;
	std::string m_vertexShader2;
	std::string m_vertexShader3;
	std::string m_vertexShader4;
	std::string m_vertexShader5;
	std::string m_vertexShader6;
	std::string m_vertexShader7;
	std::string m_vertexShader8;*/

	std::string m_fragmentShader1;
	std::string m_fragmentShader2;
	std::string m_fragmentShader3;
	std::string m_fragmentShader4;
	std::string m_fragmentShader5;
	std::string m_fragmentShader6;
};

#endif