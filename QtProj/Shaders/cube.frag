#version 330 core
in  vec3 _color;
out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{    
    //color = texture(texture_diffuse1, TexCoords);
    color = vec4(_color, 1.0f);
}