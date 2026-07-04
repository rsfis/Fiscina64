#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3  LightDirection;
uniform vec3  LightColor;
uniform float LightIntensity;
uniform float AmbientLightIntensity;
uniform vec3  AmbientLightColor;

out vec2 TexCoords;
out vec3 DiffuseLightning;

void main(){
	TexCoords = aUV;
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * aNormal);
	vec3 lightDir = normalize(-LightDirection);

	float diff = max(dot(normal, lightDir), 0.0f);
	DiffuseLightning = (vec3(AmbientLightIntensity) * AmbientLightColor) + vec3(diff) * LightColor * LightIntensity;
}