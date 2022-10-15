#SHADERV VERTEX
#version 460

layout(location = 0) in vec3 vp;

void main() 
{
    gl_Position = vec4(vp, 1.0);
}

#SHADER FRAGMENT
#version 460

layout(location = 0) out vec4 color;

void main() 
{
    color = vec4(1.0, 0.0, 0.0, 1.0);
}