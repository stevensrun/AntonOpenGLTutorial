#SHADER VERTEX
#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;

void main() 
{
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
    color = vertex_color;
}

#SHADER FRAGMENT
#version 460

in vec3 color;

layout(location = 0) out vec4 frag_color;

void main() 
{
    frag_color = vec4(color, 1.0);
}