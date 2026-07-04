#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D videoTex;

void main() {
    vec4 color = texture(videoTex, TexCoord);
    FragColor = vec4(color.rgb, 1.0); // força alpha visível
}