//========================================================================================
//
// �V�[��
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "scene.h"

#include "camera.h"
#include "light.h"


#include "input.h"

#include "sound.h"
#include "debugproc.h"	
#include "fade.h"
#include "player.h"
#include "objectX.h"
#include "enemy.h"

CFade * CScene::m_pFade = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CScene::CScene()
{
	m_Mode = MODE_NONE;
	
}
//=============================================
//�f�X�g���N�^
//=============================================
CScene::~CScene()
{
	CManager::SetLightCount(0);
}
//=============================================
//�����֐�
//=============================================
CScene * CScene::Create(MODE mode)
{
	CScene * pScene = NULL;
	switch (mode)
	{
	case CScene::MODE_TITLE:
		pScene = DBG_NEW CTitle;
		break;
	case CScene::MODE_TUTORIAL:
		pScene = DBG_NEW CTutorial;
		break;
	case CScene::MODE_GAME:
		pScene = DBG_NEW CGame;
		break;
	case CScene::MODE_RESULT:
		pScene = DBG_NEW CResult;
		break;
	default:
		break;
	}

	pScene->SetMode(mode);

	pScene->Init();

	return pScene;
}
//=================================================================================================
//�^�C�g��
//=================================================================================================
//=============================================
//�R���X�g���N�^
//=============================================
CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}


//=============================================
//�������֐�
//=============================================
HRESULT CTitle::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT/2, 0.0f),SCREEN_HEIGHT,SCREEN_WIDTH,0, "data\\TEXTURE\\TITLE\\lab1.png");
	m_pTitle = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f), 305.0f, 600.0f, 0, "data\\TEXTURE\\TITLE\\lab2.png");
	m_posDest = D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f);
	CSound * pSound = CManager::GetSound();
	//pSound->Play(CSound::SOUND_LABEL_BGM000);
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CTitle::Uninit()
{

}
//=============================================
//�X�V�֐�
//=============================================
void CTitle::Update()
{
	
	m_pTitle->SetPos(m_pTitle->GetPos() + (m_posDest - m_pTitle->GetPos()) / 120);
	if (CManager::GetDistance((m_pTitle->GetPos() - m_posDest)) <= 10.0f)
	{
		m_posDest = D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f);
	
		m_posDest.x += rand() % 100 - 50;
	}
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		m_pFade->FadeOut(MODE::MODE_GAME);
	}
}
//=============================================
//�`��֐�
//=============================================
void CTitle::Draw()
{
	
}
//=================================================================================================
//�`���[�g���A��
//=================================================================================================
//=============================================
//�R���X�g���N�^
//=============================================
CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}


//=============================================
//�������֐�
//=============================================
HRESULT CTutorial::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();

	CSound * pSound = CManager::GetSound();

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CTutorial::Uninit()
{

}
//=============================================
//�X�V�֐�
//=============================================
void CTutorial::Update()
{
	
	
	
}
//=============================================
//�`��֐�
//=============================================
void CTutorial::Draw()
{

}
//=================================================================================================
//�Q�[��
//=================================================================================================



CGame::CGame()
{
}

CGame::~CGame()
{
}
//=============================================
//�������֐�
//=============================================
HRESULT CGame::Init()
{
	
	b_Pause = false;
	m_nCnt = 0;
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	m_pCamera = DBG_NEW CCamera;
	m_pLight = DBG_NEW CLight;
	m_pPlayer = CPlayer::Create();
	CEnemy_Walker::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10);
	CObjectX::Create("data\\MODEL\\floor.x", D3DXVECTOR3(0.0f, -1000.0f, 0.0f));
	//�������ݒ�;
	
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	};
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	};

	


	CSound * pSound = CManager::GetSound();
	//pSound->Play(CSound::SOUND_LABEL_BGM001);


	return S_OK;
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CGame::Uninit()
{

	if (m_pCamera != NULL)
	{
		//���������
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		//���������
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}



}
//=============================================
//�X�V�֐�
//=============================================
void CGame::Update()
{
	CDebugProc * pDeb = CManager::GetDeb();
	m_nCnt++;

	m_pCamera->Update();
	m_pLight->Update();

	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		if (CManager::GetPause())
		{
			CManager::SetPause(false);
		}
		else
		{
			CManager::SetPause(true);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamePad::Button_START, 0))
	{
		m_pFade->FadeOut(MODE::MODE_RESULT);
	}
	
}
//=============================================
//�`��֐�
//=============================================
void CGame::Draw()
{
	
}

//=============================================
//���W����
//=============================================
void CGame::positionLimiter(D3DXVECTOR3* pos)
{
	if (pos->x > MAX_X)
	{
		pos->x = MAX_X;
	}
	else if (pos->x < -MAX_X)
	{
		pos->x = -MAX_X;
	}

	if (pos->y > MAX_Y)
	{
		pos->y = MAX_Y;
	}
	else if (pos->y < 0)
	{
		pos->y = 0.0f;
	}
	

	if (pos->z > MAX_Z)
	{
		pos->z = MAX_Z;
	}
	else if (pos->z < -MAX_Z)
	{
		pos->z = -MAX_Z;
	}
}
//=================================================================================================
//result
//=================================================================================================
//=============================================
//�R���X�g���N�^
//=============================================
CResult::CResult()
{
}

CResult::~CResult()
{
}
//=============================================
//�������֐�
//=============================================
HRESULT CResult::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\Ranking.png");
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CResult::Uninit()
{
	
}
//=============================================
//�X�V�֐�
//=============================================
void CResult::Update()
{

	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START, 0))
	{
		m_pFade->FadeOut(MODE::MODE_TITLE);
	}
}
//=============================================
//�`��֐�
//=============================================
void CResult::Draw()
{
	
}
