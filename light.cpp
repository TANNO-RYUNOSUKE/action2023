//====================================
//���C�g����
//====================================
#include "light.h"
#include "renderer.h"
#include "manager.h"

//====================================
//�R���X�g���N�^�A�f�X�g���N�^
//====================================
CLight::CLight()
{
}

CLight::~CLight()
{
}

//====================================
//������
//====================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir; //�ݒ�p�����x�N�g��
	//���C�g�̏����N���A����
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));
	for (int nCntLight = 0; nCntLight < NUM_LIGHT; nCntLight++)
	{
		
		//���C�g�̎�ނ̐ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		switch (nCntLight)
		{
		case 0:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.9f, 1.0f, 1.0f, 1.0f);
			vecDir = D3DXVECTOR3(-1.4f, 0.24f, -2.21f);
			break;
		case 1:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.7f, 0.8f, 0.9f, 0.6f);
			vecDir = D3DXVECTOR3(1.42f, -0.8f, 0.08f);
			break;
		case 2:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.5f, 0.6f, 0.6f, 0.2f);
			vecDir = D3DXVECTOR3(-0.59f, -0.8f, 1.55f);

		default:
			break;
		}
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
		m_aLight[nCntLight].Direction = vecDir;



		//���C�g��ݒ肷��
		pDevice->SetLight(0, &m_aLight[nCntLight]);

	}
	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	return S_OK;
}
//====================================
//�I��
//====================================
void CLight::Uninit(void)
{

}
//====================================
//�X�V
//====================================
void CLight::Update(void)
{

}