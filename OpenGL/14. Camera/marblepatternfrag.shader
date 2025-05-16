//------ Marble Pattern -------

#version 330 core
out vec4 FragColor;

in vec4 c1;
in vec4 c2;
in vec2 TexCoord;

uniform float time;

void main()
{
    // Distort the texture coordinates to create a marble effect
    vec2 coord = TexCoord * 10.0;
    float marble = sin(coord.x + sin(coord.y + time) * 2.0);

    // Map the result to colors
    // vec3 color1 = vec3(0.8, 0.8, 0.8); // Light gray
    // vec3 color2 = vec3(0.1, 0.1, 0.1); // Dark gray

    vec4 finalColor = mix(c1, c2, marble);
    FragColor = finalColor;
}