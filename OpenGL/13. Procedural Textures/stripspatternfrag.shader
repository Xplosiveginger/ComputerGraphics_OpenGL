//------ Strips Pattern --------

#version 330 core
out vec4 FragColor;

in vec4 c1;
in vec4 c2;
in vec2 TexCoord;

uniform float time; // Time uniform for animation

void main()
{
    // Stripes along the x-axis
    float stripes = abs(sin(TexCoord.x * 20.0 + time));

    // Alternate between two colors based on the stripe intensity
    // vec3 color1 = vec3(0.0, 0.0, 1.0); // Blue
    // vec3 color2 = vec3(1.0, 1.0, 1.0); // White

    vec4 finalColor = mix(c1, c2, stripes);
    FragColor = finalColor;
}