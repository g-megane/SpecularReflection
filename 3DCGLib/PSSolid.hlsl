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

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 現在のピクセル位置
    float3 Norm : TEXCOORD0;  // 法線
};

// ピクセルシェーダー(ライティングなし)
float4 PSSolid(PS_INPUT input) : SV_Target
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}