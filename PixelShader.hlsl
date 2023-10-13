ps_3_0
sampler2D TextureSampler; // �e�N�X�`���T���v���[���W�X�^

// �s�N�Z���V�F�[�_�[
float4 main(float2 texCoord : TEXCOORD0) : COLOR0
{
	

	float4 color = tex2D(TextureSampler, texCoord); // �I���W�i���̃e�N�X�`���J���[

															// �摜�̖��邢�����𒊏o
	float3 brightColor = color.rgb;
	float brightness = dot(brightColor, float3(0.3, 0.59, 0.11));

	// �u���[�����x�̒���
	float bloomIntensity = 2.0;

	// �u���[����臒l�i���̒l��薾�邢�������u���[���Ƃ��ĕ\������܂��j
	float bloomThreshold = 0.8;

	if (brightness > bloomThreshold)
	{
		float3 bloomColor = (brightness - bloomThreshold) * bloomIntensity;
		color.rgb += bloomColor;
	}

	return color;
}