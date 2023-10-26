//========================================================================================
//
// ナンバー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "number.h"
#include "object2D.h"
#include "manager.h"
#include "renderer.h"


//=============================================
//コンストラクタ
//=============================================
CNumber::CNumber()
{
	m_pObbject = NULL;
	m_ndata = 0;
	m_nType = 0;
}



//=============================================
//デストラクタ
//=============================================
CNumber::~CNumber()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CNumber::Init(void)
{
	m_bDisp = true;
	switch (m_nType)
	{
	case 1:
		m_pObbject = CObject2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 6, "data\\TEXTURE\\number003.png");
		break;
	default:
		m_pObbject = CObject2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 6, "data\\TEXTURE\\number005.png");
		break;
	}


	return S_OK;
}
//=============================================
//生成関数
//=============================================
CNumber * CNumber::Create(int nType)
{
	CNumber * pNumber = NULL;
 	pNumber = DBG_NEW CNumber;
	pNumber->m_nType = nType;
	pNumber->Init();
	return pNumber;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CNumber::Uninit(void)
{
	
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CNumber::Update(void)
{
	m_pObbject->SetDisp(m_bDisp);
	LPDIRECT3DVERTEXBUFFER9 * pVtxBuff = m_pObbject->GetBuff();
	VERTEX_2D * pVtx;
	(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	m_pObbject->SetTexMin(D3DXVECTOR2((0.1f * m_ndata), 0.0f));
	m_pObbject->SetTexMax(D3DXVECTOR2((0.1f * m_ndata) + 0.1f, 1.0f));

	m_pObbject->SetVtx(pVtx);

	(*pVtxBuff)->Unlock();
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CNumber::Draw(void)
{
	m_pObbject->Draw();

}
//=============================================
//設定
//=============================================
void CNumber::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	m_pObbject->SetPos(pos);
	m_pObbject->SetRot(rot);
	m_pObbject->SetHeight(fHeight);
	m_pObbject->SetWidth(fWidth);
}
