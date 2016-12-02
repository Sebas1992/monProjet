#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoord;

out vec2 texCoord0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    texCoord0 = vec2(texCoord.x, 1-texCoord.y);
}
