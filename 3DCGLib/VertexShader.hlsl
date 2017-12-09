// コンスタントバッファ
cbuffer ConstantBuffer : register(b0)
{
    matrix World;          // ワールド行列
    matrix View;           // ビュー行列
    matrix Projection;     // 射影行列
    float4 vLightDir[2];   // ライトの座標
    float4 vLightColor[2]; // ライトの色
    float4 vOutputColor;   // ライト以外のモデルの色
}

struct VS_INPUT
{
    float4 Pos : POSITION; // 頂点位置
    float3 Norm : NORMAL;  // 法線ベクトル
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
};

// 頂点シェーダー
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos  = mul(input.Pos, World);
    output.Pos  = mul(output.Pos, View);
    output.Pos  = mul(output.Pos, Projection);
    output.Norm = mul(float4(input.Norm, 0.0f), World).xyz;

    return output;
}
