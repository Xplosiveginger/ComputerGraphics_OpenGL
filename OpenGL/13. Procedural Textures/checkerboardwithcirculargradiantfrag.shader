//------- Checkerboard with Circular Gradient -------

#version 330 core
out vec4 FragColor;

in vec4 c1;
in vec4 c2;
in vec2 TexCoord;

uniform float time;

void main()
{
    // Checkerboard pattern
    float scale = 10.0;
    float checker = mod(floor(TexCoord.x * scale) + floor(TexCoord.y * scale), 2.0);

    // Circular gradient based on distance from center
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(TexCoord, center);

    // Mix colors based on checker and radial gradient
    // vec3 color1 = vec3(0.0, 0.8, 0.2); // Green
    // vec3 color2 = vec3(0.2, 0.0, 0.5); // Purple

    vec4 finalColor = mix(c1, c2, checker * dist);
    FragColor = finalColor;
}