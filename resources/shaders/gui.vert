#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvs;

out vec2 uv;

uniform vec2 pos;
uniform vec2 size;
uniform mat4 projection;

void main() {
	gl_Position = projection * vec4(position + pos, 0.0, 1.0);
	uv = uvs;
}