#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 customColor;
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);//vec4(customColor, 1.0);//ourColor, 1.0);
}