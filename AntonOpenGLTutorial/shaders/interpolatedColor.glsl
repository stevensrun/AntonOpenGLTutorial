#SHADER VERTEX
#version 460

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;

out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    gl_Position = projection * view * model * vertex_position;
    color = vertex_color;
}

#SHADER FRAGMENT
#version 460

in vec4 color;

layout(location = 0) out vec4 frag_color;

void main() 
{
    frag_color = color;
}