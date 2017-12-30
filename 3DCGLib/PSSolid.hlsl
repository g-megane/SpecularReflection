// �R���X�^���g�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    matrix World;          // ���[���h�s��
    matrix View;           // �r���[�s��
    matrix Projection;     // �ˉe�s��
    float4 vLightDir[2];   // ���C�g�̍��W
    float4 vLightColor[2]; // ���C�g�̐F
    float4 vOutputColor;   // ���C�g�ȊO�̃��f���̐F
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION; // ���݂̃s�N�Z���ʒu
    float3 Norm : TEXCOORD0;  // �@��
};

// �s�N�Z���V�F�[�_�[(���C�e�B���O�Ȃ�)
float4 PSSolid(PS_INPUT input) : SV_Target
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}