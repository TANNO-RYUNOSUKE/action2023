//====================================
//ライト処理
//====================================
#include "UI_System_Message.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
//====================================
//コンストラクタ、デストラクタ
//====================================
CUI_System_Message::CUI_System_Message()
{
}

CUI_System_Message::~CUI_System_Message()
{
}

//====================================
//初期化
//====================================
HRESULT CUI_System_Message::Init(void)
{
	m_nCnt = 0;
	m_nInterval = 30;
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	m_nPalam = 0;
	m_pWindow = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f), 144.0f, 315.0f, 6, "data\\TEXTURE\\UI\\Window.png");
	m_pUI[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f), 144.0f, 315.0f, 6, "data\\TEXTURE\\UI\\IS_UI_messages_0.png");
	m_pUI[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f), 144.0f, 315.0f, 6, "data\\TEXTURE\\UI\\IS_UI_messages_1.png");
	m_pUI[2] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f), 144.0f, 315.0f, 6, "data\\TEXTURE\\UI\\IS_UI_messages_2.png");
	m_pUI[3] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f, 0.0f), 144.0f, 315.0f, 6, "data\\TEXTURE\\UI\\IS_UI_messages_3.png");
	//m_pWindow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f));
	for (int i = 0; i < NUM_UI_System_Message; i++)
	{
	//	m_pUI[i]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pUI[i]->SetDisp(false);
		m_pUI[i]->SetTexMin(D3DXVECTOR2(0.0f, 0.0f));
		m_pUI[i]->SetTexMax(D3DXVECTOR2(1.0f, 0.2f));
	}
	return S_OK;
}
//====================================
//終了
//====================================
void CUI_System_Message::Uninit(void)
{

}
//====================================
//更新
//====================================
void CUI_System_Message::Update(void)
{
	m_nCnt++;
	for (int i = 0; i < NUM_UI_System_Message; i++)
	{
		m_pUI[i]->SetDisp(false);
		if (m_nPalam != i)
		{
			m_pUI[i]->SetTexMin(D3DXVECTOR2(0.0f,0.0f));
			m_pUI[i]->SetTexMax(D3DXVECTOR2(1.0f, 0.2f));
		}
	}
	m_pUI[m_nPalam]->SetDisp(true);
	if (m_nCnt >= m_nInterval)
	{
		m_nCnt = 0;
		m_nInterval = rand() % 40;
	
		m_pUI[m_nPalam]->SetTexMin(D3DXVECTOR2(m_pUI[m_nPalam]->GetTexMin().x, m_pUI[m_nPalam]->GetTexMin().y + 0.015f));
		m_pUI[m_nPalam]->SetTexMax(D3DXVECTOR2(m_pUI[m_nPalam]->GetTexMax().x, m_pUI[m_nPalam]->GetTexMax().y + 0.015f));
	}

	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pInputKeyboard->GetTrigger(DIK_UP))
	{
		m_nPalam++;
	}
	else if(pInputKeyboard->GetTrigger(DIK_DOWN))
	{
		m_nPalam--;
	}
	m_nPalam %= NUM_UI_System_Message;
	if (m_nPalam < 0)
	{
		m_nPalam = 0;
	}
}
