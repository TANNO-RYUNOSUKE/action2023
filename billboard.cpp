//========================================================================================
//
// 3Dオブジェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object3D.h"
#include "manager.h"
#include "billboard.h"
#include "texture.h"

//=============================================
//コンストラクタ
//=============================================

CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_Cclor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Tex_min = D3DXVECTOR2(0.0f, 0.0f);
	Tex_max = D3DXVECTOR2(1.0f, 1.0f);
	m_pVtxBuff = NULL;
	m_pName = NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
}



//=============================================
//デストラクタ
//=============================================
CBillboard::~CBillboard()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CBillboard::Init(void)
{

	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

	if (m_pName != NULL)
	{
		CTexture * pTex = CManager::GetInstance()->GetTexture();
		m_nIdxTex[0] = pTex->Regist(m_pName);
	}
	

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, +m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, -m_fHeight, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点カラーの設定
	pVtx[0].col = m_Cclor;
	pVtx[1].col = m_Cclor;
	pVtx[2].col = m_Cclor;
	pVtx[3].col = m_Cclor;

	m_pVtxBuff->Unlock();
	return S_OK;;
}
//=============================================
//生成関数
//=============================================
CBillboard * CBillboard::Create(float fHeight, float fWidth, D3DXVECTOR3 pos, char * pName)
{
	CBillboard * pObject3D = NULL;

	pObject3D = DBG_NEW CBillboard(6);
	if (pName != NULL)
	{
		CTexture * pTex = CManager::GetInstance()->GetTexture();
		
		pObject3D->m_nIdxTex[0] = pTex->Regist(pName);
	}

	pObject3D->SetHeight(fHeight);
	pObject3D->SetWidth(fWidth);
	pObject3D->SetPos(pos);
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CBillboard::Uninit(void)
{
	
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CBillboard::Update(void)
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();
	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, +m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, -m_fHeight, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(Tex_min.x, Tex_min.y);
	pVtx[1].tex = D3DXVECTOR2(Tex_max.x, Tex_min.y);
	pVtx[2].tex = D3DXVECTOR2(Tex_min.x, Tex_max.y);
	pVtx[3].tex = D3DXVECTOR2(Tex_max.x, Tex_max.y);

	//頂点カラーの設定
	pVtx[0].col = m_Cclor;
	pVtx[1].col = m_Cclor;
	pVtx[2].col = m_Cclor;
	pVtx[3].col = m_Cclor;

	m_pVtxBuff->Unlock();
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CBillboard::Draw(void)
{


	CTexture * pTex = CManager::GetInstance()->GetTexture();
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX  mtxTrans; //計算用マトリクス
	D3DXMATRIX mtxView; //ビューマトリクス取得用
	D3DXVECTOR3 pos = GetPos();


	//ライティング無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
//	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //フォグの無効化

	//Zテストを無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリクス取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;


	// ワールドマトリクスに回転行列を適用
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, GetRot().z); // Z軸周りに回転

	// ワールドマトリクスに位置変換行列も適用
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotation);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y,pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	if (m_nIdxTex != NULL)
	{
		if (m_nIdxTex >= 0)
		{
			pDevice->SetTexture(0, pTex->Getaddress(*(m_nIdxTex)));
		}
	}


	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//Zテストを有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);

	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); //フォグの有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
