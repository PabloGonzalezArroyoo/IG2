
#version 330 core
in vec2 vUv0;
in vec3 vWNormal;
in vec3 vWVertex;

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform sampler2D texFront;
uniform float tiempo;

out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal) {
	vec3 lightDir = lightPosition.xyz; // directional light ?
	if (lightPosition.w == 1.0) // positional light ?
		lightDir = normalize(lightDir - cVertex);

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
	float fac;
	if (diff(vWVertex, vWNormal) > abs(tiempo)/2.0) {
		fac = 1;
	}
	else {
		fac = 0.2;
	}
	vec3 color = fac * texture(texFront, vUv0).rgb * lightDiffuse;
	fFragColor = vec4(color, 1.0);
}