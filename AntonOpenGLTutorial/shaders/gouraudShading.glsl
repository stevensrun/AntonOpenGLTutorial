#SHADER VERTEX
#version 460

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec3 ambientLightColor;
uniform vec3 diffuseLightColor;
uniform vec3 specularLightColor;
uniform vec3 ambientReflectivity;
uniform vec3 diffuseReflectivity;
uniform vec4 specularReflectivity;

void main()
{
    vec4 position = model * vec4(vertex_position, 1.0);
    vec3 incidentRay = normalize(position.xyz - lightPosition);
    vec3 normal = vec3(inverse(transpose(model)) * vec4(vertex_normal, 0.0f));
    vec3 unitLengthNormal = normalize(normal);
    float diffuseFactor = max(dot(-incidentRay, unitLengthNormal), 0.0);
    vec3 ambientIntensity = ambientLightColor * ambientReflectivity;
    vec3 diffuseIntensity = diffuseLightColor * diffuseReflectivity * diffuseFactor;
    vec3 specularIntensity = vec3(0.0, 0.0, 0.0);

    if (diffuseFactor > 0.0)
    {
        vec3 reflectionRay = reflect(incidentRay, unitLengthNormal);
        vec3 cameraRay = normalize(cameraPosition - position.xyz);
        float specularFactor = max(dot(cameraRay, reflectionRay), 0.0);
        specularIntensity = specularLightColor * specularReflectivity.rgb * pow(specularFactor, specularReflectivity.a);
    }

    color = vec4(ambientIntensity + diffuseIntensity + specularIntensity, 1.0);
    gl_Position = projection * view * position;
}

#SHADER FRAGMENT
#version 460

in vec4 color;

out vec4 frag_color;

void main()
{
    frag_color = color;
}