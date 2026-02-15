#version 460 core

layout (std140, set = 0, binding = 0) uniform CameraData
{
	mat4 u_ViewProjection;
	mat4 u_Transform;
	vec4 u_Color;
};

#ifdef VERTEX_SHADER

layout (location = 0) in vec3 a_Pos;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0f);
}

#endif

#ifdef FRAGMENT_SHADER

layout (location = 0) out vec4 f_Color;

void main()
{
	f_Color = u_Color;
}

#endif
