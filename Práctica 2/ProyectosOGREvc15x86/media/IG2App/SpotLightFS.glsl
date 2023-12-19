
#version 330 core
in vec2 vUv0;
in vec3 vWNormal;
in vec3 vWVertex;

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform sampler2D texFront;
uniform float tiempo;

out vec4 fFragColor;

float cos(vec3 cVertex, vec3 cNormal) {
	vec3 lightDir = lightPosition.xyz; // directional light ?
	if (lightPosition.w == 1.0) // positional light ?
		lightDir = normalize(lightDir - cVertex);

	return dot(cNormal, normalize(lightDir));
}

void main() {
	float facto = 0.2;
	if (cos(vWVertex, vWNormal) > (tiempo/2.0 + 0.25)) facto = 1;
	vec3 color = facto * texture(texFront, vUv0).rgb * lightDiffuse;

	fFragColor = vec4(color, 1.0);
}