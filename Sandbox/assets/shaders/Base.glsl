#version 460 core

layout (std140, set = 0, binding = 0) uniform CameraData
{
	mat4 u_VirwProjection;
};

layout (set = 0, binding = 10) uniform sampler2D u_Texture;

layout (std140, set = 0, binding = 1) uniform Model
{
	mat4 u_Transform;
};

#ifdef VERTEX_SHADER

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;

layout (location = 0) out FS
{
	vec3 Pos;
	vec2 TexCoord;
} fs;

void main()
{
	gl_Position = u_VirwProjection * u_Transform * vec4(a_Pos, 1.0f);

	fs.Pos = a_Pos;
	fs.TexCoord = a_TexCoord;
}

#endif

#ifdef FRAGMENT_SHADER

layout (location = 0) out vec4 f_Color;

layout (location = 0) in FS
{
	vec3 Pos;
	vec2 TexCoord;
} fs;

void main()
{
	f_Color = texture(u_Texture, fs.TexCoord);
}

#endif
