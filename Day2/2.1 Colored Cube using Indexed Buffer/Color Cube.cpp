//Color Cube.cpp RamiWailShoula

//#includes
#include <iostream>
#include<vector>
#include <glew/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include<glm\glm.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<glm\gtx\transform.hpp>

using namespace std;
using namespace glm;
using namespace sf; 

//Struct Vertex declaration
struct vertex
{
	vec3 position;
	vec3 color;
	vertex() {}
	vertex(vec3 _position, vec3 _color) :position{ _position }, color{ _color }
	{
	}
	vertex(vec3 _position) :position{ _position }, color(0, 0, 0)
	{
	}
};

const GLint WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO, programId, IBO;
GLuint modelMatLoc, viewMatLoc, projMatLoc;
GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);

//Cube vertices
vertex cube_core_vertices[] = {
{vec3(-0.5, 0.5, 0.5),vec3(1,0,0)},
{vec3(-0.5, -0.5, 0.5),vec3(0,1,0) },
{vec3(0.5, -0.5, 0.5),vec3(1,0,1)},
{vec3(0.5, 0.5, 0.5),vec3(0,0,1)},
{vec3(0.5, 0.5, -0.5),vec3(1,1,0)},
{vec3(0.5, -0.5, -0.5),vec3(0,1,1)},
{vec3(-0.5, -0.5, -0.5),vec3(1,1,1)},
{vec3(-0.5, 0.5, -0.5),vec3(0,0,0)}
};

//Sphere functions
#pragma Region Sphere
vector<vertex> sphere_vertices;
vec3 Sphere_Core_vertices[4] = {
	vec3(0.0, 0.0, 1.0),
	vec3(0.0, 0.942809, -0.333333),
	vec3(-0.816497, -0.471405, -0.333333),
	vec3(0.816497, -0.471405, -0.333333)
};
void Triangle(vec3 a, vec3 b, vec3 c)
{
	vec3 color = (a + b + c) / 3.0f;
	sphere_vertices.push_back(vertex(a, a));
	sphere_vertices.push_back(vertex(b, b));
	sphere_vertices.push_back(vertex(c, c));
}
void dividTriangle(vec3 a, vec3 b, vec3 c, int itertions)
{
	if (itertions > 0)
	{
		vec3 v1 = normalize(a + b);
		vec3 v2 = normalize(a + c);
		vec3 v3 = normalize(b + c);

		dividTriangle(a, v1, v2, itertions - 1);
		dividTriangle(v1, b, v3, itertions - 1);
		dividTriangle(v1, v3, v2, itertions - 1);
		dividTriangle(v2, v3, c, itertions - 1);
	}
	else
	{
		Triangle(a, b, c);
	}
}
void CreateSphere(int iterations)
{
	sphere_vertices.clear();
	dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[1], Sphere_Core_vertices[2], iterations);
	dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[3], Sphere_Core_vertices[1], iterations);
	dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[2], Sphere_Core_vertices[3], iterations);
	dividTriangle(Sphere_Core_vertices[3], Sphere_Core_vertices[2], Sphere_Core_vertices[1], iterations);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(vertex), sphere_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (char*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

#pragma endregion 
void CreateCube()
{
#pragma region oldCube
	vertex core_positions[] = {
		{vec3(-0.5, 0.5, 0.5),                vec3(1,0,0)},
		{vec3(-0.5, -0.5, 0.5),                vec3(0,1,0)},
		{vec3(0.5, -0.5, 0.5),                vec3(0,0,1)},
		{vec3(0.5, 0.5, 0.5),                vec3(1,1,0)},
		{vec3(0.5, 0.5, -0.5),                vec3(1,0,1)},
		{vec3(0.5, -0.5, -0.5),                vec3(0,1,1)},
		{vec3(-0.5, -0.5, -0.5),		      vec3(0.5,0.5,0)},
		{vec3(-0.5, 0.5, -0.5),                vec3(1,0.5,0.5)}
	};
	GLuint indecies[] = {
		//Front
		//Quad(0, 1, 2, 3, vec3(1, 0, 0));
		0,1,2,0,2,3,
		//Right
		//Quad(3, 2, 5, 4, vec3(0, 1, 0));
		3,2,5,3,5,4,
		//Back
		//Quad(4, 5, 6, 7, vec3(0, 0, 1));
		4,5,6,4,6,7,
		//Left
		//Quad(0, 1, 6, 7, vec3(1, 1, 0));
		0,1,6,0,6,7,
		//Top
		//Quad(0, 3, 4, 7, vec3(1, 0, 1));
		0,3,4,0,4,7,
		//Bottom
		//Quad(1, 6, 5, 2, vec3(0, 1, 1));
		1,6,5,1,5,2
	};

#pragma endregion
	int vertices_Indeces[] = {
		//front
		0,
		1,
		2,

		0,
		2,
		3,
		//Right
		3,
		2,
		5,

		3,
		5,
		4,
		//Back
		4,
		5,
		6,

		4,
		6,
		7,
		//Left
		7,
		6,
		1,

		7,
		1,
		0,
		//Top
		7,
		0,
		3,

		7,
		3,
		4,
		//Bottom
		2,
		1,
		6,

		2,
		6,
		5
	};
	// create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_core_vertices), cube_core_vertices, GL_STATIC_DRAW);

	// Index Buffer
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices_Indeces), vertices_Indeces, GL_STATIC_DRAW);

	// shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (char*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void CreateTriangle()
{
	//interleaved buffer
	vertex vertices[] =
	{
		{vec3(-1,-1,0),vec3(0,1,0) },
		{vec3(1,-1,0),vec3(0,0,1)},
		{vec3(0,1,0),vec3(1,0,0)}
	};

	// create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// shader
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), ((char*)(sizeof(vec3))));
	glEnableVertexAttribArray(1);

}

void CompileShader()
{
	programId = InitShader("Vertex_S.glsl", "Frag_S.glsl");
	glUseProgram(programId);
}

float* rotateY(float theta)
{
	float* result = new float[16]();
	result[0] = cos(theta);
	result[2] = sin(theta);
	result[5] = 1;
	result[8] = -sin(theta);
	result[10] = cos(theta);
	result[15] = 1;
	return result;
}

int Init()
{
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		cout << "error";
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

	CompileShader();
	modelMatLoc = glGetUniformLocation(programId, "modelMat");
	viewMatLoc = glGetUniformLocation(programId, "viewMat");
	projMatLoc = glGetUniformLocation(programId, "projMat");


	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	return 0;

}

float theta = 0;
void Update()
{
	theta += 0.001f;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 viewMat = glm::lookAt(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));

	glm::mat4 projMat = glm::perspectiveFov(60.0f, 5.0f, 5.0f, 1.0f, 10.0f);

	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

	
	CreateCube();
	glm::mat4 ModelMat = glm::translate(glm::vec3(-0.5, 0, 0)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(0.5,0.5, 0.5));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	//CreateSphere;
	ModelMat = glm::translate(glm::vec3(0.5, 0, 5)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(1, 1, 1)) *
		glm::scale(glm::vec3(0.5, 0.5, 0.5));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

}

int main()
{
	sf::ContextSettings context;
	context.depthBits = 24;
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "Color Cube", sf::Style::Close , context);

	if (Init()) return 1;

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

		Update();
		Render();

		window.display();
	}
	return 0;
}