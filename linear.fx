// �V�F�[�_�[���f�� 3.0���g�p
float4x4 WorldViewProjection : WORLDVIEWPROJECTION;

texture Texture; // �e�N�X�`����錾
sampler TextureSampler = sampler_state
{
	Texture = <Texture>;
	MinFilter = LINEAR;  // �~�j�t�@�C���^�[�̐ݒ�
	MagFilter = LINEAR;  // �}�O�t�@�C���^�[�̐ݒ�
	MipFilter = LINEAR;  // �~�b�v�t�@�C���^�[�̐ݒ�
	AddressU = WRAP;   // U���̃A�h���X���[�h
	AddressV = WRAP;   // V���̃A�h���X���[�h
};

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 TexCoord : TEXCOORD0;
};

// �s�N�Z���V�F�[�_
float4 SmoothSamplerPS(VS_OUTPUT input) : COLOR
{
	// �e�N�X�`�����T���v�����O���A���炩�ȏo�͂𐶐�
	float4 color = tex2D(TextureSampler, input.TexCoord);

	return color;
}

technique Render
{
	pass P0
	{
		VertexShader = null;
		PixelShader = compile ps_3_0 SmoothSamplerPS();
	}
}