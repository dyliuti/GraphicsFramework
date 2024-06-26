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
	return mat2(c, s, -s, c);
}

void main()
{
	// Linearly interpolate between both textures (second texture is only slightly combined)
	// (1-alpha) * src + alpha * dst
	//vec2 uv = (TexCoord - 0.5 ) * iSize / iSize.y;
	//uv = vec2(uv.x * iSize.y/iSize.x, uv.y * iSize.x/iSize.y);
	//color = vec4(uv.y, uv.y, uv.y, 1.0);

	vec2 uv = TexCoord;
	float ratio = iSize.x/iSize.y;

	uv = vec2((uv.x * 2.0 -1.0) * ratio, uv.y * 2.0 -1.0)*rot(iTime*3);
	uv = vec2((uv.x/ratio + 1.0)/2.0, (uv.y + 1.0)/2.0);
	float matt = step(uv.x, 1.0) * step(uv.y, 1.0) * step(0.0, uv.x) * step(0.0, uv.y);
	color = texture(ourTexture1, uv) * matt;
}