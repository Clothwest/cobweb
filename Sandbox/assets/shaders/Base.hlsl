struct VSInput
{
	[[vk::location(0)]] float3 Pos : POSITION;
};

struct PSInput
{
	float4 a_Pos : SV_Position;
	[[vk::location(0)]] float3 Pos : POSITIONT;
};

cbuffer ViewProjection : register(b0)
{
	float4x4 u_ViewProjection;
}

cbuffer Transform : register(b1)
{
	float4x4 u_Transform;
}

cbuffer Uniform : register(b10)
{
	float4 u_Color;
}

PSInput VSMain(VSInput input)
{
	PSInput output;
	output.a_Pos = mul(u_ViewProjection, mul(u_Transform, float4(input.Pos, 1.0f)));
	output.Pos = input.Pos;
	return output;
}

float4 PSMain(PSInput input) : SV_Target
{
	return u_Color;
}
