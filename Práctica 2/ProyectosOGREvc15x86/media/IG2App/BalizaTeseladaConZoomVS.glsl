
#version 330 core

in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
uniform float senoTime;
float zoom;
out vec2 vUv0;
out vec2 vUv1;

void main() {
	vUv0 = uv0;
	vUv1 = uv0;
	vUv1 += (0.5, -0.5);
	zoom = 0.75 + (0.25 * senoTime);
	vUv1 *= zoom;
	vUv1 += (-0.5, 0.5);
	gl_Position = modelViewProjMat * vertex;
}