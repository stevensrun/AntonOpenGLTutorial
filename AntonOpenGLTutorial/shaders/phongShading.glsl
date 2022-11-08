#SHADER VERTEX
#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out vec3 position;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
    vec4 tempPosition = model * vec4(vertex_position, 1.0);
    gl_Position = projection * view * tempPosition;
    position = tempPosition.xyz;
    normal = vec3(inverse(transpose(model)) * vec4(vertex_normal, 0.0));
}

#SHADER FRAGMENT
#version 460

in vec3 position;
in vec3 normal;

layout(location = 0) out vec4 frag_color;

uniform vec3 lightPosition;
uniform vec3 ambientLightColor;
uniform vec3 diffuseLightColor;
uniform vec3 specularLightColor;
uniform vec3 cameraPosition;
uniform vec3 ambientReflectivity;
uniform vec3 diffuseReflectivity;
uniform vec4 specularReflectivity;

void main()
{
    vec3 ambientIntensity = ambientLightColor * ambientReflectivity;
    vec3 incidentRay = normalize(position - lightPosition);
    float dotProduct = dot(-incidentRay, normal);
    vec3 diffuseIntensity = diffuseLightColor * diffuseReflectivity * max(dotProduct, 0.0);
    vec3 reflectionRay = reflect(incidentRay, normal);
    vec3 cameraRay = normalize(cameraPosition - position);
    vec3 specularIntensity = specularLightColor * specularReflectivity.rgb * pow(max(dot(reflectionRay, cameraRay), 0.0), specularReflectivity.a);
    frag_color = vec4(ambientIntensity + diffuseIntensity + specularIntensity, 1.0);
}