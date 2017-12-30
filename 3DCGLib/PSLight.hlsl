// �R���X�^���g�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    matrix World;       // ���[���h�s��
    matrix View;        // �r���[�s��
    matrix Projection;  // �ˉe�s��
    float4 vEyePos;     // ���_�̍��W
    float4 vLightDir;   // ���C�g�̍��W
    float4 vLightColor; // ���C�g�̐F
    float4 vSpecular;   // ���C�g�ȊO�̃��f���̐F
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // ���݂̃s�N�Z���ʒu
    float4 PosW : POSITION0;  // �I�u�W�F�N�g�̃��[���h���W
    float4 NorW : TEXCOORD0;  // �@��
};

// �s�N�Z���V�F�[�_�[(���C�e�B���O)
float4 PSLight(PS_INPUT input) : SV_TARGET
{
    float3 l; // ���K�����������x�N�g��
    float3 n; // ���K�������@���x�N�g��
    float3 r; // ���K�����������˃x�N�g��
    float3 v; // ���K�����������x�N�g��
    float  i; // r�Ƃ��̓��ς����A����x�W�����ׂ��悵������

    // -- ���ʔ��� --
    l = normalize(vLightDir.xyz - input.PosW.xyz);
    n = normalize(input.NorW.xyz);
    r = 2.0 * n * dot(n , l) - l;
    v = normalize(vEyePos.xyz - input.PosW.xyz);
    i = pow(saturate(dot(r, v)), vSpecular.w);

    return float4(i * vSpecular.xyz * vLightColor.xyz, 1.0);
}