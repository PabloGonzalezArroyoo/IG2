
#version 330 core
in vec2 vUv0;
in vec3 vFrontColor;
in vec3 vBackColor;

uniform sampler2D materialTex;

out vec4 fFragColor;

void main() {
	vec3 color;
	vec3 textColor = texture(materialTex, vUv0).rgb;
	if (textColor.r > 0.6){
		discard;
	}
	else {
		if (gl_FrontFacing) color = vFrontColor;
		else color = vBackColor;
	}

	fFragColor = vec4(color, 1.0);
}