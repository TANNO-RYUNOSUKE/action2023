// シェーダーモデル3.0を使用
// ドット絵風のシェーダー

sampler2D texSampler : register(s0);

float4 Main(float2 texCoord : TEXCOORD0) : COLOR
{
	// ピクセルのサイズを設定
	float2 pixelSize = float2(1.0 / 1280.0, 1.0 / 720.0); // 画面サイズに合わせて調整

														 // ドット絵風のエフェクトを適用
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