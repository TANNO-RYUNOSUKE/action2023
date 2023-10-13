//========================================================================================
//
// �t�F�[�h
// Author: �O�� ���V��
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
//�������֐�
//=============================================
HRESULT CObjectLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();
	m_nID = CManager::GetLightCount() + 1;
	CManager::SetLightCount(m_nID);
	//���C�g��ݒ肷��
	if (m_nID > 0)
	{
		pDevice->SetLight(m_nID, m_pLight);
		//���C�g��L���ɂ���
		pDevice->LightEnable(m_nID, TRUE);

	}
	else
	{
		CManager::SetLightCount(1);
		m_nID = 1;
		pDevice->SetLight(m_nID, m_pLight);
		//���C�g��L���ɂ���
		pDevice->LightEnable(m_nID, TRUE);
	}

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CObjectLight::Uninit()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pLight != NULL)
	{
		CManager::SetLightCount(CManager::GetLightCount()-1);
		ZeroMemory(m_pLight, sizeof(D3DLIGHT9));
		//���C�g��ݒ肷��
		pDevice->SetLight(m_nID, m_pLight);

		delete m_pLight;
		m_pLight = NULL;
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CObjectLight::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pLight->Position = GetPos();

	//���C�g��ݒ肷��
	pDevice->SetLight(m_nID, m_pLight);
	//���C�g��L���ɂ���
	pDevice->LightEnable(m_nID, TRUE);

}
//=============================================
//�`��֐�
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