// コンスタントバッファ
cbuffer ConstantBuffer : register(b0)
{
    matrix World;       // ワールド行列
    matrix View;        // ビュー行列
    matrix Projection;  // 射影行列
    float4 vEyePos;     // 視点の座標
    float4 vLightDir;   // ライトの座標
    float4 vLightColor; // ライトの色
    float4 vSpecular;   // ライト以外のモデルの色
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // 現在のピクセル位置
    float4 PosW : POSITION0;  // オブジェクトのワールド座標
    float4 NorW : TEXCOORD0;  // 法線
};

// ピクセルシェーダー(ライティング)
float4 PSLight(PS_INPUT input) : SV_TARGET
{
    float3 l; // 正規化した光源ベクトル
    float3 n; // 正規化した法線ベクトル
    float3 r; // 正規化した正反射ベクトル
    float3 v; // 正規化した視線ベクトル
    float  i; // rとｖの内積を取り、光沢度係数をべき乗した結果

    // -- 鏡面反射 --
    l = normalize(vLightDir.xyz - input.PosW.xyz);
    n = normalize(input.NorW.xyz);
    r = 2.0 * n * dot(n , l) - l;
    v = normalize(vEyePos.xyz - input.PosW.xyz);
    i = pow(saturate(dot(r, v)), vSpecular.w);

    return float4(i * vSpecular.xyz * vLightColor.xyz, 1.0);
}