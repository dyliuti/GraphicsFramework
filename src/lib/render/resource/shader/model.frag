#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;
uniform vec2 iSize;
uniform float iTime;
uniform float mixValue;

// Texture samplers
uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

mat2 rot(float angle){
	float s = sin(angle);
	float c = cos(angle);
	mat2 m = mat2(c, s, -s, c);
	return m;
}

void main()
{
	// Linearly interpolate between both textures (second texture is only slightly combined)
	// (1-alpha) * src + alpha * dst
	vec2 uv = (TexCoord - 0.5 * iSize.xy) / iSize;
	//color = vec4(uv.y, uv.y, uv.y, 1.0);
	uv = uv*rot(iTime*3);
	color = texture(ourTexture1, vec2(uv.x + 0.5, uv.y + 0.7));
}