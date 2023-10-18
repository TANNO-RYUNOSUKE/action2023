//========================================================================================
//
// �}�l�[�W��
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "objectX.h"
#include "billboard.h"
#include "texture.h"
#include "scene.h"
#include "xfile.h"
#include "Xmanager.h"
#include "enemymanager.h"
#include "map.h"

CManager * CManager::pInstance = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CManager::CManager()
{
	
	
}
//=============================================
//�f�X�g���N�^
//=============================================
CManager::~CManager()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	m_pScene = NULL;
	m_bPause = false;
	m_pRenderer = DBG_NEW CRenderer;
	m_pInputKeyboard = DBG_NEW CInputKeyboard;
	m_pInputGamepad = DBG_NEW CInputGamePad;
	m_pInputMouse = DBG_NEW CInputMouse;
	m_pDeb = DBG_NEW CDebugProc;
	m_pSound = DBG_NEW CSound;
	m_pTexture = DBG_NEW CTexture;
	m_pXFile = DBG_NEW CXFile;
	m_pEnemyManager = DBG_NEW CEnemyManager;
	m_pEnemyManager->Init();
	m_pXManager = DBG_NEW CXManager;
	m_pXManager->Init();
	//�������ݒ�;
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	};
	if (FAILED(m_pInputKeyboard->Init(hinstance,hWnd)))
	{
		return -1;
	};
	if (FAILED(m_pInputGamepad->Init(hinstance, hWnd)))
	{
		return -1;
	};
	if (FAILED(m_pInputMouse->Init(hinstance, hWnd)))
	{
		return -1;
	};
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return -1;
	};



	m_pDeb->Init();


	
	



	SetMode(CScene::MODE::MODE_TITLE);

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CManager::Uninit()
{

	CObject::ReleaseAll();
	
	m_pSound->Stop();

	if (m_pRenderer != NULL)
	{//���������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pInputKeyboard != NULL)
	{//���������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	if (m_pInputGamepad != NULL)
	{
		//���������
		m_pInputGamepad->Uninit();
		delete m_pInputGamepad;
		m_pInputGamepad = NULL;
	}
	if (m_pInputMouse != NULL)
	{
		//���������
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}
	if (m_pSound != NULL)
	{
		//���������
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	if (m_pDeb != NULL)
	{
		//���������
		m_pDeb->Uninit();
		delete m_pDeb;
		m_pDeb = NULL;
	}
	if (m_pTexture != NULL)
	{
		//���������
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = NULL;
	}
	if (m_pXFile != NULL)
	{
		//���������
		m_pXFile->Unload();
		delete m_pXFile;
		m_pXFile = NULL;
	}
	
	if (m_pXManager != NULL)
	{
		//���������
		delete m_pXManager;
		m_pXManager = NULL;
	}if (m_pEnemyManager != NULL)
	{
		//���������
		delete m_pEnemyManager;
		m_pEnemyManager = NULL;
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CManager::Update()
{
	//�X�V����
	m_pInputKeyboard->Update();
	m_pInputGamepad->Update();
	m_pInputMouse->Update();
	if (m_bPause != true && m_nHitStop <= 0)
	{
		m_pRenderer->Update();
		m_pDeb->Update();
	}
	else
	{
		m_pScene->Update();
	}
	m_nHitStop--;
}
//=============================================
//�`��֐�
//=============================================
void CManager::Draw()
{
	//�X�V����

	m_pRenderer->Draw();
	
}
//=============================================
//���[�h�ݒ�
//=============================================
void CManager::SetMode(CScene::MODE mode)
{
	m_bPause = false;
	m_nHitStop = 0;
	m_pSound->Stop();
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}
	
	CObject::ReleaseAll();
	m_pScene = CScene::Create(mode);
	
}
//=============================================
//�|���S���ւ̃��C�֐�
//=============================================
bool CManager::RayTri(const D3DXVECTOR3& startPoint, const D3DXVECTOR3& endPoint, const D3DXVECTOR3& polypos1, const D3DXVECTOR3& polypos2, const D3DXVECTOR3& polypos3,D3DXVECTOR3 * pPos)
{
	// ���C�̍쐬
	D3DXVECTOR3 rayOrigin = startPoint;
	D3DXVECTOR3 rayDirection = endPoint - startPoint;
	bool isIntersecting = false;
	float u, v, distance;
	distance = -1.0f;
	D3DXIntersectTri(
		&polypos1,          // �|���S���̒��_0�̍��W
		&polypos2,          // �|���S���̒��_1�̍��W
		&polypos3,          // �|���S���̒��_2�̍��W
		&rayOrigin,         // ���C�̎n�_�̍��W
		&rayDirection,      // ���C�̕����x�N�g��
		&u,                 // �����_�̏d�� u
		&v,                 // �����_�̏d�� v
		&distance           // ���C�ƃ|���S���̋���
	);

	// ���C�ƃ|���S�����������Ă��邩�ǂ����𔻒�
	if (distance >= 0.0f && distance <= 1.0f)
	{
		// ���C�ƃ|���S�����������Ă���
		isIntersecting = true;
		if (pPos != NULL)
		{
			*pPos = rayOrigin + rayDirection * distance;
		}
	
	}
	else
	{
		// ���C�ƃ|���S�����������Ă��Ȃ�
		isIntersecting = false;
	}
	return isIntersecting;
}

//=============================================
//�����擾�֐�
//=============================================
float CManager::GetDistance(D3DXVECTOR3 vec)
{
	if (vec.x < 0.0f)
	{
		vec.x *= -1.0f;
	}
	if (vec.y < 0.0f)
	{
		vec.y *= -1.0f;
	}
	if (vec.z < 0.0f)
	{
		vec.z *= -1.0f;
	}
	float fDis = vec.x + vec.y + vec.z;
	return fDis;
}
//=============================================
//�����_���[�̎擾
//=============================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//=============================================
//�L�[�{�[�h�擾
//=============================================
CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//=============================================
//�R���g���[���[�擾
//=============================================
CInputGamePad * CManager::GetInputGamePad(void)
{
	return m_pInputGamepad;
}
//=============================================
//�}�E�X�擾
//=============================================
CInputMouse * CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//=============================================
//�f�o�b�O�v���V�[�W���擾
//=============================================
CDebugProc * CManager::GetDeb(void)
{
	return m_pDeb;
}

