#version 330 core

layout (location = 0) in vec2 aPos;   // quad definido em [0,1] (não [-1,1]!)
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

uniform vec2 position;
uniform vec2 scale;
uniform float rotation;
uniform mat4 projection;

void main()
{
    vec2 centered = (aPos - 0.5) * scale;

    mat2 rot = mat2(cos(rotation), -sin(rotation),
                    sin(rotation),  cos(rotation));
    vec2 rotated = rot * centered;

    vec2 translated = rotated + position;

    gl_Position = projection * vec4(translated, 0.0, 1.0);

    TexCoord = aTex;
}