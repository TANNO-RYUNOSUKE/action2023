//========================================================================================
//
// ナンバー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "Timer.h"
#include "object2D.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CTimer::CTimer()
{
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_fdata = 9000;
	m_pos = D3DXVECTOR3(1000.0f, 600.0f, 0.0f);
}



//=============================================
//デストラクタ
//=============================================
CTimer::~CTimer()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CTimer::Init(void)
{
	CObject2D::Create(D3DXVECTOR3(m_pos.x + 80.0f, m_pos.y - 5.0f, m_pos.z), 116.0f, 234.0f, 5, "data\\TEXTURE\\UI\\Timer.png");
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create();
		if (nCnt >= 3)
		{
			m_apNumber[nCnt]->Set(D3DXVECTOR3(m_pos.x + 25.0f * nCnt + 64, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f);
		}
		else
		{
			m_apNumber[nCnt]->Set(D3DXVECTOR3(m_pos.x + 50.0f * nCnt, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 50.0f);

		}
	}
	return S_OK;
}
//=============================================
//生成関数
//=============================================
CTimer * CTimer::Create(void)
{
	CTimer * pTimer = NULL;
	pTimer = DBG_NEW CTimer;
	pTimer->Init();
	return pTimer;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CTimer::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
		m_apNumber[nCnt] = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CTimer::Update(void)
{
	if (CManager::GetInstance()->GetStageCount() % 2 == 1)
	{
		m_fdata -= 1.666667f;
	}
	if (m_fdata < 0.0f)
	{
		m_fdata = 0.0f;
		for (int i = 0; i < NUM_NUMBER; i++)
		{
			m_apNumber[i]->Get2D()->SetCol(D3DXCOLOR(1.0, 0.0f, 0.0f, 1.0f));

		}
	}
	int nData = (int)m_fdata;

	m_apNumber[0]->Setdata(nData % 100000 / 10000);
	m_apNumber[1]->Setdata(nData % 10000 / 1000);
	m_apNumber[2]->Setdata(nData % 1000 / 100);
	m_apNumber[3]->Setdata(nData % 100 / 10);
	m_apNumber[4]->Setdata(nData % 10 / 1);
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CTimer::Draw(void)
{
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}

}
