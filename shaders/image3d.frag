#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform float alpha;

void main() {
    vec4 color = texture(tex, TexCoord);
    if (color.a < 0.1f){
        discard;
    }
    FragColor = vec4(color.rgb, color.a * alpha);
}