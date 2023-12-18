
#version 330 core
in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewMat;
uniform mat4 modelViewProjMat;
uniform mat3 normalMat;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform vec3 materialDiffuseFront;
uniform vec3 materialDiffuseBack;
uniform sampler2D texFront;
uniform sampler2D texBack;

out vec2 vUv0;
out vec3 vFrontColor;
out vec3 vBackColor;

float diff(vec3 cVertex, vec3 cNormal) {
	vec3 lightDir = lightPosition.xyz; // directional light ?
	if (lightPosition.w == 1) // positional light ?
		lightDir = lightDir - cVertex;

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
	vec3 viewVertex = vec3(modelViewMat * vertex);
	vec3 viewNormal = normalize(normalMat * normal);
	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse;

	vFrontColor = diffuse + texture(texFront, uv0).rgb * materialDiffuseFront;
	vBackColor = diffuse + texture(texBack, uv0).rgb * materialDiffuseBack;
	
	vUv0 = uv0;
	gl_Position = modelViewProjMat * vertex;
}