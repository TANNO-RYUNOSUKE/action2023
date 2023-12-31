//========================================================================================
//
// プレイヤー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "player.h"
#include "input.h"

#include "debugproc.h"
#include "camera.h"

#include "camera.h"
#include "bullet.h"
#include <stdio.h>
#include "fade.h"

#include "scene.h"
#include "sound.h"
#include "objectX.h"
#include "Xmanager.h"
#include <assert.h>
#include "particle.h"
#include "enemymanager.h"
#include "enemy.h"
#include "ui_system_message.h"
#include"fake_bluescreen.h"

//マクロ定義
#define MOVE_PLAYER (2.0f)
#define DASH_PLAYER (35.0f)
#define JUMP_PLAYER (20.0f)
//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority):CObject(nPriority)
{
 	m_bLand = false;
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{		
			m_apModel[nCnt] = NULL;
	
	}

	SetType(CObject::TYPE_PLAYER);
	m_state = STATE_NEUTRAL;
	m_nStateCount = 0;
	m_nLife = 0;

	m_pFilterDamage = NULL;

}
//=============================================
//デストラクタ
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CPlayer::Init()
{
	m_fEnergy = ENERGY_MAX;
	m_nCntInvincivl = 0;
	m_pTarget = NULL;
	m_pFilterDamage = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 6, "data\\TEXTURE\\RedFilter.png");
	m_pFilterDamage->SetDisp(false);
	m_nFilter = 0;
	m_nLife = 5;

	m_apTargetUI[0] = CBillboard::Create(60.0f, 60.0f,GetPos(), "data\\TEXTURE\\UI\\target2.png");
	m_apTargetUI[1] = CBillboard::Create(60.0f, 60.0f, GetPos(), "data\\TEXTURE\\UI\\target1.png");
	for (int i = 0; i < 2; i++)					
	{
		m_apTargetUI[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	m_pMotionUp = DBG_NEW CMotion;
	m_pMotionUp->SetModel(&m_apModel[0]);

	m_pMotionUp->Load("data\\TEXT\\motion_player.txt");
	m_pLight = CObjectLight::Create(D3DLIGHT_POINT, D3DXCOLOR(1.5f, 1.5f, 1.7f, 1.0f), GetPos(), 500);
	m_pLight->GetLight()->Falloff = 100.0f;
	m_pLight->GetLight()->Attenuation0 = 2.0f;
	m_pLight->GetLight()->Attenuation1 = 0.0f;
	m_pLight->GetLight()->Attenuation2 = 0.0f;
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CPlayer::Uninit()
{
	
	
	if (m_pMotionUp != NULL)
	{
		//m_pMotionUp->Uninit();
		delete m_pMotionUp;
		m_pMotionUp = NULL;
	}

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete (m_apModel[nCnt]);
			m_apModel[nCnt] = NULL;
		}
	
	}
}
//=============================================
//更新関数
//=============================================
void CPlayer::Update()
{
	m_fEnergy += 0.01f;
	if (m_bLand == true)
	{
		m_fEnergy += 0.1f;
	}
	if (m_fEnergy >= ENERGY_MAX)
	{
		m_fEnergy = ENERGY_MAX;
	}
	
	

	m_nFilter--;
	m_nCntInvincivl--;
	m_nReload--;
	if (m_nFilter <= 0)
	{
		m_nFilter = 0;
		m_pFilterDamage->SetDisp(false);
	}
	else
	{
		m_pFilterDamage->SetDisp(true);
	}
	if (m_nCntInvincivl <0)
	{
		m_nCntInvincivl = 0;
	}
	CSound * pSound = CManager::GetInstance()->GetSound();
	CInputGamePad * pInputGamePad = CManager::GetInstance()->GetInputGamePad();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	//モーション更新

	m_pMotionUp->Update();

	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		bool bMove = false;




		CCamera * pCamera = CManager::GetInstance()->GetScene()->GetCamera();
		CDebugProc * pDeb = CManager::GetInstance()->GetDeb();


		//注視点の座標設定
		D3DXVECTOR3 seepos = GetPos();

		if (!CManager::GetInstance()->GetPause())
		{
			seepos.y += 100.0f;
			//seepos.y += 200.0f;
			m_pLight->SetPos(seepos);
			pCamera->SetRDest(seepos);
			seepos.z -= 1000.0f;
			seepos.y += 50.0f;
			pCamera->SetVDest(seepos);
		}


		pDeb->Print("WASD:移動\n");
		pDeb->Print("プレイヤーの座標(X:%f,Y:%f,Z:%f)\n", GetPos().x, GetPos().y, GetPos().z);
		pDeb->Print("プレイヤーの移動値(X:%f,Y:%f,Z:%f)\n", GetMove().x, GetMove().y, GetMove().z);
		pDeb->Print("ライトの数:%d\n", CManager::GetInstance()->GetLightCount());
		//頂点座標の設定



		SetPosOld(GetPos());//posoldの更新
		if (m_state != STATE_DEATH)
		{
			Move();
		}
	
		if (m_pTarget != NULL)
		{
			if (*m_pTarget)
			{
				for (int i = 0; i < 2; i++)
				{
					m_apTargetUI[i]->SetColor(D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f));
				}
				m_apTargetUI[0]->SetPos(D3DXVECTOR3((*m_pTarget)->GetModel()->GetMatrix()._41, (*m_pTarget)->GetModel()->GetMatrix()._42, (*m_pTarget)->GetModel()->GetMatrix()._43));
				m_apTargetUI[1]->SetPos(m_apTargetUI[1]->GetPos() +(D3DXVECTOR3((*m_pTarget)->GetModel()->GetMatrix()._41, (*m_pTarget)->GetModel()->GetMatrix()._42, (*m_pTarget)->GetModel()->GetMatrix()._43) - m_apTargetUI[1]->GetPos()) *0.2f);
				if (m_pMotionUp->GetType() != LOWERMOTION_WALK)
				{
					D3DXVECTOR3 rot = GetRot();
					rot.y = CBullet::VectorToAngles(GetPos() - (*m_pTarget)->GetPos()).y;
					SetRot(rot);
				}
			}
			else
			{
				for (int i = 0; i < 2; i++)
				{
					m_pTarget = nullptr;
					m_apTargetUI[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_apTargetUI[i]->SetPos(pCamera->GetPosV());
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				m_apTargetUI[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_apTargetUI[i]->SetPos(pCamera->GetPosV());
			}
		}
		if ((pInputKeyboard->GetPress(DIK_RETURN) || pInputGamePad->GetPress(CInputGamePad::Button_RB,0))&& m_nReload <= 0)
		{
			m_nReload = 6;
			D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[13]->GetMatrix()._41, m_apModel[13]->GetMatrix()._42, m_apModel[13]->GetMatrix()._43);
			if (m_pTarget != NULL)
			{
				if (*m_pTarget)
				{
					D3DXVECTOR3 vec = pos - ((*m_pTarget)->GetPos() + (*m_pTarget)->GetModel()->GetPos());
					D3DXVec3Normalize(&vec, &vec);
					
					for (int i = 0; i < 8; i++)
					{
						m_nReload = 30;
						CBullet::Create(pos, -vec * 50.0f, 300, CBullet::TYPE_PLAYER, false, m_pTarget);
					}
					
				}
				else
				{
					CBullet::Create(pos, -CBullet::AnglesToVector(GetRot()) * 50.0f, 30, CBullet::TYPE_PLAYER, false);
				}
			}
			else
			{
				CBullet::Create(pos, -CBullet::AnglesToVector(GetRot()) * 50.0f, 30, CBullet::TYPE_PLAYER, false);
			}

		}

	
		m_nStateCount--;
		if (m_nStateCount <= 0)
		{
			m_nStateCount = 0;
			switch (m_state)
			{
			case CPlayer::STATE_NONE:
				break;
			case CPlayer::STATE_NEUTRAL:
				break;
			case CPlayer::STATE_DASH:
				m_state = STATE_NEUTRAL;
				break;
			case CPlayer::STATE_HOVER:
				m_state = STATE_NEUTRAL;
				break;
			case CPlayer::STATE_DAMAGE:
				m_state = STATE_NEUTRAL;
				break;
			case CPlayer::STATE_DEATH:
				CManager::GetInstance()->GetScene()->SetPlayer(NULL);
				CGame::GetFade()->FadeOut(CGame::MODE_RESULT);
			

				return;
				break;
			case CPlayer::STATE_MAX:
				break;
			default:
				assert(false);
				break;
			}
		}
		
		CEnemy ** pEnemy = CManager::GetInstance()->GetEnemyManager()->GetEnemy();
		D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[0]->GetMatrix()._41, m_apModel[0]->GetMatrix()._42, m_apModel[0]->GetMatrix()._43);
		switch (m_state)
		{
		case CPlayer::STATE_NONE:
			break;
		case CPlayer::STATE_NEUTRAL:
			break;
		case CPlayer::STATE_DASH:

			for (int i = 0; i < NUM_ENEMY; i++, pEnemy++)
			{

				if (*pEnemy != NULL)
				{
					CModel * pModel = (*pEnemy)->GetModel();
					CHitBox * pHitBox = (*pEnemy)->GetHitBox();
					do
					{
						D3DXVECTOR3 max = pHitBox->GetMax() + (*pEnemy)->GetPos();
						D3DXVECTOR3 min = pHitBox->GetMin() + (*pEnemy)->GetPos();

						if (pos.x <= max.x + 100.0f && pos.y <= max.y + 100.0f && pos.z <= max.z + 100.0f)
						{
							if (pos.x >= min.x - 100.0f && pos.y >= min.y - 100.0f && pos.z >= min.z - 100.0f)
							{
								CSound * pSound = CManager::GetInstance()->GetSound();
								pSound->Play(CSound::SOUND_LABEL_SE_SLASHHIT);
								m_nCntInvincivl = 60;
								m_pMotionUp->SetType(CPlayer::LOWERMOTION_FLIP);
								(*pEnemy)->AddLife(-1);
								(*pEnemy)->SetState(CEnemy::STATE_DAMAGE, 60);
								D3DXVECTOR3 vec  = (*pEnemy)->GetPos() -GetPos();
								
								D3DXVec3Normalize(&vec, &vec);
								(*pEnemy)->SetMove((*pEnemy)->GetMove() + vec * 10.0f);
								m_state = STATE_NEUTRAL;
								m_pTarget = pEnemy;
								D3DXVECTOR3 move = GetMove();
								vec.y = 0.0f;
								vec.x *= -1.0f;
								D3DXVec3Normalize(&vec, &vec);
								vec.y = 0.75f;
								move = vec * 15.0f;
								SetMove(move);
								CParticle::Create(D3DXVECTOR3(m_apModel[1]->GetMatrix()._41, m_apModel[1]->GetMatrix()._42, m_apModel[1]->GetMatrix()._43), D3DXCOLOR(1.0f, 0.6f, 0.3f, 1.0f), 1, 15, 80.0f, 3, 5, 1.01f);
								CParticle::Create(D3DXVECTOR3(m_apModel[1]->GetMatrix()._41, m_apModel[1]->GetMatrix()._42, m_apModel[1]->GetMatrix()._43), D3DXCOLOR(1.0f, 0.6f, 0.3f, 1.0f), 1, 15, 480.0f, 30, 1);
								break;
							}
						}
						pHitBox = pHitBox->GetNext();
					} while (pHitBox != NULL);

				}

			}
			break;
		case CPlayer::STATE_HOVER:
			break;
		case CPlayer::STATE_DAMAGE:
			break;
		case CPlayer::STATE_DEATH:
			break;
		case CPlayer::STATE_MAX:
			break;
		default:
			assert(false);
			break;
		}
	}
	if (m_nLife <= 0 && m_state != STATE_DEATH)
	{
		SetState(STATE_DEATH, 300);
		for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
		{
			/*	if (m_apModelUp[nCnt] != NULL)
			{
			D3DXVECTOR3 pos = D3DXVECTOR3(m_apModelUp[nCnt]->GetMatrix()._41, m_apModelUp[nCnt]->GetMatrix()._42, m_apModelUp[nCnt]->GetMatrix()._43);
			CDebri::Create(m_apModelUp[nCnt]->GetName(), pos, GetRot(), D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10), D3DXVECTOR3((rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f), 120);
			}
			if (m_apModelLow[nCnt] != NULL)
			{
			D3DXVECTOR3 pos = D3DXVECTOR3(m_apModelLow[nCnt]->GetMatrix()._41, m_apModelLow[nCnt]->GetMatrix()._42, m_apModelLow[nCnt]->GetMatrix()._43);
			CDebri::Create(m_apModelLow[nCnt]->GetName(), pos, GetRot(), D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10), D3DXVECTOR3((rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f), 120);
			}*/
		}
		// CGame::SetPlayer(NULL);
		
		m_pMotionUp->SetType(LOWERMOTION_DEATH);
	}
}
//=============================================
//描画関数
//=============================================
void CPlayer::Draw()
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
	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	//{
	//	if (m_apModelUp[nCnt] != NULL)
	//	{
	//		m_apModelUp[nCnt]->Draw();
	//	}
	//}
}
//=============================================
//生成関数
//=============================================
CPlayer * CPlayer::Create(void)
{
	CPlayer * pPlayer = NULL;
	pPlayer = DBG_NEW CPlayer;
	pPlayer->Init();

	return pPlayer;
}
void CPlayer::Move()
{
	


	SetPosOld(GetPos());//posoldの更新

	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamePad = CManager::GetInstance()->GetInputGamePad();

	CInputMouse * pMouse = CManager::GetInstance()->GetInputMouse();

	D3DXVECTOR3 pos = GetPos();

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = GetMove();
	float fSpeed = MOVE_PLAYER;
	float fDif = 1.0f;;

	if (!m_bLand)
	{
		fSpeed *= 0.25f;
		fDif *= 0.25f;
	}
	bool bMove = false;
	float fHeight = GetHeight();
	float fWidth = GetWidth();


	//移動



		if (m_state == STATE_NEUTRAL)
		{
			if (pInputKeyboard->GetPress(DIK_A))
			{
				move.x -= fSpeed;
				bMove = true;
			}
			if (pInputKeyboard->GetPress(DIK_D))
			{
				move.x += fSpeed;
				bMove = true;
			}
			if (pInputGamePad->GetStickL(0, 0.1f) != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				move.x += pInputGamePad->GetStickL(0, 0.1f).x * fSpeed;
				bMove = true;
			}
			if (((pInputKeyboard->GetTrigger(DIK_W))  || pInputGamePad->GetTrigger(CInputGamePad::Button_A,0))&& m_bLand == true)
			{
				move.y = JUMP_PLAYER;
				m_bLand = false;
			}
		}
		if ((pInputKeyboard->GetTrigger(DIK_SPACE) || pInputGamePad->GetTrigger(CInputGamePad::Button_X,0)) && m_fEnergy >= 1.0f)
		{
			D3DXVECTOR3 vec{ 0.0f,0.0f, 0.0f };
			if (pInputKeyboard->GetPress(DIK_W))
			{
				vec.y += 0.75f;
			}
			if (pInputKeyboard->GetPress(DIK_A))
			{
				vec.y += 0.25f;
				vec.x -= 1.0f;
			}
			if (pInputKeyboard->GetPress(DIK_S))
			{
				vec.y -= 0.75f;
			}
			if (pInputKeyboard->GetPress(DIK_D))
			{
				vec.y += 0.25f;
				vec.x += 1.0f;
			}
			if (pInputGamePad->GetStickL(0,0.1f)!= D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				vec = pInputGamePad->GetStickL(0, 0.1f);
				vec.y *= -1.0f;
				vec.y += 0.25f;
			}

			if (vec.x != 0.0f)
			{
				CSound * pSound = CManager::GetInstance()->GetSound();
				pSound->Play(CSound::SOUND_LABEL_SE_HIGHSPEED);
				D3DXVec3Normalize(&vec, &vec);
				move = vec * DASH_PLAYER;
				SetState(STATE_DASH, 30);
				m_fEnergy -= 1.0f;
			}
		}
	
	if (m_pMotionUp->GetType() != LOWERMOTION_FLIP && m_pMotionUp->GetType() != LOWERMOTION_DAMAGE)
	{
		if (!m_bLand)
		{
			m_pMotionUp->SetType(CPlayer::LOWERMOTION_JUMP);
		}
		else
		{
			//歩行モーション設定
			if (bMove)
			{
				m_pMotionUp->SetType(CPlayer::LOWERMOTION_WALK);
			}
			else
			{
				m_pMotionUp->SetType(CPlayer::LOWERMOTION_NEUTRAL);
			}
		}
	}
	//ジャンプ
	if (move.x != 0 )
	{
		rot.y = atan2f(-move.x, -move.z);
	}

	switch (m_state)
	{
	case CPlayer::STATE_NONE:
		break;
	case CPlayer::STATE_NEUTRAL:
		move.y -= GRAVITY;//重力を与える
		if (m_bLand)
		{
			move.x *= 0.9f;//原則係数
			move.z *= 0.9f;//原則係数
		}
		{
			move.x *= 0.98f;//原則係数
			move.z *= 0.98f;//原則係数
		}
		break;
	case CPlayer::STATE_DASH:
		CParticle::Create(D3DXVECTOR3(m_apModel[1]->GetMatrix()._41, m_apModel[1]->GetMatrix()._42, m_apModel[1]->GetMatrix()._43), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 1, 12, 10.0f, 20, 6, 1.01f);
		move.y -= GRAVITY ;//重力を与える
		move.x *= 0.99f;//原則係数
		move.z *= 0.99f;//原則係数
		break;
	case CPlayer::STATE_HOVER:
		move.y -= GRAVITY * 0.33f;//重力を与える
		move *= 0.95f;//原則係数
		break;
	case CPlayer::STATE_MAX:
		break;
	default:
			move.x *= 0.9f;//原則係数
			move.z *= 0.9f;//原則係数
		break;
	}
	if (m_state == STATE_DASH)
	{
		
	}
	else
	{
	
	}

	SetPos(pos + move);
	if (m_pMotionUp->GetType() != LOWERMOTION_FLIP)
	{
		SetRot(rot);
	}
	else
	{
		SetRot(-rot);
	}

	SetMove(move);
	
	CXManager * pManger = CManager::GetInstance()->GetXManager();
	CObjectX ** pObjectX = CManager::GetInstance()->GetXManager()->GetX();
	m_bLand = false;
	bool bX = false;
	bool bY = false;
	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			if (m_state == STATE_DASH)
			{
				D3DXVECTOR3 move = GetMove();
				pObjectX[i]->Collision(GetPosOld(), GetPosAddress(), &move, 150.0f, 0.0f, &m_bLand, &bX, &bY);
			}
			else if (pObjectX[i]->Collision(GetPosOld(), GetPosAddress(), GetMoveAddress(), 150.0f, 0.0f, &m_bLand))
			{
				if (m_state == STATE_HOVER)
				{
					m_state = STATE_NEUTRAL;
				}
			}
		}
	}

	if (bX)
	{
		D3DXVECTOR3 move = D3DXVECTOR3(GetMove().x * -1.0f, GetMove().y, GetMove().z);
		D3DXVec3Normalize(&move, &move);
		SetMove(move * DASH_PLAYER *0.7f);
		m_state = STATE_NEUTRAL;
	
	}

	if (bY)
	{
		D3DXVECTOR3 move = D3DXVECTOR3(GetMove().x, GetMove().y * -1.0f, GetMove().z);
		D3DXVec3Normalize(&move, &move);
		SetMove(move * DASH_PLAYER*0.7f);
		m_state = STATE_NEUTRAL;
	
	}

    CItemManager * pItemmanager = CManager::GetInstance()->GetItemManager();
}
D3DXVECTOR3 CPlayer::LinePrediction(D3DXVECTOR3 shotPosition, D3DXVECTOR3 targetPosition, D3DXVECTOR3 targetPrePosition, float bulletSpeed)
{

	//目標の1フレームの移動速度
	D3DXVECTOR3 v3_Mv = targetPosition - targetPrePosition;
	//射撃する位置から見た目標位置
	D3DXVECTOR3 v3_Pos = targetPosition - shotPosition;

	//ピタゴラスの定理から２つのベクトルの長さが等しい場合の式を作り
	//二次方程式の解の公式を使って弾が当たる予測時間を計算する
	float A = (v3_Mv.x * v3_Mv.x + v3_Mv.y * v3_Mv.y + v3_Mv.z * v3_Mv.z) - bulletSpeed * bulletSpeed;
	float B = 2 * (v3_Pos.x * v3_Mv.x + v3_Pos.y * v3_Mv.y + v3_Pos.z * v3_Mv.z);
	float C = (v3_Pos.x * v3_Pos.x + v3_Pos.y * v3_Pos.y + v3_Pos.z * v3_Pos.z);

	//0割り禁止処理
	if (A == 0)
	{
		if (B == 0)
		{
			return targetPosition;
		}
		else
		{
			return targetPosition + v3_Mv * (-C / B);
		}
	}

	//弾が当たる時間のフレームを計算する
	float flame1, flame2;
	//二次方程式の解の公式の判別式で分類
	float D = B * B - 4 * A * C;
	if (D > 0)
	{
		float E = sqrtf(D);
		flame1 = (-B - E) / (2 * A);
		flame2 = (-B + E) / (2 * A);
		//解は2つなので正の数の最小値を使う
		flame1 = PlusMin(flame1, flame2);
	}
	else
	{
		//虚数解
		//当たらないので今の位置を狙う
		flame1 = 0;
	}

	//予想位置を返す
	return targetPosition + v3_Mv * flame1;
}
//プラスの最小値を返す(両方マイナスなら0)
float CPlayer::PlusMin(float a, float b)
{
	if (a < 0 && b < 0) return 0;
	if (a < 0) return b;
	if (b < 0) return a;
	return a < b ? a : b;
}
float CPlayer::CheckEnemyAngle(const D3DXVECTOR3& cameraDirection, const D3DXVECTOR3& enemyDirection)
{
	// ベクトルの正規化
	D3DXVECTOR3 normalizedCameraDir, normalizedEnemyDir;
	D3DXVec3Normalize(&normalizedCameraDir, &cameraDirection);
	D3DXVec3Normalize(&normalizedEnemyDir, &enemyDirection);
	// ベクトルの内積を計算
	float dotProduct = D3DXVec3Dot(&normalizedCameraDir, &normalizedEnemyDir);
	// ラジアンから度数法に変換して返す
	return acosf(dotProduct) * (180.0f / D3DX_PI);
}