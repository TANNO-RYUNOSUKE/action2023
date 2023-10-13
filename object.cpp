//========================================================================================
//
// �I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "debugproc.h"

//�ÓI�����o�ϐ��̏�����
CObject *CObject::m_apTop[NUM_PRIORITY] = {};
CObject *CObject::m_apCur[NUM_PRIORITY] = {}; 
CObject *CObject::m_pStaticNext = NULL;
int CObject::m_nNumALL = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CObject::CObject(int nPriority)
{
	m_pNext = NULL;
	m_pPrev = NULL;
	if (nPriority >= 0 && nPriority < NUM_PRIORITY)
	{
		m_nPriority = nPriority;
		if (m_apTop[nPriority] == NULL)
		{
			m_apTop[nPriority] = this;
		}
		if (m_apCur[nPriority] == NULL)
		{
			m_apCur[nPriority] = this;
		}
		else
		{
			m_apCur[nPriority]->m_pNext = this;
			this->m_pPrev = m_apCur[nPriority];
			m_apCur[nPriority] = this;
		}
	}
	m_nNumALL++;
	/*m_nID = -1;
	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apObject[nPriority][nCnt] == NULL)
		{
			m_apObject[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_nPriority = nPriority;
			m_nNumALL++;
			break;
		}
	}*/
	m_Type = TYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 8; i++)
	{
		m_nIdxTex[i] = -1;
	}

	
}
//=============================================
//�f�X�g���N�^
//=============================================
CObject::~CObject()
{
}
//=============================================
//���������
//=============================================
void CObject::Release(void)
{
	if (m_pNext != NULL)
	{
		m_pNext->SetPrev(m_pPrev);
	}
	if (m_pPrev != NULL)
	{
		m_pPrev->SetNext(m_pNext);
	}
	if (m_apTop[m_nPriority] == this)
	{
		m_apTop[m_nPriority] = m_pNext;
	}
	if (m_apCur[m_nPriority] == this)
	{
		m_apCur[m_nPriority] = m_pPrev;
	}
	if (m_pStaticNext == this)
	{
		m_pStaticNext = m_pNext;
	}
	this->Uninit();
	delete this;

	m_nNumALL--;

}
//=============================================
//�S���������
//=============================================
void CObject::ReleaseAll(void)
{
	CObject * pObject;
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			pObject->Release();
			pObject = m_pStaticNext;
		}
	}
	m_nNumALL = 0;
}
//=============================================
//�X�V
//=============================================
void CObject::UpDateAll(void)
{
	CObject * pObject;
	CManager::GetDeb()->Print("���݂̃I�u�W�F�N�g��:%d\n", m_nNumALL);
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			pObject->Update();
			pObject = m_pStaticNext;
		}
		/*for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
		{
			if (m_apObject[nPriority][nCnt] != NULL)
			{
				m_apObject[nPriority][nCnt]->Update();
			}
		}*/
	}
}
//=============================================
//�`��
//=============================================
void CObject::DrawAll(void)
{
	CCamera * pCamera = CManager::GetScene()->GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Set();
	}
	CObject * pObject;
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			pObject->Draw();
			pObject = m_pStaticNext;
		}
	}
}

D3DXVECTOR3 CObject::GetPos() 
{ 
	return m_pos; 
}//���W�擾
