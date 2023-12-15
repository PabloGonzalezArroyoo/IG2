
#version 330 core
in vec2 vUv0;

uniform sampler2D texFront;
uniform sampler2D texBack;
uniform sampler2D texCorr;

out vec4 fFragColor;

void main() {
	vec3 color;
	vec3 textColor = texture(texCorr, vUv0).rgb;
	if (textColor.r > 0.6){
		discard;
	}
	else {
		if (gl_FrontFacing) color = vec3(texture(texFront,vUv0));
		else color = vec3(texture(texBack,vUv0));
	}
	
	fFragColor = vec4(color, 1.0);
}