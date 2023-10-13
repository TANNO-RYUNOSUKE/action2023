// �u���[���V�F�[�_�[
sampler2D SceneTexture : register(s0);



float4 main(float2 texCoord : TEXCOORD0) : COLOR0
{ 
	float BloomThreshold = 1.0; // �u���[���̂������l
float BloomIntensity = 1.5; // �u���[���̋��x

	// �u���[���̒��o
	float4 brightColor = tex2D(SceneTexture, texCoord);
	if (brightColor.r + brightColor.g + brightColor.b > BloomThreshold)
	{
		brightColor = (brightColor - BloomThreshold) * BloomIntensity;
	}
	else
	{
		brightColor = 0;
	}

	// �V�[���ƃu���[���̍���
	float4 finalColor = tex2D(SceneTexture, texCoord) + brightColor;
	return finalColor;
}

technique Bloom
{
	pass P0
	{
		PixelShader = compile ps_2_0 main();
	}
}