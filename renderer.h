//==================
//レンダラーヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _RENDERER_H_//二重インクルード防止のマクロ
#define _RENDERER_H_
//インクルード
#include "main.h"

//クラス定義
class CRenderer //レンダラークラス
{
public:
	//コンストラクタとデストラクタ
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	RECT GetTextureRect(IDirect3DTexture9* pSceneTexture);
	LPDIRECT3DDEVICE9 GetDevice(void){return m_pD3DDevice;}
	D3DPRESENT_PARAMETERS GetD3D(void) { return m_pD3Dpa; }

private:						
	LPDIRECT3D9 m_pD3D;						//direct3Dへのポインタ
	D3DPRESENT_PARAMETERS m_pD3Dpa;
	LPDIRECT3DDEVICE9 m_pD3DDevice;			//direct3Dデバイスへのポインタ
	LPD3DXEFFECT pEffect;
	LPD3DXEFFECT pEffectdot;
	LPD3DXEFFECT pEffectDownSample;
	LPD3DXEFFECT pEffectBrightCheck;
	LPD3DXEFFECT pEffectLinear;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		//頂点バッファ
	LPDIRECT3DTEXTURE9 pSceneTexture;
	LPDIRECT3DTEXTURE9 pBloomTexture;
};

#endif // ! _RENDERER_H_
