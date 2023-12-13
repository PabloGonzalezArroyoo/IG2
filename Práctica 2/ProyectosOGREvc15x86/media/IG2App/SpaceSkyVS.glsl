
#version 330 core

in vec4 vertex;
in vec4 uv0;
uniform mat4 modelViewProjMat;
uniform float senoTime;
uniform float cosenoTime;
out vec4 vUv0;

void main() {
	mat3 rotationMatrix = mat3(cosenoTime, senoTime, 0, -senoTime, cosenoTime, 0, 0, 0, 1);
	vec3 vertex3 = vec3(vertex);
	vertex3 = vertex3 * rotationMatrix;
	vUv0 = uv0;
	gl_Position = modelViewProjMat * vec4(vertex3, 1);
}