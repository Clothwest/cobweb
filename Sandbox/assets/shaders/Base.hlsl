struct VSInput
{
	[[vk::location(0)]] float3 Pos : POSITION;
};

struct PSInput
{
	float4 a_Pos : SV_Position;
	[[vk::location(0)]] float3 Pos : POSITIONT;
};

cbuffer Uniform : register(b0)
{
	float4 u_Color;
};

PSInput VSMain(VSInput input)
{
	PSInput output;
	output.a_Pos = float4(input.Pos, 1.0f);
	output.Pos = input.Pos;
	return output;
};

float4 PSMain(PSInput input) : SV_Target
{
	return u_Color;
}
