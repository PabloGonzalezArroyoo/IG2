
#version 330 core
in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelMat;
uniform mat4 modelViewProjMat;
uniform mat4 normalMat;
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
		lightDir = normalize(lightDir - cVertex);

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
	vec3 worldVertex = vec3(modelMat * vertex);
	vec3 worldNormal = normalize(vec3(normalMat * vec4(normal, 0.0)));

	vec3 diffuseFront = diff(worldVertex, worldNormal) * lightDiffuse;
	vec3 diffuseBack = diff(worldVertex, -worldNormal) * lightDiffuse;
		
	vFrontColor = diffuseFront * texture(texFront, uv0).rgb * materialDiffuseFront;
	vBackColor = diffuseBack * texture(texBack, uv0).rgb * materialDiffuseBack;
	
	vUv0 = uv0;
	gl_Position = modelViewProjMat * vertex;
}