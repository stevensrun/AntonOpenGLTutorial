#SHADER VERTEX
#version 460

layout(location = 0) in vec3 vertex_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}

#SHADER FRAGMENT
#version 460

layout(location = 0) out vec4 frag_color;

uniform vec3 ambientReflectivity;

void main()
{
    frag_color = vec4(ambientReflectivity, 1.0);
}