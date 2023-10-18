// シェーダーモデル 3.0を使用
float4x4 WorldViewProjection : WORLDVIEWPROJECTION;

texture Texture; // テクスチャを宣言
sampler TextureSampler = sampler_state
{
	Texture = <Texture>;
	MinFilter = LINEAR;  // ミニファイルターの設定
	MagFilter = LINEAR;  // マグファイルターの設定
	MipFilter = LINEAR;  // ミップファイルターの設定
	AddressU = WRAP;   // U軸のアドレスモード
	AddressV = WRAP;   // V軸のアドレスモード
};

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 TexCoord : TEXCOORD0;
};

// ピクセルシェーダ
float4 SmoothSamplerPS(VS_OUTPUT input) : COLOR
{
	// テクスチャをサンプリングし、滑らかな出力を生成
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