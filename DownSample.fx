
sampler2D TextureSampler : register(s0);

struct VS_OUTPUT
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
};

float4 main(VS_OUTPUT Input) : COLOR
{
	// �s�N�Z���̍��W
	float2 pixelCoord = Input.TexCoord;

	// �s�N�Z�����S����̃I�t�Z�b�g���v�Z
	float2 offset = 1.0 / float2(160.0, 90.0);
	// �T���v���p�̃I�t�Z�b�g�l
	float2 offsets[8] = {
		float2(-0.5, -0.5), float2(0.5, -0.5), float2(-0.5, 0.5), float2(0.5, 0.5),
		float2(-1.5, -1.5), float2(-0.5, -1.5), float2(-1.5, -0.5), float2(-0.5, -0.5)
	};

	// �T���v�����ʂ�������
	float4 sampleColor = float4(0, 0, 0, 0);

	// 8�̃T���v�����擾���A���ς��v�Z
	for (int i = 0; i < 8; i++)
	{
		sampleColor += tex2D(TextureSampler, pixelCoord + offset * offsets[i]);
	}

	// ���ω������F��8�Ŋ����Đ��K��
	sampleColor /= 8.0;

	return sampleColor;
}
technique DownSample
{
	pass Pass1
	{
		PixelShader = compile ps_2_0 main();
	}
}
