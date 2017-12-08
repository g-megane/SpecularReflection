cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 vLightDir[2];
    float4 vLightColor[2];
    float4 vOutputColor;
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
};

float4 PSLight(PS_INPUT input) : SV_TARGET
{
    float4 finalColor = 0;

    for (int i = 0; i < 2; ++i) {
        finalColor += saturate(dot((float3)vLightDir[i], input.Norm) * vLightColor[i]);
    }
    finalColor.a = 1;

	return finalColor;
}