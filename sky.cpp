//========================================================================================
//
// 3Dオブジェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "Sky.h"
#include "objectX.h"
#include "manager.h"
#include "texture.h"
#include "Xmanager.h"

//=============================================
//コンストラクタ
//=============================================

CSky::CSky(int nPriority) : CObjectX(nPriority)
{


}



//=============================================
//デストラクタ
//=============================================
CSky::~CSky()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CSky::Init(void)
{
	SetName("data\\MODEL\\sky.x");
	CObjectX::Init();

	CXManager * pManger = CManager::GetXManager();
	
		pManger->Release(m_nID);
		m_nID = -1;
	return S_OK;;
}
//=============================================
//生成関数
//=============================================
CSky * CSky::Create()
{
	CSky * pObject3D = NULL;

	pObject3D = DBG_NEW CSky(0);
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CSky::Uninit(void)
{
	CObjectX::Uninit();
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CSky::Update(void)
{
	
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CSky::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
    pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //フォグの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	CObjectX::Draw();
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); 
}

