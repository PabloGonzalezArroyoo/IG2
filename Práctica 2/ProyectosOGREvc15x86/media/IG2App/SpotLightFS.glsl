
#version 330 core
in vec2 vUv0;
in vec3 vWNormal;
in vec3 vWVertex;

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform sampler2D texFront;
uniform float tiempo;

out vec4 fFragColor;

float fac(vec3 cVertex, vec3 cNormal){
	vec3 lightDir = lightPosition.xyz; // directional light ?
	if (lightPosition.w == 1.0) // positional light ?
		lightDir = normalize(lightDir - cVertex);

	if (dot(cNormal, lightDir) > (tiempo > 0 ? tiempo : tiempo/2.0)) return 1;
	else return 0.2;
}

void main() {
	float facto = fac(vWVertex, vWNormal);
	vec3 color = facto * texture(texFront, vUv0).rgb * lightDiffuse;
	fFragColor = vec4(color, 1.0);
}