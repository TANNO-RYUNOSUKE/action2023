// �V�F�[�_�[���f��3.0���g�p
// �h�b�g�G���̃V�F�[�_�[

sampler2D texSampler : register(s0);

float4 Main(float2 texCoord : TEXCOORD0) : COLOR
{
	// �s�N�Z���̃T�C�Y��ݒ�
	float2 pixelSize = float2(1.0 / 1280.0, 1.0 / 720.0); // ��ʃT�C�Y�ɍ��킹�Ē���

														 // �h�b�g�G���̃G�t�F�N�g��K�p
	float2 roundedTexCoord = floor(texCoord / pixelSize) * pixelSize;
	float4 color = tex2D(texSampler, roundedTexCoord);

	return color;
}

technique PostProcess
{
	pass P0
	{
		PixelShader = compile ps_3_0 Main();
	}
}