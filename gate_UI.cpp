//========================================================================================
//
// ゲートUI
// Author: 丹野 竜之介
//
//========================================================================================
#include "Gate_UI.h"
#include "manager.h"
#include "renderer.h"
#include "enemymanager.h"
#include "input.h"
#include "player.h"
#include "map.h"

 char *c_apMapPath[] =					//マップデータ読み込み
{
	"data\\TEXT\\map\\map_01_Rooms.csv",
	"data\\TEXT\\map\\map_02_Twin.csv",
	"data\\TEXT\\map\\map_03_Step.csv",
	"data\\TEXT\\map\\map_04_Rooms2.csv",
};

#define MAP_CORRIDOR ("data\\TEXT\\map\\map_00_Corridor.csv")



CGate_UI::CGate_UI() :CBillboard(6)
{
}

CGate_UI::~CGate_UI()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CGate_UI::Init()
{
	
	CBillboard::Init();
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CGate_UI::Uninit()
{
	CBillboard::Uninit();
}
//=============================================
//更新関数
//=============================================
void CGate_UI::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	CInputGamePad * pInputGamePad = CManager::GetInstance()->GetInputGamePad();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pPlayer != NULL)
	{
		if (CManager::GetInstance()->GetDistance(pPlayer->GetPos() - GetPos()) < 500.0f)
		{
			SetHeight(GetHeight() + (50.f - GetHeight()) * 0.1f);
			SetWidth(GetWidth() + (50.f - GetWidth()) * 0.1f);
		}
		else
		{
			SetHeight(GetHeight() + (0.f - GetHeight()) * 0.1f);
			SetWidth(GetWidth() + (0.f - GetWidth()) * 0.1f);
		}
	}

	int nEnemy = CManager::GetInstance()->GetEnemyManager()->GetNum();
	if (nEnemy > 0)
	{
		SetTexMin(D3DXVECTOR2(0.0f, 0.5f));
		SetTexMax(D3DXVECTOR2(1.0f, 1.0f));
	}
	else
	{
		SetTexMin(D3DXVECTOR2(0.0f, 0.0f));
		SetTexMax(D3DXVECTOR2(1.0f, 0.5f));
	}
	CBillboard::Update();
	if (pPlayer != NULL)
	{
		if (nEnemy <= 0)
		{
			if (CManager::GetInstance()->GetDistance(pPlayer->GetPos() - GetPos()) < 250.0f)
			{
				if (pInputKeyboard->GetTrigger(DIK_W) || pInputGamePad->GetStickL(0,0.1f).y < -0.8f)
				{
					Release();
					CManager::GetInstance()->SetStageCount(CManager::GetInstance()->GetStageCount() + 1);
					if (CManager::GetInstance()->GetStageCount() % 2 != 0)
					{
						int nRand = rand() % 4;
						CMap::Load(c_apMapPath[nRand], pPlayer);
					}
					else
					{
						CMap::Load("data\\TEXT\\map\\map_00_Corridor.csv", pPlayer);
					}

				}
			}
		}
	}
}
//=============================================
//描画関数
//=============================================
void CGate_UI::Draw()
{
	CBillboard::Draw();
}

CGate_UI * CGate_UI::Create(D3DXVECTOR3 pos)
{
	CGate_UI * pObject2D = NULL;
	pObject2D = DBG_NEW  CGate_UI();
	pObject2D->SetPos(pos);
	pObject2D->SetHeight(0.0f);
	pObject2D->SetWidth(0.0f);
	pObject2D->SetName("data\\TEXTURE\\UI\\gate.png");
	pObject2D->Init();
	return pObject2D;
}