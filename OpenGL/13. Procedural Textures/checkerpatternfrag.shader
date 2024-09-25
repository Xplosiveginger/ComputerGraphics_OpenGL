//------ Checker Pattern ------

#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

in vec4 c1;
in vec4 c2;
uniform float time; // Time uniform for potential animation

void main()
{
    // Procedural checkerboard texture
    float scale = 10.0; // Controls the size of the checkers
    float checker = mod(floor(TexCoord.x * scale) + floor(TexCoord.y * scale), 2.0);

    // Alternate colors for the checkers
    // vec3 color1 = vec3(1.0, 0.5, 0.0); // Orange
    // vec3 color2 = vec3(0.2, 0.2, 0.2); // Dark gray

    // Mix between the two colors based on checker pattern
    vec4 finalColor = mix(c1, c2, checker);

    FragColor = finalColor; // Output final color with full opacity
}