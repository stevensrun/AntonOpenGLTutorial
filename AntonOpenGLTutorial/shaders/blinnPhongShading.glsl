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
    position = tempPosition.xyz;
    normal = vec3(inverse(transpose(model)) * vec4(vertex_normal, 0.0));
    gl_Position = projection * view * tempPosition;
}

#SHADER FRAGMENT
#version 460

in vec3 position;
in vec3 normal;

layout(location = 0) out vec4 frag_color;

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
    vec3 unitLengthNormal = normalize(normal);
    vec3 ambientIntensity = ambientLightColor * ambientReflectivity;
    vec3 lightDirection = normalize(lightPosition - position);
    float diffuseFactor = max(dot(lightDirection, unitLengthNormal), 0.0);
    vec3 diffuseIntensity = diffuseLightColor * diffuseReflectivity * diffuseFactor;
    vec3 specularIntensity = vec3(0.0, 0.0, 0.0);

    if (diffuseFactor > 0.0)
    {
        vec3 cameraDirection = normalize(cameraPosition - position);
        vec3 halfWay = normalize(lightDirection + cameraDirection);
        float specularFactor = max(dot(halfWay, unitLengthNormal), 0.0);
        specularIntensity = specularLightColor * specularReflectivity.rgb * pow(specularFactor, specularReflectivity.a);
    }

    frag_color = vec4(ambientIntensity + diffuseIntensity + specularIntensity, 1.0);
}