//========================================================================================
//
// �e�N�X�`��
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "texture.h"
#include "manager.h"
#include <string.h>
//�ÓI�����o�̏�����
int CTexture::m_nNumAll = 0;

CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
		m_pNameArray[nCnt] = NULL;
	}

}

CTexture::~CTexture()
{
	for (int i = 0; i < NUM_TEXTURE; i++)
	{
		if (m_pNameArray[i] !=NULL)
		{
			delete[]  m_pNameArray[i];
			m_pNameArray[i] = NULL;
		}
	
	}
}
//=============================================
//���[�h�֐�
//=============================================
HRESULT CTexture::Load(void)
{
	return S_OK;
}
//=============================================
//�A�����[�h�֐�
//=============================================
void CTexture::Unload(void)
{
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
		m_nNumAll = 0;
	}
}
//=============================================
//�o�^�֐�
//=============================================
int CTexture::Regist(char * pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	int nIdx = m_nNumAll;

	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		if (strcmp(m_pNameArray[nCnt], pFilename) == 0)
		{
			return nCnt;
		}
	}

	if (m_apTexture[nIdx] == NULL)
	{
		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, pFilename, &m_apTexture[nIdx]);

		// �t�@�C�������R�s�[���ĕۑ�
		m_pNameArray[nIdx] = new char[strlen(pFilename) + 1];
		strcpy(m_pNameArray[nIdx], pFilename);

		m_nNumAll++;
		return nIdx;
	}
	else
	{
		return -1;
	}
}
//=============================================
//�A�h���X�擾�֐�
//=============================================
LPDIRECT3DTEXTURE9 CTexture::Getaddress(int nIdx)
{
	if (nIdx < 0 || nIdx >= NUM_TEXTURE)
	{
		return NULL;
	}

	if (m_apTexture[nIdx] != NULL)
	{
		return m_apTexture[nIdx];
	}
	return NULL;
}
