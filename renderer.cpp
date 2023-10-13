//========================================================================================
//
// レンダラー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//=============================================
//デストラクタ
//=============================================
CRenderer::~CRenderer()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//DirectXオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct#Dデバイスの生成
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	m_pD3Dpa = d3dpp;
	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//各種オブジェクト初期化処理はここ

	ID3DXBuffer* pError = NULL;
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);
	VERTEX_2D *pVtx;
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//法線の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtxBuff->Unlock();
	pDevice->CreateTexture(
		SCREEN_WIDTH,          // テクスチャの幅
		SCREEN_HEIGHT,         // テクスチャの高さ
		1,              // ミップマップ レベル
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8, // フォーマット
		D3DPOOL_DEFAULT, // プール
		&pSceneTexture,  // テクスチャ オブジェクト
		NULL);

	// fxファイルを読み込む

	HRESULT hr = D3DXCreateEffectFromFile(
		pDevice,				// デバイスへのポインタ
		"BloomEffect.fx",			// fxファイルのパス
		NULL,                  // プリプロセッサ定義
		NULL,                  // プリプロセッサ定義ファイル
		D3DXSHADER_DEBUG,                     // フラグ
		NULL,                  // カスタムエフェクトプール
		&pEffect,              // 読み込まれたエフェクト
		&pError                // エラーメッセージ
	);
	if (pError)
	{
		OutputDebugStringA((LPCSTR)pError->GetBufferPointer());
		// ログファイルに書き出すか、デバッグコンソールに表示する
		MessageBoxA(NULL, (LPCSTR)pError->GetBufferPointer(), "Shader Error", MB_OK);

	}

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CRenderer::Uninit(void)
{
	//各種オブジェクトの終了処理
	
	//DirectX3dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	//DirectX3dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
	

}
//=============================================
//更新関数
//=============================================
void CRenderer::Update(void)
{

	// ウィンドウのクライアント領域のサイズを取得
	RECT clientRect;




	// クライアント領域の幅と高さを表示
	float width = SCREEN_WIDTH;
	float height = SCREEN_HEIGHT;
	VERTEX_2D *pVtx;
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//座標
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(width, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(width, height, 0.0f);

	pVtxBuff->Unlock();


	//各種オブジェクトの更新処理
	CObject::UpDateAll();

	
}
//=============================================
//描画関数
//=============================================
void CRenderer::Draw(void)
{
	CDebugProc * pDeb = CManager::GetDeb();
	//画面クリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);





	IDirect3DSurface9* pBackBuffer;
	m_pD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	IDirect3DSurface9* pRenderTarget;
	pSceneTexture->GetSurfaceLevel(0, &pRenderTarget);
	m_pD3DDevice->SetRenderTarget(0, pRenderTarget);



	m_pD3DDevice->SetRenderTarget(0, pBackBuffer);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//成功した場合
		CObject::DrawAll();
		pDeb->Draw();


		//頂点バッファをデータストリームに設定
		m_pD3DDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		m_pD3DDevice->SetTexture(0, NULL);

		//ポリゴンの描画
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		

		//終了
		m_pD3DDevice->EndScene();
	}


	pBackBuffer->Release();
	pRenderTarget->Release();
	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
