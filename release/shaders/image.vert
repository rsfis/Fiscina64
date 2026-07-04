#version 330 core

layout (location = 0) in vec2 aPos;   // [0,1]
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

uniform vec2 position;
uniform vec2 scale;      // multiplicador (1x, 2x…)
uniform vec2 texSize;    // (width, height) da imagem
uniform float rotation;
uniform mat4 projection;

void main()
{
    // 1) quad vira o tamanho REAL da textura (pixels)
    vec2 sizeQuad = aPos * texSize;

    // 2) centraliza em torno do meio da textura
    vec2 centered = (sizeQuad - texSize * 0.5) * scale;

    // 3) rotaciona
    mat2 rot = mat2(cos(rotation), -sin(rotation),
                    sin(rotation),  cos(rotation));

    vec2 rotated = rot * centered;

    // 4) posiciona
    vec2 translated = rotated + position;

    gl_Position = projection * vec4(translated, 0.0, 1.0);
    TexCoord = aTex;
}