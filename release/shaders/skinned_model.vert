#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in uvec4 aJoints;
layout (location = 4) in vec4 aWeights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 finalBones[128];

uniform vec3  LightDirection;
uniform vec3  LightColor;
uniform float LightIntensity;
uniform float AmbientLightIntensity;
uniform vec3  AmbientLightColor;

out vec2 TexCoords;
out vec3 DiffuseLightning;

void main() {
    mat4 skinMatrix =
        aWeights.x * finalBones[aJoints.x] +
        aWeights.y * finalBones[aJoints.y] +
        aWeights.z * finalBones[aJoints.z] +
        aWeights.w * finalBones[aJoints.w];

    vec4 skinnedPosition = skinMatrix * vec4(aPos, 1.0);
    TexCoords = aUV;
    gl_Position = projection * view * model * skinnedPosition;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * aNormal);
	vec3 lightDir = normalize(-LightDirection);

	float diff = max(dot(normal, lightDir), 0.0f);
	DiffuseLightning = (vec3(AmbientLightIntensity) * AmbientLightColor) + vec3(diff) * LightColor * LightIntensity;
}