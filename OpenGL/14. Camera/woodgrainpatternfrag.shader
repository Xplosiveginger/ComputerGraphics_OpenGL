//------- Wood Grain Pattern -------

#version 330 core
out vec4 FragColor;

in vec4 c1;
in vec4 c2;
in vec2 TexCoord;

uniform float time;

void main()
{
    // Calculate distance from the center to simulate rings
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(TexCoord, center) * 10.0;

    // Create rings by using sine of distance
    float rings = sin(dist - time);

    // Simulate wood grain by combining sine waves
    float grain = rings + 0.1 * sin(dist * 10.0);

    // Color based on wood grain effect
    // vec3 color1 = vec3(0.6, 0.4, 0.1); // Brown
    // vec3 color2 = vec3(0.4, 0.2, 0.05); // Darker brown

    vec4 finalColor = mix(c1, c2, grain);
    FragColor = finalColor;
}