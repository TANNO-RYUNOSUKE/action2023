ps_3_0
sampler2D TextureSampler; // テクスチャサンプラーレジスタ

// ピクセルシェーダー
float4 main(float2 texCoord : TEXCOORD0) : COLOR0
{
	

	float4 color = tex2D(TextureSampler, texCoord); // オリジナルのテクスチャカラー

															// 画像の明るい部分を抽出
	float3 brightColor = color.rgb;
	float brightness = dot(brightColor, float3(0.3, 0.59, 0.11));

	// ブルーム強度の調整
	float bloomIntensity = 2.0;

	// ブルームの閾値（この値より明るい部分がブルームとして表示されます）
	float bloomThreshold = 0.8;

	if (brightness > bloomThreshold)
	{
		float3 bloomColor = (brightness - bloomThreshold) * bloomIntensity;
		color.rgb += bloomColor;
	}

	return color;
}