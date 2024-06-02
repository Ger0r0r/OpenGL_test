#version 330 core
in vec3 normal;
in vec3 position;
in vec2 texcoord;

uniform sampler2D tex;

out vec4 color;
void main() {
	color = texture(tex, texcoord);
}