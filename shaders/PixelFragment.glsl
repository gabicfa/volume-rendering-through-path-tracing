#version 410 core

layout(location=0) out vec4 fragColour;

in vec3 pixelColour;

void main()
{
    fragColour=vec4(pixelColour, 1.0);
}