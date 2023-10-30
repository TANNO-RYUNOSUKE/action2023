//========================================================================================
//
// アイテム
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Pause.h"
#include "input.h"

#include "sound.h"

#include "fade.h"

 char *c_apPause[] =
{
	"data\\TEXTURE\\PAUSE\\Pause0.png",
	"data\\TEXTURE\\PAUSE\\Pause1.png",
	"data\\TEXTURE\\PAUSE\\Pause2.png",
	"data\\TEXTURE\\PAUSE\\Pause3.png",
	"data\\TEXTURE\\PAUSE\\Cursor.png",
};

//=============================================
//コンストラクタ
//=============================================
CPause::CPause(int nPriority) :CObject(nPriority)
{
	for (int i = 0; i < 5; i++)
	{
		m_pPause[i] = NULL;
	}
}
//=============================================
//デストラクタ
//=============================================
CPause::~CPause()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CPause::Init()
{
	m_nChoice = 0;
	m_pPause[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 269.0f, 1280.0f, 6, c_apPause[0]);
	m_pPause[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + -80.0f, 0.0f), 54.0f, 101.0f, 6, c_apPause[1]);
	m_pPause[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 63.0f, 81.0f, 6, c_apPause[2]);
	m_pPause[3] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f), 54.0f, 143.0f, 6, c_apPause[3]);
	m_pPause[4] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + -78.0f, 0.0f), 59.0f, 197.0f, 6, c_apPause[4]);

	m_fHeigth = m_pPause[0]->GetHeight();

	for (int i = 0; i < 5; i++)
	{
		m_pPause[i]->SetDisp(false);
	}

	for (int i = 1; i < 4; i++)
	{
		m_pPause[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CPause::Uninit()
{
	
}
//=============================================
//更新関数
//=============================================
void CPause::Update()
{
	if (CManager::GetInstance()->GetPause())
	{

		CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
		CInputGamePad * pInputGamepad = CManager::GetInstance()->GetInputGamePad();
		CInputMouse * pInputMousee = CManager::GetInstance()->GetInputMouse();
		for (int i = 0; i < 5; i++)
		{
			m_pPause[i]->Update();
			
		}
		m_pPause[0]->SetDisp(true);
		m_pPause[0]->SetHeight(m_pPause[0]->GetHeight() + (m_fHeigth - m_pPause[0]->GetHeight()) /6);
		if (m_pPause[0]->GetHeight() - m_fHeigth > -1.0f)
		{
			for (int i = 1; i < 5; i++)
			{
				if (m_pPause[i-1]->GetCol().a > 0.9f)
				{
					m_pPause[i]->SetDisp(true);
					m_pPause[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_pPause[i]->GetCol().a + (1.0f - m_pPause[i]->GetCol().a) / 6));
				}
			}
		}
		m_pPause[4]->SetPos(m_pPause[4]->GetPos() + ( m_pPause[m_nChoice + 1]->GetPos() - m_pPause[4]->GetPos()) / 3);
		
		if (pInputKeyboard->GetTrigger(DIK_UP) || pInputGamepad->GetTrigger(CInputGamePad::Button_UP, 0)|| pInputMousee->GetMove().z < -100.0f)
		{
			m_nChoice--;
		}
		else if (pInputKeyboard->GetTrigger(DIK_DOWN) || pInputGamepad->GetTrigger(CInputGamePad::Button_DOWN, 0) || pInputMousee->GetMove().z > 100.0f)
		{
			m_nChoice++;
		}
		else if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamePad::Button_A, 0) || pInputMousee->GetTrigger(CInputMouse::MOUSE_LEFT))
		{
			switch (m_nChoice)
			{
			case 0:
				CManager::GetInstance()->SetPause(false);
				break;
			case 1:
				CGame::GetFade()->FadeOut(CScene::MODE_GAME);
				CManager::GetInstance()->SetPause(false);
				break;
			case 2:
				CGame::GetFade()->FadeOut(CScene::MODE_TITLE);
				CManager::GetInstance()->SetPause(false);
				break;
			default:
				break;
			}
		}
		if (m_nChoice < 0)
		{
			m_nChoice = 2;
		}
		m_nChoice %= 3;
	}
	else
	{
		for (int i = 1; i < 5; i++)
		{
			m_pPause[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		for (int i = 0; i < 5; i++)
		{
			m_pPause[i]->SetDisp(false);
		}

		m_pPause[0]->SetHeight(0.0f);
	}
}
//=============================================
//描画関数
//=============================================
void CPause::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		m_pPause[i]->Draw();
	}
}
//=============================================
//生成関数
//=============================================
CPause * CPause::Create()
{
	CPause * pPause = NULL;
	pPause = DBG_NEW CPause;
	
	pPause->Init();
	return pPause;
}
