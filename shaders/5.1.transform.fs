#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = texture(texture2, vec2(TexCoord.x, -TexCoord.y));
	if (texture(texture2, vec2(TexCoord.x, -TexCoord.y)).a < 0.2)
		FragColor = texture(texture1, vec2(TexCoord.x/2, -TexCoord.y/2));
}