
#version 330 core
in vec3 vWVertex;
in vec3 vWNormal;
in vec2 vUv0;

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform vec3 materialDiffuseFront;
uniform vec3 materialDiffuseBack;

uniform sampler2D texMeta;
uniform sampler2D texRock;
uniform sampler2D texCorr;

out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal) {
	vec3 lightDir = lightPosition.xyz; // directional light ?
	if (lightPosition.w == 1.0) // positional light ?
		lightDir = lightDir - cVertex;

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
	vec3 textColor = texture(texCorr, vUv0).rgb;
	if (textColor.r > 0.6){
		discard;
	}

	vec3 diffuse = diff(vWVertex, vWNormal) * lightDiffuse;

	vec3 vFrontColor = diffuse + vec3(texture(texMeta, vUv0)) * materialDiffuseFront;
	vec3 vBackColor = diffuse + vec3(texture(texRock, vUv0)) * materialDiffuseBack;
	
	if (gl_FrontFacing) fFragColor = vec4(vFrontColor, 1.0);
	else fFragColor = vec4(vBackColor, 1.0);
}