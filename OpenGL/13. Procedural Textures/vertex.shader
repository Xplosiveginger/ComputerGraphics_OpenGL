#version 330 core
layout(location = 0) in vec3 aVerts;// 0th attribute
layout(location = 1) in vec2 aTexCoord;// 2nd attribute

out vec4 c1;
out vec4 c2;
out vec2 TexCoord;

uniform vec4 color1;
uniform vec4 color2;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection*view*model*vec4(aVerts.x, aVerts.y, aVerts.z,1.0);
	TexCoord = aTexCoord;
	c1 = color1;
	c2 = color2;
}