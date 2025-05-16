//-------- Radial Gradient Pattern -------

#version 330 core
out vec4 FragColor;

in vec4 c1;
in vec4 c2;
in vec2 TexCoord;
uniform float mul;

uniform float time;

void main()
{
    // Calculate distance from the center (0.5, 0.5)
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(TexCoord, center);

    // Create a radial gradient based on the distance
    // vec3 color1 = vec3(0.0, 0.0, 1.0); // Blue at center
    // vec3 color2 = vec3(1.0, 1.0, 1.0); // White at edges

    vec4 finalColor = mix(c1, c2, dist * mul);
    FragColor = finalColor;
}