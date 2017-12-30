// �R���X�^���g�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    matrix World;          // ���[���h�s��
    matrix View;           // �r���[�s��
    matrix Projection;     // �ˉe�s��
    float4 vEyePos;
    float4 vLightDir;      // ���C�g�̍��W
    float4 vLightColor;    // ���C�g�̐F
    float4 vSpecular;   // ���C�g�ȊO�̃��f���̐F
}

struct VS_INPUT
{
    float4 Pos : POSITION; // ���_�ʒu
    float3 Norm : NORMAL;  // �@���x�N�g��
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 PosW : POSITION0;
    float4 NorW : TEXCOORD0;
};

// ���_�V�F�[�_�[
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
    output.PosW  = mul(input.Pos, World);
    output.Pos   = mul(output.PosW, View);
    output.Pos   = mul(output.Pos, Projection);
    output.NorW  = mul(input.Norm, World);

    return output;
}
