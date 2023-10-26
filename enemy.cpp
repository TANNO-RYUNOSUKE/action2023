//========================================================================================
//
// エネミー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Enemy.h"
#include "input.h"

#include "player.h"

#include "enemymanager.h"
#include "scene.h"

#include "sound.h"
#include "objectX.h"
#include "bullet.h"
#include "camera.h"
#include "Xmanager.h"
#include "xfile.h"
#define ENEMY_MOVE (0.2f)
#define ENEMY_ACT (2.0f)
//==============================
//コンストラクタ,デストラクタ
//==============================
CHitBox::CHitBox()
{

}
CHitBox::~CHitBox()
{

}
CHitBox * CHitBox::Create(D3DXVECTOR3 max, D3DXVECTOR3 min, D3DXVECTOR3 pos, CHitBox * pNext)
{
	CHitBox * pHitBox;
	pHitBox = DBG_NEW CHitBox;
	pHitBox->m_nShot = 1;
	pHitBox->m_max = max;
	pHitBox->m_min = min;
	pHitBox->m_pos = pos;
	pHitBox->m_pNext = pNext;
	return pHitBox;
}

//=============================================
//コンストラクタ
//=============================================
CEnemy::CEnemy():CObject()
{
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CEnemyManager * pManger = CManager::GetInstance()->GetEnemyManager();
	m_pMotion = NULL;
	m_nLife = 0;
	m_nID = -1;
	pManger->Regist(this);
	if (m_nID < 0)
	{
		CObject::Release();
	}
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		m_apModel[nCnt] = NULL;
	}
	
}
//=============================================
//デストラクタ
//=============================================
CEnemy::~CEnemy()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CEnemy::Init()
{
	m_State = STATE_NONE;
	m_nStateCount = 0;
	
	m_posDest.x = GetPos().x + (float)(rand() % 2000 - 1000);
	m_posDest.z = GetPos().z + (float)(rand() % 2000 - 1000);
	m_posDest.y = GetPos().y + (float)(rand() % 200 - 100);
	
	
	m_pMotion = DBG_NEW  CMotion;
	m_pMotion->SetModel(&m_apModel[0]);
	SetType(CObject::TYPE_ENEMY);

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy::Uninit()
{
	if (pHitBox != NULL)
	{
		delete pHitBox;
		pHitBox = NULL;
	}
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt]; // ポインタを解放
		m_apModel[nCnt] = NULL;
		}
		
	}
	
}
//=============================================
//更新関数
//=============================================
void CEnemy::Update()
{

	if (m_apModel[0] != NULL)
	{
		pHitBox->SetPos(GetPos() + m_apModel[0]->GetPos());
	}

	posOld = GetPos();
	

	CSound * pSound = CManager::GetInstance()->GetSound();

	if (m_nLife <= 0 )
	{
		if (m_State != STATE_DEAD)
		{


			D3DXVECTOR3 vec = GetMove();
		
			D3DXVec3Normalize(&vec, &vec);
			vec.y = 0.1f;
			SetMove(vec * 200.0f);
			SetState(STATE_DEAD, 60);
		}
	}

	if (m_State == STATE_DEAD)
	{
	
		m_apModel[0]->SetRot(D3DXVECTOR3(m_apModel[0]->GetRot().x + 0.1f, m_apModel[0]->GetRot().y + 0.4f, m_apModel[0]->GetRot().z+0.1f ));
		
	}
	else
	{
		if (m_pMotion != NULL)
		{
			m_pMotion->Update();

		}

		

		D3DXVECTOR3 turn = m_rotDest - GetRot();
		if (turn.x < -D3DX_PI)
		{
			turn.x += D3DX_PI * 2;
		}
		else if (turn.x > D3DX_PI)
		{
			turn.x += -D3DX_PI * 2;
		}
		if (turn.y < -D3DX_PI)
		{
			turn.y += D3DX_PI * 2; 
		}
		else if (turn.y > D3DX_PI)
		{
			turn.y += -D3DX_PI * 2;
		}
		if (turn.z < -D3DX_PI)
		{
			turn.z += D3DX_PI * 2;
		}
		else if (turn.z > D3DX_PI)
		{
			turn.z += -D3DX_PI * 2;
		}
		SetRot(GetRot() + (turn * 0.2f));
	}
	SetPos(GetPos() + GetMove());
	
	m_nStateCount--;
	if (m_nStateCount <= 0)
	{
		m_nStateCount = 0;
		switch (m_State)
		{
		case CEnemy::STATE_NONE:
			break;
		case CEnemy::STATE_DAMAGE:
			m_State = STATE_NONE;
			break;
		case CEnemy::STATE_DEAD:
			
				for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
				{
					if (m_apModel[nCnt] != NULL)
					{
						D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[nCnt]->GetMatrix()._41, m_apModel[nCnt]->GetMatrix()._42, m_apModel[nCnt]->GetMatrix()._43);
						CDebri::Create(m_apModel[nCnt]->GetName(), pos, GetRot(), D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10), D3DXVECTOR3((rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f), 120);
					}

				}
		
				Release();
				return;
			break;
		default:
			m_State = STATE_NONE;
			break;
		}
	}

	CXManager * pManger = CManager::GetInstance()->GetXManager();
	CObjectX ** pObjectX = CManager::GetInstance()->GetXManager()->GetX();
	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			pObjectX[i]->Collision(posOld, GetPosAddress(), GetMoveAddress(), 200.0f, 100.0f);
		}
	}

	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	//if (pInputKeyboard->GetPress(DIK_K))
	//{
	//	m_nLife = 0;
	//}
}
//=============================================
//描画関数
//=============================================
void CEnemy::Draw()
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}

}
//=============================================
//生成関数
//=============================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, int nLife)
{
	
	CEnemy * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy;
	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	return pEnemy;
}
void CEnemy::Release(void)
{

	CManager::GetInstance()->GetEnemyManager()->Release(m_nID);

	CObject::Release();
	
}

CEnemy_Walker::CEnemy_Walker() :CEnemy()
{

}

CEnemy_Walker::~CEnemy_Walker()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CEnemy_Walker::Init()
{
	CEnemy::Init();
	m_pMotion->Load("data\\TEXT\\motion_walker.txt");
	m_pMotion->SetType(0);
	m_Move = MOVE_NONE;
	pHitBox = CHitBox::Create(m_apModel[0]->GetMax(), m_apModel[0]->GetMin(), m_apModel[0]->GetPos() + GetPos());
	m_posDest.x = GetPos().x;
	m_posDest.z = GetPos().z;
	m_posDest.y = GetPos().y;
	m_rotDest = (D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy_Walker::Uninit()
{

	CEnemy::Uninit();

}
//=============================================
//更新関数
//=============================================
void CEnemy_Walker::Update()
{

	CPlayer * pPlayer = NULL;
	pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();


	D3DXVECTOR3 move = GetMove();
	if (pPlayer != NULL)
	{
		m_pMotion->SetType(MOVE_WALK);
		if (pPlayer->GetPos().x - GetPos().x > 0.0f)
		{
			move.x += ENEMY_MOVE;
		}
		else
		{
			move.x -= ENEMY_MOVE;
		}
		
	}
	else
	{
		m_pMotion->SetType(MOVE_NONE);
	}
	m_rotDest = CBullet::VectorToAngles(-move);
	move.x *= 0.92f;//原則係数
	move.z *= 0.92f;//原則係数
	move.y -= GRAVITY;


	SetMove(move);

	CEnemy::Update();
}

//=============================================
//描画関数
//=============================================
void CEnemy_Walker::Draw()
{
	CEnemy::Draw();
}
//=============================================
//生成関数
//=============================================
CEnemy_Walker * CEnemy_Walker::Create(D3DXVECTOR3 pos, int nLife)
{

	CEnemy_Walker * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy_Walker;

	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	if (pEnemy->GetID() < 0)
	{
		pEnemy->Release();
		return NULL;
	}
	return pEnemy;
}