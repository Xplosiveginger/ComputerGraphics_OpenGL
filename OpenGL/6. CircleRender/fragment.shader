#version 330 core

out vec4 FragColor;
in vec3 fCol;

uniform float timeT;

void main()
{
	FragColor = vec4(fCol.x * timeT, fCol.y * sin(timeT) * (fCol.x / fCol.z), (fCol.z + fCol.y) * cos(timeT + fCol.z), 1.0);
}