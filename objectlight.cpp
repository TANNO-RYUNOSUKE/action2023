//========================================================================================
//
// フェード
// Author: 丹野 竜之介
//
//========================================================================================
#include "objectlight.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

CObjectLight::CObjectLight()
{
	m_pLight = DBG_NEW D3DLIGHT9;
	m_nID = 0;
	*m_pLight = {};
}

CObjectLight::~CObjectLight()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CObjectLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();
	m_nID = CManager::GetLightCount() + 1;
	CManager::SetLightCount(m_nID);
	//ライトを設定する
	if (m_nID > 0)
	{
		pDevice->SetLight(m_nID, m_pLight);
		//ライトを有効にする
		pDevice->LightEnable(m_nID, TRUE);

	}
	else
	{
		CManager::SetLightCount(1);
		m_nID = 1;
		pDevice->SetLight(m_nID, m_pLight);
		//ライトを有効にする
		pDevice->LightEnable(m_nID, TRUE);
	}

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CObjectLight::Uninit()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pLight != NULL)
	{
		CManager::SetLightCount(CManager::GetLightCount()-1);
		ZeroMemory(m_pLight, sizeof(D3DLIGHT9));
		//ライトを設定する
		pDevice->SetLight(m_nID, m_pLight);

		delete m_pLight;
		m_pLight = NULL;
	}
}
//=============================================
//更新関数
//=============================================
void CObjectLight::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pLight->Position = GetPos();

	//ライトを設定する
	pDevice->SetLight(m_nID, m_pLight);
	//ライトを有効にする
	pDevice->LightEnable(m_nID, TRUE);

}
//=============================================
//描画関数
//=============================================
void CObjectLight::Draw()
{
	
}
CObjectLight * CObjectLight::Create(D3DLIGHTTYPE type, D3DXCOLOR Diffuse,D3DXVECTOR3 pos,float fRange)
{
	CObjectLight * pObj = DBG_NEW CObjectLight;
	
	pObj->GetLight()->Type = type;
	pObj->GetLight()->Diffuse = Diffuse;
	pObj->GetLight()->Position = pos;
	pObj->GetLight()->Range = fRange;
	pObj->SetPos(pos);
	
	pObj->Init();
	return pObj;
}