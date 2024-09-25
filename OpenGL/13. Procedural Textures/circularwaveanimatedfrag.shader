//------- Circular Wave Pattern (Animated) --------

#version 330 core
out vec4 FragColor;

in vec4 c1;
in vec4 c2;
in vec2 TexCoord;

uniform float time;

void main()
{
    // Calculate distance from the center
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(TexCoord, center);

    // Create circular waves based on distance and time
    float wave = sin(dist * 40.0 - time * 5.0);

    // Color pattern
    vec3 color1 = vec3(0.0, 1.0, 1.0); // Cyan
    vec3 color2 = vec3(0.0, 0.0, 0.0); // Black

    vec4 finalColor = mix(c1, c2, wave);
    FragColor = finalColor;
}