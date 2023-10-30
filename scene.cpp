//========================================================================================
//
// シーン
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
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

#include "map.h"
#include "pause.h"

CFade * CScene::m_pFade = NULL;
//=============================================
//コンストラクタ
//=============================================
CScene::CScene()
{
	m_Mode = MODE_NONE;
	
}
//=============================================
//デストラクタ
//=============================================
CScene::~CScene()
{
	CManager::GetInstance()->SetLightCount(0);
}
//=============================================
//生成関数
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
//タイトル
//=================================================================================================
//=============================================
//コンストラクタ
//=============================================
CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}


//=============================================
//初期化関数
//=============================================
HRESULT CTitle::Init()
{

	m_pLight = DBG_NEW CLight;
	m_pLight->Init();
	m_pCamera = DBG_NEW CCamera;
	m_pCamera->Init();
	m_pPlayer = CPlayer::Create();
	for (int i = 0; i < 3; i++)
	{
		CObjectX::Create("data\\MODEL\\corridor_ceiling.x", D3DXVECTOR3(-700.0f + 550.0f * i, -10.0f, 0.0f));
		CObjectX::Create("data\\MODEL\\corridor_wall.x", D3DXVECTOR3(-700.0f + 550.0f * i, -10.0f, 0.0f));
		CObjectX::Create("data\\MODEL\\corridor_floor.x", D3DXVECTOR3(-700.0f + 550.0f * i, -10.0f, 0.0f));
	}
	m_posDest = { -100.0f,150.0f, -250.0f };
	D3DXVECTOR3 pos ={-100.0f,100.0f,0.0f};
	m_pCamera->SetPosR(pos);
	
	m_pCamera->SetRDest(pos);
	pos.z -= 30.0f;
	pos.y += 50.0f;
	m_pCamera->SetPosV(pos);
	m_pCamera->SetVDest(pos);
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	m_pTitleLogo = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH /2 + 20.0f, SCREEN_HEIGHT/2, 0.0f),68,646,6, "data\\TEXTURE\\UI\\IronShadow.png");
	m_pTitle = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, 280.0f, 6, "data\\TEXTURE\\UI\\IS_UI_boot.png");
	
	CSound * pSound = CManager::GetInstance()->GetSound();

	pSound->Play(CSound::SOUND_LABEL_BGM000);
	pSound->Play(CSound::SOUND_LABEL_BGM_ATMOSPHERE);

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CTitle::Uninit()
{
	if (m_pCamera != NULL)
	{
		//メモリ解放
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		//メモリ解放
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
}
//=============================================
//更新関数
//=============================================
void CTitle::Update()
{ 
	m_pLight->Update();
	m_pCamera->Update();


	
	m_pCamera->SetVDest(m_pCamera->GetPosV()+ (m_posDest -m_pCamera->GetPosV()  ) * 0.01f);
	if (CManager::GetInstance()->GetDistance(m_posDest - m_pCamera->GetPosV()) < 10.0f)
	{
		m_posDest.x = -100.0f +(rand() % 1000 - 500) * 0.1f;
		m_posDest.y = 150.0f + (rand() % 500 - 250) * 0.1f;
	}

	if (rand()% 15 == 0)
	{
		m_pTitle->SetTexMin(D3DXVECTOR2(m_pTitle->GetTexMin().x, m_pTitle->GetTexMin().y + 0.02f));
		m_pTitle->SetTexMax(D3DXVECTOR2(m_pTitle->GetTexMax().x, m_pTitle->GetTexMax().y + 0.02f));

	}
	if (rand() % 120 == 0)
	{
		
		m_pTitleLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));


	}
	else 
	{
		m_pTitleLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		
	}
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInstance()->GetInputGamePad();
	
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		m_pFade->FadeOut(MODE::MODE_GAME);
	}
}
//=============================================
//描画関数
//=============================================
void CTitle::Draw()
{
	
}
//=================================================================================================
//チュートリアル
//=================================================================================================
//=============================================
//コンストラクタ
//=============================================
CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}


//=============================================
//初期化関数
//=============================================
HRESULT CTutorial::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	
	CSound * pSound = CManager::GetInstance()->GetSound();

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CTutorial::Uninit()
{

}
//=============================================
//更新関数
//=============================================
void CTutorial::Update()
{
	
	
	
}
//=============================================
//描画関数
//=============================================
void CTutorial::Draw()
{

}
//=================================================================================================
//ゲーム
//=================================================================================================



CGame::CGame()
{
}

CGame::~CGame()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CGame::Init()
{
	m_pUI = DBG_NEW CUI_System_Message;
	m_pUI->Init();
	b_Pause = false;
	m_nCnt = 0;
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	m_pCamera = DBG_NEW CCamera;
	m_pLight = DBG_NEW CLight;
	m_pPlayer = CPlayer::Create();
	m_pTimer = m_pTimer->Create();
	m_pPause = CPause::Create();
	CManager::GetInstance()->SetStageCount(1);
	CEnemy_Walker::Create(D3DXVECTOR3(6000.0f, -2500.0f, 0.0f), 10);
	CMap::Load("data\\TEXT\\map\\map_01_Rooms.csv", m_pPlayer);
	//初期化設定;
	
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	};
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	};

	


	CSound * pSound = CManager::GetInstance()->GetSound();
//	pSound->Play(CSound::SOUND_LABEL_BGM001);
	pSound->Play(CSound::SOUND_LABEL_BGM_ATMOSPHERE);


	return S_OK;
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CGame::Uninit()
{

	if (m_pCamera != NULL)
	{
		//メモリ解放
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		//メモリ解放
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pTimer != NULL)
	{
		//メモリ解放
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = NULL;
	}

	if (m_pUI != NULL)
	{
		delete m_pUI;
		m_pUI = NULL;
	}
}
//=============================================
//更新関数
//=============================================
void CGame::Update()
{
	CDebugProc * pDeb = CManager::GetInstance()->GetDeb();
	m_nCnt++;
	if (!CManager::GetInstance()->GetPause())
	{
		m_pTimer->Update();
	}
	m_pUI->Update();
	m_pCamera->Update();
	m_pLight->Update();
	m_pPause->Update();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		if (CManager::GetInstance()->GetPause())
		{
			CManager::GetInstance()->SetPause(false);
		}
		else
		{
			CManager::GetInstance()->SetPause(true);
		}
	}
	float fTime = m_pTimer->GetTimer();
	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamePad::Button_START, 0) || fTime == 0.0f)
	{
		m_pFade->FadeOut(MODE::MODE_RESULT);
	}
	
}
//=============================================
//描画関数
//=============================================
void CGame::Draw()
{
	
}

//=============================================
//座標制限
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
//コンストラクタ
//=============================================
CResult::CResult()
{
}

CResult::~CResult()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CResult::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create();
		
		m_apNumber[nCnt]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.75f + 75.0f*nCnt, SCREEN_HEIGHT * 0.45f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 75.0f);
		
	}
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\Ranking.png");
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CResult::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_apNumber[i] != NULL)
		{
			delete m_apNumber[i];
			m_apNumber[i] = NULL;
		}
		
	}
}
//=============================================
//更新関数
//=============================================
void CResult::Update()
{
	int nData = CManager::GetInstance()->GetStageCount();
	nData /=2;
	nData++;
	m_apNumber[0]->Setdata(nData % 100 / 10);
	m_apNumber[1]->Setdata(nData % 10 / 1);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START, 0))
	{
		m_pFade->FadeOut(MODE::MODE_TITLE);
	}
}
//=============================================
//描画関数
//=============================================
void CResult::Draw()
{
	
}
