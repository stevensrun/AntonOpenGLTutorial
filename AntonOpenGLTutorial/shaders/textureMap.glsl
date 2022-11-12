#SHADER VERTEX
#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_textureCoordinate;

out vec3 position;
out vec3 normal;
out vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
    vec4 tempPosition = model * vec4(vertex_position, 1.0);
    gl_Position = projection * view * tempPosition;
    position = tempPosition.xyz;
    normal = vec3(inverse(transpose(model)) * vec4(vertex_normal, 0.0));
    textureCoordinate = vertex_textureCoordinate;
}

#SHADER FRAGMENT
#version 460

in vec3 position;
in vec3 normal;
in vec2 textureCoordinate;

layout(location = 0) out vec4 frag_color;

uniform sampler2D baseTexture;
uniform sampler2D secondaryTexture;

void main()
{
    vec4 baseColor = texture(baseTexture, textureCoordinate);
    vec4 secondaryColor = texture(secondaryTexture, textureCoordinate);
    frag_color = mix(baseColor, secondaryColor, 0.7);
}