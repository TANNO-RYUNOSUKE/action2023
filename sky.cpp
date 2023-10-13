//========================================================================================
//
// 3D�I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "Sky.h"
#include "objectX.h"
#include "manager.h"
#include "texture.h"
#include "Xmanager.h"

//=============================================
//�R���X�g���N�^
//=============================================

CSky::CSky(int nPriority) : CObjectX(nPriority)
{


}



//=============================================
//�f�X�g���N�^
//=============================================
CSky::~CSky()
{
}


//=============================================
//�|���S���������֐�
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
//�����֐�
//=============================================
CSky * CSky::Create()
{
	CSky * pObject3D = NULL;

	pObject3D = DBG_NEW CSky(0);
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CSky::Uninit(void)
{
	CObjectX::Uninit();
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CSky::Update(void)
{
	
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CSky::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
    pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //�t�H�O�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	CObjectX::Draw();
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); 
}

