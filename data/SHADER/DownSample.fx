
sampler2D TextureSampler : register(s0);

struct VS_OUTPUT
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
};

float4 main(VS_OUTPUT Input) : COLOR
{
	// ピクセルの座標
	float2 pixelCoord = Input.TexCoord;

	// ピクセル中心からのオフセットを計算
	float2 offset = 1.0 / float2(160.0, 90.0);
	// サンプル用のオフセット値
	float2 offsets[8] = {
		float2(-0.5, -0.5), float2(0.5, -0.5), float2(-0.5, 0.5), float2(0.5, 0.5),
		float2(-1.5, -1.5), float2(-0.5, -1.5), float2(-1.5, -0.5), float2(-0.5, -0.5)
	};

	// サンプル結果を初期化
	float4 sampleColor = float4(0, 0, 0, 0);

	// 8つのサンプルを取得し、平均を計算
	for (int i = 0; i < 8; i++)
	{
		sampleColor += tex2D(TextureSampler, pixelCoord + offset * offsets[i]);
	}

	// 平均化した色を8で割って正規化
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
