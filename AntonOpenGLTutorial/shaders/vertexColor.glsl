#SHADER VERTEX
#version 460

layout (location = 0) in vec3 vertex_position;
layout (location = 2) in vec4 vertex_color;

out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    color = vertex_color;
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}

#SHADER FRAGMENT
#version 460

in vec4 color;

out vec4 frag_color;

void main()
{
    frag_color = color;
}