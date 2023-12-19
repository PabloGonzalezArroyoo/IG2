
#version 330 core
in vec4 vertex;
in vec3 normal;
in vec2 uv0;

uniform mat4 modelMat;
uniform mat4 modelViewProjMat;
uniform mat4 normalMat;

out vec2 vUv0;
out vec3 vWNormal;
out vec3 vWVertex;

void main(){
	vUv0 = uv0;
	vWVertex = vec3(modelMat * vertex);
	vWNormal = normalize(vec3(normalMat * vec4(normal, 0.0)));

	gl_Position = modelViewProjMat * vertex;
}