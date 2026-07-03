#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec4 color;

void main() {
    float alpha = texture(text, TexCoords).r; // FreeType atlas stores grayscale in RED channel
    FragColor = vec4(color.rgb, color.a * alpha);
}