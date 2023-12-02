
#version 330 core
in vec2 vUv0;

uniform sampler2D checkersTex;
uniform sampler2D spaceTex;
uniform sampler2D metalTex;

out vec4 fFragColor;

void main() {
	vec3 colorCheckers = vec3(texture(checkersTex, vUv0));
	vec3 color;
	if (colorCheckers.x > 0) {
		color = vec3(texture(spaceTex, vUv0));
	}
	else {
		color = vec3(texture(metalTex, vUv0));
	}
	fFragColor = vec4(color, 1.0);
}