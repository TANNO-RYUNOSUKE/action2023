//========================================================================================
//
// ゲートUI
// Author: 丹野 竜之介
//
//========================================================================================
#include "UI_first_aid.h"
#include "manager.h"
#include "renderer.h"
#include "enemymanager.h"
#include "input.h"
#include "player.h"

CUI_first_aid * CUI_first_aid::pInstance = NULL;
CUI_first_aid::CUI_first_aid() :CBillboard(6)
{
}

CUI_first_aid::~CUI_first_aid()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CUI_first_aid::Init()
{
	m_nChoice = 0;
	for (int i = 0; i < NUM_AID_UI; i++)
	{
		m_pUI[i] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * (0.4f + (0.2f * i)), SCREEN_HEIGHT * 0.7f, 0.0f), 0.0f, 127.0f, 6, "data\\TEXTURE\\UI\\box.png");
		m_pUI[i]->SetTexMin(D3DXVECTOR2(0.5*i, 0));
		m_pUI[i]->SetTexMax(D3DXVECTOR2(0.5*(i +1), 1.0f));
	}
	m_pCircle = CBillboard::Create(220.0f, 246.0f, GetPos(), "data\\TEXTURE\\UI\\RECOVERY.png");
	CBillboard::Init();
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CUI_first_aid::Uninit()
{
	for (int i = 0; i < NUM_AID_UI; i++)
	{
		if (m_pUI[i] != NULL)
		{
			
			m_pUI[i]->Release();
		}
	}
	if (m_pCircle != NULL)
	{

		m_pCircle->Release();
	}
	CBillboard::Uninit();
}
//=============================================
//更新関数
//=============================================
void CUI_first_aid::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	CInputGamePad * pInputGamePad = CManager::GetInstance()->GetInputGamePad();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	for (int i = 0; i < NUM_AID_UI; i++)
	{
		m_pUI[i]->SetCol(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	}
	m_pUI[m_nChoice]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	if (pPlayer != NULL)
	{
		if (CManager::GetInstance()->GetDistance(pPlayer->GetPos() - GetPos()) < 500.0f)
		{
			SetHeight(GetHeight() + (30.f - GetHeight()) * 0.1f);
			SetWidth(GetWidth() + (30.f - GetWidth()) * 0.1f);
			m_pCircle->SetHeight(GetHeight() + (120.f - GetHeight()) * 0.1f);
			m_pCircle->SetWidth(GetWidth() + (120.f - GetWidth()) * 0.1f);
			for (int i = 0; i < NUM_AID_UI; i++)
			{
				m_pUI[i]->SetHeight(m_pUI[i]->GetHeight() + (127.0f - m_pUI[i]->GetHeight()) * 0.1f);
			}

			if (pInputKeyboard->GetTrigger(DIK_RIGHT) || pInputGamePad->GetTrigger(CInputGamePad::Button_RIGHT, 0))
			{
				m_nChoice++;
			}
			if (pInputKeyboard->GetTrigger(DIK_LEFT) || pInputGamePad->GetTrigger(CInputGamePad::Button_LEFT, 0))
			{
				m_nChoice--;
			}
		}
		else
		{
			SetHeight(GetHeight() + (0.f - GetHeight()) * 0.1f);
			SetWidth(GetWidth() + (0.f - GetWidth()) * 0.1f);
			m_pCircle->SetHeight(GetHeight() + (0.f - GetHeight()) * 0.1f);
			m_pCircle->SetWidth(GetWidth() + (0.f - GetWidth()) * 0.1f);
			for (int i = 0; i < NUM_AID_UI; i++)
			{
				m_pUI[i]->SetHeight(m_pUI[i]->GetHeight() + (0.0f - m_pUI[i]->GetHeight()) * 0.25f);
			}
		}
	}

	m_nChoice %= NUM_AID_UI;
	if (m_nChoice < 0)
	{
		m_nChoice = NUM_AID_UI - 1;
	}
	m_pCircle->SetRot(D3DXVECTOR3(0.0f, 0.0f, m_pCircle->GetRot().z - 0.005f));

	CBillboard::Update();
	if (pPlayer != NULL)
	{
			if (CManager::GetInstance()->GetDistance(pPlayer->GetPos() - GetPos()) < 250.0f)
			{
				if (pInputKeyboard->GetTrigger(DIK_W) || pInputGamePad->GetStickL(0, 0.1f).y < -0.8f)
				{
				

				}
			}
	}
	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamePad->GetTrigger(CInputGamePad::Button_A, 0))
	{
		switch (m_nChoice)
		{
	
		case 0:
			pPlayer->AddLife(1);
			break;
		case 1:
			CManager::GetInstance()->GetScene()->GetTimer()->Add(1000);
			break;
		default:
			break;
		}
		Release();
	}
}
//=============================================
//描画関数
//=============================================
void CUI_first_aid::Draw()
{
	CBillboard::Draw();
}

CUI_first_aid * CUI_first_aid::Create(D3DXVECTOR3 pos)
{
	CUI_first_aid * pObject2D = NULL;
	pObject2D = DBG_NEW  CUI_first_aid();
	pObject2D->SetPos(pos);
	pObject2D->SetHeight(0.0f);
	pObject2D->SetWidth(0.0f);
	pObject2D->SetName("data\\TEXTURE\\UI\\Closs.png");
	pObject2D->Init();
	return pObject2D;
}