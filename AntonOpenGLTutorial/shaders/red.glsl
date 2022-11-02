#SHADERV VERTEX
#version 460

layout(location = 0) in vec3 vertex_position;

void main() 
{
    gl_Position = vec4(vertex_position, 1.0);
}

#SHADER FRAGMENT
#version 460

layout(location = 0) out vec4 frag_color;

void main() 
{
    frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}