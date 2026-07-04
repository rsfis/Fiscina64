#version 330 core

in vec2  TexCoords;
in vec3  DiffuseLightning;
out vec4 FragColor;

uniform sampler2D tex;

void main(){
	vec4 baseColor = texture(tex, TexCoords);
	if (baseColor.a < 0.1){
		discard;
	}
	FragColor = baseColor * vec4(DiffuseLightning, 1.0f);
}