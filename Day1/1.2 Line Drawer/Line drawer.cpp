//Line drawer.cpp RamiWailShoula

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
vector<vec3> positions;
vector<int> stops = { 0 };
bool _canDraw = false;

void onMouseMove(int x, int y) {
    if (_canDraw)
    {
        positions.push_back(vec3((x / 250.0f) - 1, 1 - (y / 250.0f), 0));
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);
    }
}

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
    glLineWidth(5);

    GLuint bufferID;

    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
    glEnableVertexAttribArray(0);

}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < stops.size() - 1; i++)
    {
        glDrawArrays(GL_LINE_STRIP, stops[i], stops[i + 1] - stops[i]);
    }
    glDrawArrays(GL_LINE_STRIP, stops[stops.size() - 1], positions.size() - stops[stops.size() - 1]);

}

//Main

int main() {
    //show command indow
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::RenderWindow window(sf::VideoMode(600, 600), "Line drawer");// , sf::Style::Close);
    //window.setVerticalSyncEnabled(true);

    //window.setActive(true);
    Init();
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        cout << "glew error";
        return 0;
    }

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

            case sf::Event::MouseButtonReleased:
                _canDraw = false;
                stops.push_back(positions.size());
                break;

            case sf::Event::MouseButtonPressed:
                _canDraw = true;
                stops.push_back(positions.size());
                break;

            case sf::Event::MouseMoved:
                onMouseMove(event.mouseMove.x, event.mouseMove.y);
                break;
            }
        }
        glUseProgram(shaderID);
        Render();
        window.display();
    }
    return 0;
}