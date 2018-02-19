#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Vertex and Fragment Shaders")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
} Vertex;

Vertex vertex[36];
GLubyte triangles[6];

/* Variable to hold the VBO identifier and shader data */
GLuint	index, //Index to draw
		vsid, //Vertex Shader ID
		fsid, //Fragment Shader ID
		progID, //Program ID
		vao = 0, //Vertex Array ID
		vbo[1], // Vertex Buffer ID
		positionID, //Position ID
		colorID; // Color ID


void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = -0.2f;
	vertex[0].coordinate[1] = -0.2f;
	vertex[0].coordinate[2] = 0.0f;

	vertex[1].coordinate[0] = -0.2f;
	vertex[1].coordinate[1] = 0.2f;
	vertex[1].coordinate[2] = 0.0f;

	vertex[2].coordinate[0] = 0.2f;
	vertex[2].coordinate[1] = 0.2f;
	vertex[2].coordinate[2] = 0.0f;

	vertex[3].coordinate[0] = 0.2f;
	vertex[3].coordinate[1] = 0.2f;
	vertex[3].coordinate[2] = 0.0f;

	vertex[4].coordinate[0] = 0.2f;
	vertex[4].coordinate[1] = -0.2f;
	vertex[4].coordinate[2] = 0.0f;

	vertex[5].coordinate[0] = -0.2f;
	vertex[5].coordinate[1] = -0.2f;
	vertex[5].coordinate[2] = 0.0f;

	vertex[6].coordinate[0] = 0.2f;
	vertex[6].coordinate[1] = -0.2f;
	vertex[6].coordinate[2] = 0.0f;

	vertex[7].coordinate[0] = 0.2f;
	vertex[7].coordinate[1] = 0.2f;
	vertex[7].coordinate[2] = 0.0f;

	vertex[8].coordinate[0] = 0.2f;
	vertex[8].coordinate[1] = 0.2f;
	vertex[8].coordinate[2] = 0.2f;

	vertex[9].coordinate[0] = 0.2f;
	vertex[9].coordinate[1] = 0.2f;
	vertex[9].coordinate[2] = 0.2f;

	vertex[10].coordinate[0] = 0.2f;
	vertex[10].coordinate[1] = -0.2f;
	vertex[10].coordinate[2] = 0.2f;

	vertex[11].coordinate[0] = 0.2f;
	vertex[11].coordinate[1] = -0.2f;
	vertex[11].coordinate[2] = 0.0f;

	vertex[12].coordinate[0] = 0.2f;
	vertex[12].coordinate[1] = -0.2f;
	vertex[12].coordinate[2] = 0.2f;

	vertex[13].coordinate[0] = 0.2f;
	vertex[13].coordinate[1] = 0.2f;
	vertex[13].coordinate[2] = 0.2f;

	vertex[14].coordinate[0] = -0.2f;
	vertex[14].coordinate[1] = 0.2f;
	vertex[14].coordinate[2] = 0.2f;

	vertex[15].coordinate[0] = -0.2f;
	vertex[15].coordinate[1] = 0.2f;
	vertex[15].coordinate[2] = 0.2f;

	vertex[16].coordinate[0] = -0.2f;
	vertex[16].coordinate[1] = -0.2f;
	vertex[16].coordinate[2] = 0.2f;

	vertex[17].coordinate[0] = 0.2f;
	vertex[17].coordinate[1] = -0.2f;
	vertex[17].coordinate[2] = 0.2f;

	vertex[18].coordinate[0] = -0.2f;
	vertex[18].coordinate[1] = -0.2f;
	vertex[18].coordinate[2] = 0.2f;

	vertex[19].coordinate[0] = -0.2f;
	vertex[19].coordinate[1] = 0.2f;
	vertex[19].coordinate[2] = 0.2f;

	vertex[20].coordinate[0] = -0.2f;
	vertex[20].coordinate[1] = 0.2f;
	vertex[20].coordinate[2] = 0.0f;

	vertex[21].coordinate[0] = -0.2f;
	vertex[21].coordinate[1] = 0.2f;
	vertex[21].coordinate[2] = 0.0f;

	vertex[22].coordinate[0] = -0.2f;
	vertex[22].coordinate[1] = -0.2f;
	vertex[22].coordinate[2] = 0.0f;

	vertex[23].coordinate[0] = -0.2f;
	vertex[23].coordinate[1] = -0.2f;
	vertex[23].coordinate[2] = 0.2f;

	vertex[24].coordinate[0] = -0.2f;
	vertex[24].coordinate[1] = 0.2f;
	vertex[24].coordinate[2] = 0.0f;

	vertex[25].coordinate[0] = -0.2f;
	vertex[25].coordinate[1] = 0.2f;
	vertex[25].coordinate[2] = 0.2f;

	vertex[26].coordinate[0] = 0.2f;
	vertex[26].coordinate[1] = 0.2f;
	vertex[26].coordinate[2] = 0.2f;

	vertex[27].coordinate[0] = 0.2f;
	vertex[27].coordinate[1] = 0.2f;
	vertex[27].coordinate[2] = 0.2f;

	vertex[28].coordinate[0] = 0.2f;
	vertex[28].coordinate[1] = 0.2f;
	vertex[28].coordinate[2] = 0.0f;

	vertex[29].coordinate[0] = -0.2f;
	vertex[29].coordinate[1] = 0.2f;
	vertex[29].coordinate[2] = 0.0f;

	vertex[30].coordinate[0] = -0.2f;
	vertex[30].coordinate[1] = -0.2f;
	vertex[30].coordinate[2] = 0.2f;

	vertex[31].coordinate[0] = -0.2f;
	vertex[31].coordinate[1] = -0.2f;
	vertex[31].coordinate[2] = 0.0f;

	vertex[32].coordinate[0] = 0.2f;
	vertex[32].coordinate[1] = -0.2f;
	vertex[32].coordinate[2] = 0.0f;

	vertex[33].coordinate[0] = 0.2f;
	vertex[33].coordinate[1] = -0.2f;
	vertex[33].coordinate[2] = 0.0f;

	vertex[34].coordinate[0] = 0.2f;
	vertex[34].coordinate[1] = -0.2f;
	vertex[34].coordinate[2] = 0.2f;

	vertex[35].coordinate[0] = -0.2f;
	vertex[35].coordinate[1] = -0.2f;
	vertex[35].coordinate[2] = 0.2f;

	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.7f;
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[7].color[0] = 0.8f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	vertex[8].color[0] = 0.9f;
	vertex[8].color[1] = 1.0f;
	vertex[8].color[2] = 0.0f;

	vertex[9].color[0] = 1.0f;
	vertex[9].color[1] = 1.0f;
	vertex[9].color[2] = 0.0f;

	vertex[10].color[0] = 1.0f;
	vertex[10].color[1] = 0.0f;
	vertex[10].color[2] = 0.1f;

	vertex[11].color[0] = 1.0f;
	vertex[11].color[1] = 0.0f;
	vertex[11].color[2] = 0.2f;

	vertex[12].color[0] = 1.0f;
	vertex[12].color[1] = 0.0f;
	vertex[12].color[2] = 0.3f;

	vertex[13].color[0] = 1.0f;
	vertex[13].color[1] = 0.0f;
	vertex[13].color[2] = 0.4f;

	vertex[14].color[0] = 1.0f;
	vertex[14].color[1] = 0.0f;
	vertex[14].color[2] = 0.5f;

	vertex[15].color[0] = 1.0f;
	vertex[15].color[1] = 0.0f;
	vertex[15].color[2] = 0.6f;

	vertex[16].color[0] = 1.0f;
	vertex[16].color[1] = 0.0f;
	vertex[16].color[2] = 0.7f;

	vertex[17].color[0] = 1.0f;
	vertex[17].color[1] = 0.0f;
	vertex[17].color[2] = 0.8f;

	vertex[18].color[0] = 1.0f;
	vertex[18].color[1] = 0.0f;
	vertex[18].color[2] = 0.9f;

	vertex[19].color[0] = 1.0f;
	vertex[19].color[1] = 0.0f;
	vertex[19].color[2] = 1.0f;

	vertex[20].color[0] = 0.0f;
	vertex[20].color[1] = 1.0f;
	vertex[20].color[2] = 0.1f;

	vertex[21].color[0] = 0.0f;
	vertex[21].color[1] = 1.0f;
	vertex[21].color[2] = 0.2f;

	vertex[22].color[0] = 0.0f;
	vertex[22].color[1] = 1.0f;
	vertex[22].color[2] = 0.3f;

	vertex[23].color[0] = 0.0f;
	vertex[23].color[1] = 1.0f;
	vertex[23].color[2] = 0.4f;

	vertex[24].color[0] = 0.0f;
	vertex[24].color[1] = 1.0f;
	vertex[24].color[2] = 0.5f;

	vertex[25].color[0] = 0.0f;
	vertex[25].color[1] = 1.0f;
	vertex[25].color[2] = 0.6f;

	vertex[26].color[0] = 0.0f;
	vertex[26].color[1] = 1.0f;
	vertex[26].color[2] = 0.7f;

	vertex[27].color[0] = 0.0f;
	vertex[27].color[1] = 1.0f;
	vertex[27].color[2] = 0.8f;

	vertex[28].color[0] = 0.0f;
	vertex[28].color[1] = 1.0f;
	vertex[28].color[2] = 0.9f;

	vertex[29].color[0] = 0.0f;
	vertex[29].color[1] = 1.0f;
	vertex[29].color[2] = 1.0f;

	vertex[30].color[0] = 0.0f;
	vertex[30].color[1] = 0.1f;
	vertex[30].color[2] = 1.0f;

	vertex[31].color[0] = 0.0f;
	vertex[31].color[1] = 0.2f;
	vertex[31].color[2] = 1.0f;

	vertex[32].color[0] = 0.0f;
	vertex[32].color[1] = 0.3f;
	vertex[32].color[2] = 1.0f;

	vertex[33].color[0] = 0.0f;
	vertex[33].color[1] = 0.4f;
	vertex[33].color[2] = 1.0f;

	vertex[34].color[0] = 0.0f;
	vertex[34].color[1] = 3.5f;
	vertex[34].color[2] = 1.0f;

	vertex[35].color[0] = 0.0f;
	vertex[35].color[1] = 0.6f;
	vertex[35].color[2] = 1.0f;

	/*Index of Poly / Triangle to Draw */
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;
	triangles[6] = 6;   triangles[7] = 7;   triangles[8] = 8;
	triangles[9] = 9;   triangles[10] = 10;   triangles[11] = 11;
	triangles[12] = 12;   triangles[13] = 13;   triangles[14] = 14;
	triangles[15] = 15;   triangles[16] = 16;   triangles[17] = 17;
	triangles[18] = 18;   triangles[19] = 19;   triangles[20] = 20;
	triangles[21] = 21;   triangles[22] = 22;   triangles[23] = 23;
	triangles[24] = 24;   triangles[25] = 25;	  triangles[26] = 26;
	triangles[27] = 27;   triangles[28] = 28;	  triangles[29] = 29;
	triangles[30] = 30;   triangles[31] = 31;   triangles[32] = 32;
	triangles[33] = 33;	 triangles[34] = 34;   triangles[35] = 35;
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	for (int i = 0; i < 36; i++)
	{
		currentPosition[i] = Vector3D{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
	}
	for (int i = 0; i < 36; i++)
	{
		vertex[i].coordinate[0] = currentPosition[i].X();
		vertex[i].coordinate[1] = currentPosition[i].Y();
		vertex[i].coordinate[2] = currentPosition[i].Z();
	}

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"out vec4 color;"
		"void main() {"
		"	color = sv_color;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"in vec4 color;"
		"out vec4 fColor;"
		"void main() {"
		"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	//Change vertex data
	/*vertex[0].coordinate[0] += -0.0001f;
	vertex[0].coordinate[1] += -0.0001f;
	vertex[0].coordinate[2] += -0.0001f;

	vertex[1].coordinate[0] += -0.0001f;
	vertex[1].coordinate[1] += -0.0001f;
	vertex[1].coordinate[2] += -0.0001f;

	vertex[2].coordinate[0] += -0.0001f;
	vertex[2].coordinate[1] += -0.0001f;
	vertex[2].coordinate[2] += -0.0001f;*/

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
}

