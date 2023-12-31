//========================================================================================
//
// 3Dモデル(階層構造)
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "manager.h"
#include "texture.h"
#include "xfile.h"

//=============================================
//コンストラクタ
//=============================================

CModel::CModel() 
{
	m_pIdxTex = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	m_dwNumMat = 0;
	
	m_pModelName = {};
	m_pBuffMat = NULL;
	m_pParent = NULL;
	m_pMesh = NULL;
}



//=============================================
//デストラクタ
//=============================================
CModel::~CModel()
{

}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CModel::Init(void)
{
	int nNumVtx = 0; //頂点数
	DWORD dwSizeFVF; //頂点フォーマットのサイズ
	BYTE*pVtxBuff = NULL; //頂点バッファへのポインタ
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();


	CTexture * pTex = CManager::GetInstance()->GetTexture();
	CXFile * pXFile = CManager::GetInstance()->GetXFiles();
	m_nIdxXFile = pXFile->Regist(m_pModelName);
	//xファイルの読み込み
	/*if (D3DXLoadMeshFromX(m_pModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh) != D3D_OK)
	{
		return E_FAIL;
	}*/

	//頂点数を取得
	nNumVtx = pXFile->GetAddress(m_nIdxXFile)->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(pXFile->GetAddress(m_nIdxXFile)->GetFVF());

	//頂点バッファをロック
	pXFile->GetAddress(m_nIdxXFile)->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_vtxMinModel.x > vtx.x)
		{
			m_vtxMinModel.x = vtx.x;
		}
		if (m_vtxMinModel.y > vtx.y)
		{
			m_vtxMinModel.y = vtx.y;
		}
		if (m_vtxMinModel.z > vtx.z)
		{
			m_vtxMinModel.z = vtx.z;
		}
		if (m_vtxMaxModel.x < vtx.x)
		{
			m_vtxMaxModel.x = vtx.x;
		}
		if (m_vtxMaxModel.y < vtx.y)
		{
			m_vtxMaxModel.y = vtx.y;
		}
		if (m_vtxMaxModel.z < vtx.z)
		{
			m_vtxMaxModel.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;
	}
	//頂点バッファをアンロック
	pXFile->GetAddress(m_nIdxXFile)->UnlockVertexBuffer();

	//テクスチャの読み込み

	m_pIdxTex = DBG_NEW  int[(int)pXFile->GetNumMaterial(m_nIdxXFile)];
	*m_pIdxTex = -1;
	D3DXMATERIAL *pMat; //マテリアルデータへのポインタ
	pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		m_pIdxTex[nCntMat] = -1;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する時
			m_pIdxTex[nCntMat] = pTex->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	return S_OK;;
}
//=============================================
//生成関数
//=============================================
CModel * CModel::Create( char * pModelName)
{
	CModel * pObject3D = NULL;
	pObject3D = DBG_NEW  CModel();
	pObject3D->m_pModelName = pModelName;
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CModel::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//テクスチャの破棄
	if (m_pIdxTex != NULL)
	{
		delete[] m_pIdxTex;
		m_pIdxTex = NULL;
	}

}

//=============================================
//ポリゴンの更新処理
//=============================================
void CModel::Update(void)
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

}

//=============================================
//ポリゴンの描画処理
//=============================================
void CModel::Draw(void)
{

	CTexture * pTex = CManager::GetInstance()->GetTexture();
	CXFile * pXFile = CManager::GetInstance()->GetXFiles();
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス
	D3DXMATRIX mtxParent;
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL *pMat = NULL; //マテリアルデータへのポインタ

	
	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
	//ワールドマトリクスの設定
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//算出したマトリクスをかけ合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータのポインタを取得
	if (pXFile->GetMaterial(m_nIdxXFile) != NULL)
	{
		pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();

	}

	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		//if (nCntMat == 1)
		//{
		//	D3DMATERIAL9 mat;
		//	ZeroMemory(&mat, sizeof(D3DMATERIAL9));
		//	mat.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); // マテリアルの拡散色（白色）
		//	mat.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); // マテリアルの環境色（白色）
		//	mat.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); // マテリアルの鏡面反射色（白色）
		//	mat.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); // マテリアルの自己発光色（黒色）
		//	mat.Power = 32.0f; // マテリアルの鏡面反射の強さ

		//	pDevice->SetMaterial(&mat);
		//}
		
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		
	
		//テクスチャの設定
		pDevice->SetTexture(0, pTex->Getaddress(m_pIdxTex[nCntMat]));

		//モデル(パーツ)の描写
		pXFile->GetAddress(m_nIdxXFile)->DrawSubset(nCntMat);
		//m_pMesh->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);


}

