#SHADER VERTEX
#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec4 vertex_color;
layout(location = 3) in vec3 vertex_ambientReflectivity;
layout(location = 4) in vec3 vertex_diffuseReflectivity;
layout(location = 5) in vec4 vertex_specularReflectivity;

out vec3 position;
out vec3 normal;
out vec4 color;
out vec3 ambientReflectivity;
out vec3 diffuseReflectivity;
out vec4 specularReflectivity;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
    vec4 tempPosition = view * model * vec4(vertex_position, 1.0);
    gl_Position = projection * tempPosition;
    position = tempPosition.xyz;
    normal = vec3(view * model * vec4(vertex_normal, 0.0));
    color = vertex_color;
    ambientReflectivity = vertex_ambientReflectivity;
    diffuseReflectivity = vertex_diffuseReflectivity;
    specularReflectivity = vertex_specularReflectivity;
}

#SHADER FRAGMENT
#version 460

in vec3 position;
in vec3 normal;
in vec4 color;
in vec3 ambientReflectivity;
in vec3 diffuseReflectivity;
in vec4 specularReflectivity;

layout(location = 0) out vec4 frag_color;

uniform vec3 lightPosition;
uniform vec3 ambientLightColor;
uniform vec3 diffuseLightColor;
uniform vec3 specularLightColor;

void main()
{
    vec3 ambientColor = ambientLightColor * ambientReflectivity;
    frag_color = vec4(ambientColor, 1.0);
}