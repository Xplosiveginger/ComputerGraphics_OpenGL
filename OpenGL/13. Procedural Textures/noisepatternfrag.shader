//------- Noise-Like Pattern ---------

#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float time;

// Simple hash function for noise generation
float hash(vec2 p) {
    return fract(sin(dot(p ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    // Scale texture coordinates for finer noise
    vec2 scaledCoord = TexCoord * 10.0;

    // Calculate noise by hashing the texture coordinates
    float noiseValue = hash(scaledCoord + time);

    // Use noise value to generate color
    vec3 finalColor = vec3(noiseValue);

    FragColor = vec4(finalColor, 1.0);
}