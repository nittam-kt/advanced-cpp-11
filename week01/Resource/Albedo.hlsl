// 0�Ԃ̃e�N�X�`���X���b�g���g�p����
Texture2D texture0 : register(t0);

// 0�Ԃ̃T���v���X���b�g���g�p����
SamplerState sampler0 : register(s0);

cbuffer VSConstants : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 projection;
};

// ���_�V�F�[�_�[�֓��͂���f�[�^
struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXUV;
};


// ���_�V�F�[�_�[����o�͂���f�[�^
struct PSInput
{
    float4 pos : SV_Position; // ���_�̍��W(�ˉe���W�n)
    float2 uv : TEXCOORD0; // UV���W
};
 
// ----------------------------------------------------------
// ���_�V�F�[�_�[
// ----------------------------------------------------------
PSInput VS(VSInput vin)
{
    PSInput Out;
    float4 p = mul(world, vin.pos);
    p = mul(view, p);
    p = mul(projection, p);
    Out.pos = p;
    Out.uv = vin.uv;
    return Out;
}
 
// ----------------------------------------------------------
// �s�N�Z���V�F�[�_�[
// ----------------------------------------------------------
float4 PS(PSInput In) : SV_Target0
{
    // �e�N�X�`������F���擾
    float4 texColor = texture0.Sample(sampler0, In.uv);
 
    // �e�N�X�`���̐F���o��
    return texColor;
}
