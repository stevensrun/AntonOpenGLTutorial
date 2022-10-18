#SHADER VERTEX
#version 460

layout(location = 0) in vec4 vp;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vp;
}

#SHADER FRAGMENT
#version 460

uniform vec4 u_color;

layout(location = 0) out vec4 color;

void main() {
    color = u_color;
}