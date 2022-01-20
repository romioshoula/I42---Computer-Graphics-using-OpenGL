#version 330 core

layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 acolor;

out vec3 ourColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
void main(){
        gl_Position = perspective*view*model*  vec4(apos,1.0f);
                ourColor = acolor;

}