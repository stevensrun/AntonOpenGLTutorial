#SHADER VERTEX
#version 460

layout(location = 0) in vec3 vp;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(vp, 1.0);
}

#SHADER FRAGMENT
#version 460

uniform vec4 u_color;

layout(location = 0) out vec4 color;

void main() {
    color = u_color;
}