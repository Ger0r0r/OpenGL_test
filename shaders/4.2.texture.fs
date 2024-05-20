#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float proc;

void main()
{
	FragColor = texture(texture2, vec2(TexCoord.x, -TexCoord.y));
	if (texture(texture2, vec2(TexCoord.x, -TexCoord.y)).a < proc)
		FragColor = texture(texture1, vec2(TexCoord.x/2, -TexCoord.y/2));
}