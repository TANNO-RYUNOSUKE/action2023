// ブルームシェーダー
sampler2D SceneTexture : register(s0);



float4 main(float2 texCoord : TEXCOORD0) : COLOR0
{ 
	float BloomThreshold = 1.0; // ブルームのしきい値
float BloomIntensity = 1.5; // ブルームの強度

	// ブルームの抽出
	float4 brightColor = tex2D(SceneTexture, texCoord);
	if (brightColor.r + brightColor.g + brightColor.b > BloomThreshold)
	{
		brightColor = (brightColor - BloomThreshold) * BloomIntensity;
	}
	else
	{
		brightColor = 0;
	}

	// シーンとブルームの合成
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