//Sine wave.cpp RamiWailShoula

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include<gtx\transform.hpp>
#include<fstream>
#include<Math.h>
#include<vector>


using namespace sf;
using namespace std;
using namespace glm;

//Functions

GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);
GLuint shaderID;

vector<float> positions;

int Init()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		cout << "Error";
		getchar();
		return 1;
	}
	else
	{
		if (GLEW_VERSION_3_0)
			cout << "Driver support OpenGL 3.0\nDetails:\n";
	}
	cout << "\tUsing glew " << glewGetString(GLEW_VERSION) << endl;
	cout << "\tVendor: " << glGetString(GL_VENDOR) << endl;
	cout << "\tRenderer: " << glGetString(GL_RENDERER) << endl;
	cout << "\tVersion: " << glGetString(GL_VERSION) << endl;
	cout << "\tGLSL:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	glClearColor(1.0, 1.0, 1.0, 0.0);

	for (int i = 0; i < 1000; i++)
	{
		float x = (i - 500) / 500.0f;
		positions.push_back(x);
	}

	GLuint bufferID;

	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);

}

float shift = 0;
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_LINE_STRIP, 0, 1000);
	glVertexAttribPointer(shift, 1.0f, GL_FLOAT, GL_FALSE, sizeof(float), 0);
	//glGetUniformLocation(shaderID, "shift");
	shift += 0.001f;


}

void main()
{
	sf::Window window(sf::VideoMode(600, 600), "Sine Wave");
	Init();
	shaderID = InitShader("vShader.glsl", "fShader.glsl");

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		glUseProgram(shaderID);
		Render();
		window.display();
	}
}