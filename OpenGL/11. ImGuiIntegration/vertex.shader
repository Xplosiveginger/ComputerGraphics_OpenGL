#version 330 core

layout (location = 0) in vec3 aPos;

uniform float size;
uniform vec4 color;
out vec4 ourColor;

void main()
{
    gl_Position = vec4(aPos * size, 1.0);
    ourColor = color;
}