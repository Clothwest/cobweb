#version 460 core

layout (std140, binding = 0) uniform Data
{
	mat4 u_ViewProjection;
	mat4 u_Transform;
	vec4 u_Color;
};

layout (binding = 10) uniform sampler2D u_Texture[32];

#ifdef VERTEX_SHADER

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TexIndex;
layout (location = 4) in float a_TilingFactor;

layout (location = 0) out FS
{
	vec4 Color;
	vec2 TexCoord;
	float TexIndex;
	float TilingFactor;
} fs;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Pos, 1.0f);

	fs.Color = a_Color;
	fs.TexCoord = a_TexCoord;
	fs.TexIndex = a_TexIndex;
	fs.TilingFactor = a_TilingFactor;
}

#endif

#ifdef FRAGMENT_SHADER

layout (location = 0) out vec4 f_Color;

layout (location = 0) in FS
{
	vec4 Color;
	vec2 TexCoord;
	float TexIndex;
	float TilingFactor;
} fs;

void main()
{
//	f_Color = fs.Color;

	int texIndex = int(fs.TexIndex);
	f_Color = texture(u_Texture[texIndex], fs.TexCoord * fs.TilingFactor) * fs.Color;
}

#endif
