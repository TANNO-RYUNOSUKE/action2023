//========================================================================================
//
// �G�l�~�[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
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
//�R���X�g���N�^,�f�X�g���N�^
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
//�R���X�g���N�^
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
//�f�X�g���N�^
//=============================================
CEnemy::~CEnemy()
{
}

//=============================================
//�������֐�
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
	m_pPointMark = m_pPointMark->Create(10.0f, 10.0f, GetPos(), "data\\TEXTURE\\Enemymark.png");



	return S_OK;
}
//=============================================
//�I���֐�
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
		delete m_apModel[nCnt]; // �|�C���^�����
		m_apModel[nCnt] = NULL;
		}
		
	}
	
}
//=============================================
//�X�V�֐�
//=============================================
void CEnemy::Update()
{
	m_pPointMark->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 150.0f, GetPos().z));

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
			SetMove(vec * 20.0f);
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
			pSound->Play(CSound::SOUND_LABEL_SE_DESTRUCT);
			pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
				for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
				{
					if (m_apModel[nCnt] != NULL)
					{
						D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[nCnt]->GetMatrix()._41, m_apModel[nCnt]->GetMatrix()._42, m_apModel[nCnt]->GetMatrix()._43);
						CDebri::Create(m_apModel[nCnt]->GetName(), pos, GetRot(), D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10), D3DXVECTOR3((rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f), 120);
					}

				}
				if (m_pPointMark != NULL)
				{
					m_pPointMark->Release();
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
//�`��֐�
//=============================================
void CEnemy::Draw()
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�t�H�[�}�b�g�̐ݒ�
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
//�����֐�
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
//�������֐�
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
//�I���֐�
//=============================================
void CEnemy_Walker::Uninit()
{

	CEnemy::Uninit();

}
//=============================================
//�X�V�֐�
//=============================================
void CEnemy_Walker::Update()
{

	CPlayer * pPlayer = NULL;
	pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();


	D3DXVECTOR3 move = GetMove(); if (m_State == STATE_NONE)
	{
		if (pPlayer != NULL)
		{
			if (pPlayer->GetState()==CPlayer::STATE_DEATH)
			{
				m_pMotion->SetType(MOVE_NONE);
			}
			else
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
		
		}
		else
		{
			m_pMotion->SetType(MOVE_NONE);
		}
		m_rotDest = CBullet::VectorToAngles(-move);
	}
	else
	{
		m_pMotion->SetType(MOVE_DAMAGE);
		m_rotDest = CBullet::VectorToAngles(move);
		SetRot(m_rotDest);
	}
	move.x *= 0.95f;//�����W��
	move.z *= 0.95f;//�����W��
	move.y -= GRAVITY;


	SetMove(move);
	if (pPlayer != NULL)
	{
		D3DXVECTOR3 max = GetPos() + GetModel()->GetPos() + GetModel()->GetMax();
		D3DXVECTOR3 min = GetPos() + GetModel()->GetPos() + GetModel()->GetMin();
		D3DXVECTOR3 pos = pPlayer->GetPos() + pPlayer->GetModelUp()->GetPos();
		if (pos.x <= max.x && pos.x >= min.x)
		{
			if (pos.y <= max.y && pos.y >= min.y)
			{
				if (pPlayer->GetInvincivl() <= 0 && pPlayer->GetState() != CPlayer::STATE_DAMAGE&& pPlayer->GetState() != CPlayer::STATE_DEATH &&  pPlayer->GetState() != CPlayer::STATE_DASH)
				{
					pPlayer->AddLife(-1);
					pPlayer->GetMotion()->SetType(CPlayer::LOWERMOTION_DAMAGE);
					pPlayer->SetState(CPlayer::STATE_DAMAGE, 15);
					D3DXVECTOR3 vec = pos - (GetPos() + GetModel()->GetPos());
					vec.y = 0.0f;
					vec.z = 0.0f;
					D3DXVec3Normalize(&vec, &vec);
					pPlayer->SetMove(pPlayer->GetMove() + vec * 50.0f);
					pPlayer->SetInvincivl(120);
					pPlayer->SetFilterDisp(6);
				}
			}
		}
	}
	

	CEnemy::Update();
}

//=============================================
//�`��֐�
//=============================================
void CEnemy_Walker::Draw()
{
	CEnemy::Draw();
}
//=============================================
//�����֐�
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

CEnemy_Drone::CEnemy_Drone() :CEnemy()
{

}

CEnemy_Drone::~CEnemy_Drone()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CEnemy_Drone::Init()
{
	CEnemy::Init();
	delete m_pMotion;
	m_pMotion = NULL;
	m_nCount = 0;
	m_nHeat = 0;
	m_bOverHeat = false;
	m_nHeat = 180;
	m_nMaxHeat = rand() % 1000 + 100;
	m_apModel[0] = m_apModel[0]->Create("data\\MODEL\\probe.x");
	pHitBox = CHitBox::Create(m_apModel[0]->GetMax(), m_apModel[0]->GetMin(), m_apModel[0]->GetPos() + GetPos());
	m_fRot = rand() % 628 - 314 * 0.01f;
	m_fLength = rand() % 1000000 * 0.1f + 200.0f;
	m_posDest = {};
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CEnemy_Drone::Uninit()
{

	CEnemy::Uninit();

}
//=============================================
//�X�V�֐�
//=============================================
void CEnemy_Drone::Update()
{

	m_nHeat--;
	if (m_nHeat <= 0)
	{
		m_nHeat = 0;
	}
	CPlayer * pPlayer = NULL;
	pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	if (m_State != STATE_DEAD)
	{
		if (pPlayer != NULL)
		{
			m_posDest.x = pPlayer->GetPos().x;
			m_posDest.y = pPlayer->GetPos().y;
			m_posDest.y += 100.0f;
			D3DXVECTOR3 vecplayer = GetMove();
		
		
			m_rotDest = D3DXVECTOR3(0.0f, atan2f(vecplayer.x, vecplayer.z), 0.0f);
		
		

			
		}
	}
	if (m_nHeat <= 0)
	{
		if (pPlayer != NULL)
		{
			D3DXVECTOR3 vecplayer;
			vecplayer = CPlayer::LinePrediction(GetPos(), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPosOld()), 30.0f) - GetPos();
			D3DXVec3Normalize(&vecplayer, &vecplayer);
			CBullet::Create(GetPos(), vecplayer * 10.0f, 150, CBullet::TYPE_ENEMY, true);;
			m_nHeat += 120;
		}
	
	}

	D3DXVECTOR3 vec = m_posDest - GetPos();
	D3DXVec3Normalize(&vec, &vec);
	SetMove(GetMove() + vec * 0.25f);

	D3DXVECTOR3 move = GetMove();
	move.x *= 0.99f;//�����W��
	move.y *= 0.99f;//�����W��
	move.z *= 0.99f;//�����W��


	SetMove(move);
	CEnemy::Update();
}

//=============================================
//�`��֐�
//=============================================
void CEnemy_Drone::Draw()
{
	CEnemy::Draw();
}


//=============================================
//�����֐�
//=============================================
CEnemy_Drone * CEnemy_Drone::Create(D3DXVECTOR3 pos, int nLife)
{

	CEnemy_Drone * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy_Drone;

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