#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

uniform vec3 position;
uniform vec3 scale;
uniform vec3 rotation;
uniform float aspect_ratio;

uniform mat4 projection;
uniform mat4 view;

mat4 rotX(float a)
{
    float c = cos(a);
    float s = sin(a);
    return mat4(
        1, 0, 0, 0,
        0, c,-s, 0,
        0, s, c, 0,
        0, 0, 0, 1
    );
}

mat4 rotY(float a)
{
    float c = cos(a);
    float s = sin(a);
    return mat4(
         c, 0, s, 0,
         0, 1, 0, 0,
        -s, 0, c, 0,
         0, 0, 0, 1
    );
}

mat4 rotZ(float a)
{
    float c = cos(a);
    float s = sin(a);
    return mat4(
        c,-s, 0, 0,
        s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

void main()
{
    vec3 fixedScale = scale;
    fixedScale.x *= aspect_ratio;

    mat4 S = mat4(
        fixedScale.x, 0, 0, 0,
        0, fixedScale.y, 0, 0,
        0, 0, fixedScale.z, 0,
        0, 0, 0, 1
    );

    mat4 R = rotZ(rotation.z) * rotY(rotation.y) * rotX(rotation.x);

    mat4 T = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        position.x, position.y, position.z, 1
    );

    mat4 model = T * R * S;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTex;
}