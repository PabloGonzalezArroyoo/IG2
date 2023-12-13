
#version 330 core

in vec4 vertex;
in vec2 uv0;
float zoom;
uniform float senoTime;
uniform mat4 modelViewProjMat;
out vec2 vUv0; // out del vertex shader

void main() {
	vUv0 = uv0;
	vUv0 += (0.5, -0.5);
	zoom = 0.75 + (0.25 * senoTime);
	vUv0 *= zoom;
	vUv0 += (-0.5, 0.5);
	gl_Position = modelViewProjMat * vertex;
}