#version 330 core
layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 position;
out vec2 texcoord;

void main(){
	gl_Position = projection * view * model * vec4(in_vertex, 1.0f);
	position = gl_Position.xyz;
	normal = normalize(mat3(projection * view * model) * in_normal);
	// position = in_vertex;
	texcoord = in_texcoord;
}

