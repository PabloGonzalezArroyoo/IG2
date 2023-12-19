
#version 330 core
in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewMat;
uniform mat4 modelViewProjMat;
uniform mat3 normalMat;

out vec2 vUv0;
out vec3 vWNormal;
out vec3 vWVertex;

void main(){
	vUv0 = uv0;
	vWVertex = vec3(modelViewMat * vertex);
	vWNormal = normalize(normalMat * normal);

	gl_Position = modelViewProjMat * vertex;
}