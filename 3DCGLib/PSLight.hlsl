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

// ピクセルシェーダー(ライティング)
float4 PSLight(PS_INPUT input) : SV_TARGET
{
    float4 finalColor = 0;

    // 2ヶ所のライトを計算
    for (int i = 0; i < 2; ++i) {
        // ライトベクトルと法線ベクトルの内積(dot)を計算
        // 求めた内積の値でで光の当たり具合が-1 ～ 1の範囲で求まる(saturateで0 ～ １に抑制)
        // 求めた内積とライトから最終的な面の値を算出
        finalColor += saturate(dot((float3)vLightDir[i], input.Norm) * vLightColor[i]);
    }
    finalColor.a = 1;

	return finalColor;
}