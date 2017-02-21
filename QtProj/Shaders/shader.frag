#version 430 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{    
    color = texture(texture_diffuse1, TexCoords);
    //color = vec4(TexCoords, 1.0f, 1.0f);
}