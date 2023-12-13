
#version 330 core
uniform sampler2D texturaL;
uniform sampler2D texturaM;
uniform float BF;
uniform float intLuzAmb;
float LFactor;
uniform float senoTime;
in vec2 vUv0;
out vec4 fFragColor;

void main() {
	vec3 colorL = vec3(texture(texturaL, vUv0));
	vec3 colorM = vec3(texture(texturaM, vUv0));
	LFactor = 0.625 - (0.375 * senoTime);
	vec3 color = mix(colorL, colorM, BF) * intLuzAmb * LFactor;
	fFragColor = vec4(color, 1.0);
}