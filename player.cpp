//========================================================================================
//
// �v���C���[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
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

#include "scene.h"
#include "sound.h"
#include "objectX.h"
#include "Xmanager.h"
#include <assert.h>
#include "particle.h"
#include "enemymanager.h"
#include "enemy.h"

//�}�N����`
#define MOVE_PLAYER (2.0f)
#define DASH_PLAYER (30.0f)
#define JUMP_PLAYER (20.0f)
//=============================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CPlayer::Init()
{
	m_pTarget = NULL;
	m_pFilterDamage = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\RedFilter.png");
	m_pFilterDamage->SetDisp(false);
	
	m_nLife = 10;

	
	

	m_pMotionUp = DBG_NEW CMotion;
	m_pMotionUp->SetModel(&m_apModel[0]);

	m_pMotionUp->Load("data\\TEXT\\motion_player.txt");
	m_pLight = CObjectLight::Create(D3DLIGHT_POINT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), GetPos(), 500);
	m_pLight->GetLight()->Falloff = 100.0f;
	m_pLight->GetLight()->Attenuation0 = 2.0f;
	m_pLight->GetLight()->Attenuation1 = 0.0f;
	m_pLight->GetLight()->Attenuation2 = 0.0f;
	return S_OK;
}
//=============================================
//�I���֐�
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
//�X�V�֐�
//=============================================
void CPlayer::Update()
{
	
	CSound * pSound = CManager::GetInstance()->GetSound();
	CInputGamePad * pInputGamePad = CManager::GetInstance()->GetInputGamePad();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	//���[�V�����X�V

	m_pMotionUp->Update();


	bool bMove = false;

	


	CCamera * pCamera = CManager::GetInstance()->GetScene()->GetCamera();
	CDebugProc * pDeb = CManager::GetInstance()->GetDeb();


	//�����_�̍��W�ݒ�
	D3DXVECTOR3 seepos = GetPos();
	
	if (!CManager::GetInstance()->GetPause())
	{
		seepos.y += 100.0f;
		//seepos.y += 200.0f;
		m_pLight->SetPos(seepos);
		pCamera->SetRDest(seepos);
		seepos.z -= 750.0f;
		seepos.y += 50.0f;
		pCamera->SetVDest(seepos);
	}
	

	pDeb->Print("WASD:�ړ�\n");
	pDeb->Print("�v���C���[�̍��W(X:%f,Y:%f,Z:%f)\n", GetPos().x, GetPos().y, GetPos().z);
	pDeb->Print("�v���C���[�̈ړ��l(X:%f,Y:%f,Z:%f)\n", GetMove().x, GetMove().y, GetMove().z);
	pDeb->Print("���C�g�̐�:%d\n", CManager::GetInstance()->GetLightCount());
	//���_���W�̐ݒ�

	
	
	SetPosOld(GetPos());//posold�̍X�V
	Move();

	if (pInputKeyboard->GetTrigger(DIK_LSHIFT))
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[13]->GetMatrix()._41, m_apModel[13]->GetMatrix()._42, m_apModel[13]->GetMatrix()._43);
		if (m_pTarget != NULL)
		{
			if (*m_pTarget)
			{
				D3DXVECTOR3 vec = pos - ((*m_pTarget)->GetPos() + (*m_pTarget)->GetModel()->GetPos());
				D3DXVec3Normalize(&vec, &vec);
				CBullet::Create(pos, -vec * 50.0f, 30, CBullet::TYPE_PLAYER, false);
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

	if (m_nLife <= 0)
	{
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
		
		Release();
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
			SetState(STATE_HOVER, 60);
			break;
		case CPlayer::STATE_HOVER:
			m_state = STATE_NEUTRAL;
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
								(*pEnemy)->AddLife(-1);
								SetState(STATE_HOVER, 60);
								m_pTarget = pEnemy;
								D3DXVECTOR3 move = GetMove();
								move.y = 20.0f;
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
	case CPlayer::STATE_MAX:
		break;
	default:
		assert(false);
		break;
	}
}
//=============================================
//�`��֐�
//=============================================
void CPlayer::Draw()
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
	//���[���h�}�g���N�X�̐ݒ�
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
//�����֐�
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
	


	SetPosOld(GetPos());//posold�̍X�V

	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamePad = CManager::GetInstance()->GetInputGamePad();

	CInputMouse * pMouse = CManager::GetInstance()->GetInputMouse();

	D3DXVECTOR3 pos = GetPos();

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = GetMove();
	float fSpeed = MOVE_PLAYER;
	bool bMove = false;
	float fHeight = GetHeight();
	float fWidth = GetWidth();
	


	//�ړ�
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
		if ((pInputKeyboard->GetTrigger(DIK_W)) && m_bLand == true)
		{
			move.y = JUMP_PLAYER;
			m_bLand = false;
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_SPACE))
	{
		D3DXVECTOR3 vec{ 0.0f,0.0f, 0.0f };
		if (pInputKeyboard->GetPress(DIK_W))
		{
			vec.y += 0.5f;
		}
		if (pInputKeyboard->GetPress(DIK_A))
		{
			vec.x -= 1.0f;
		}
		if (pInputKeyboard->GetPress(DIK_S))
		{
			vec.y -= 0.5f;
		}
		if (pInputKeyboard->GetPress(DIK_D))
		{
			vec.x += 1.0f;
		}
		if (vec.x != 0.0f)
		{
			D3DXVec3Normalize(&vec, &vec);
			move = vec * DASH_PLAYER;
			SetState(STATE_DASH, 20);
		}
	}

	if (!m_bLand)
	{
		m_pMotionUp->SetType(CPlayer::LOWERMOTION_JUMP);
	}
	else
	{
		//���s���[�V�����ݒ�
		if (bMove)
		{
			m_pMotionUp->SetType(CPlayer::LOWERMOTION_WALK);
		}
		else
		{
			m_pMotionUp->SetType(CPlayer::LOWERMOTION_NEUTRAL);
		}
	}
	
	//�W�����v
	if (move.x != 0 )
	{
		rot.y = atan2f(-move.x, -move.z);
	}

	switch (m_state)
	{
	case CPlayer::STATE_NONE:
		break;
	case CPlayer::STATE_NEUTRAL:
		move.y -= GRAVITY;//�d�͂�^����
		move.x *= 0.9f;//�����W��
		move.z *= 0.9f;//�����W��
		break;
	case CPlayer::STATE_DASH:
		CParticle::Create(D3DXVECTOR3(m_apModel[13]->GetMatrix()._41, m_apModel[13]->GetMatrix()._42, m_apModel[13]->GetMatrix()._43), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 1, 12, 10.0f, 20, 6, 1.01f);
		move.x *= 0.99f;//�����W��
		move.z *= 0.99f;//�����W��
		break;
	case CPlayer::STATE_HOVER:
		move.y -= GRAVITY * 0.33f;//�d�͂�^����
		move *= 0.95f;//�����W��
		break;
	case CPlayer::STATE_MAX:
		break;
	default:

		break;
	}
	if (m_state == STATE_DASH)
	{
		
	}
	else
	{
	
	}
	SetPos(pos + move);
	SetRot(rot);
	SetMove(move);
	
	CXManager * pManger = CManager::GetInstance()->GetXManager();
	CObjectX ** pObjectX = CManager::GetInstance()->GetXManager()->GetX();
	m_bLand = false;

	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			if (pObjectX[i]->Collision(GetPosOld(), GetPosAddress(), GetMoveAddress(),&m_bLand))
			{
				if (m_state == STATE_HOVER)
				{
					m_state = STATE_NEUTRAL;
				}
			}
		}
	}
    CItemManager * pItemmanager = CManager::GetInstance()->GetItemManager();
}
D3DXVECTOR3 CPlayer::LinePrediction(D3DXVECTOR3 shotPosition, D3DXVECTOR3 targetPosition, D3DXVECTOR3 targetPrePosition, float bulletSpeed)
{

	//�ڕW��1�t���[���̈ړ����x
	D3DXVECTOR3 v3_Mv = targetPosition - targetPrePosition;
	//�ˌ�����ʒu���猩���ڕW�ʒu
	D3DXVECTOR3 v3_Pos = targetPosition - shotPosition;

	//�s�^�S���X�̒藝����Q�̃x�N�g���̒������������ꍇ�̎������
	//�񎟕������̉��̌������g���Ēe��������\�����Ԃ��v�Z����
	float A = (v3_Mv.x * v3_Mv.x + v3_Mv.y * v3_Mv.y + v3_Mv.z * v3_Mv.z) - bulletSpeed * bulletSpeed;
	float B = 2 * (v3_Pos.x * v3_Mv.x + v3_Pos.y * v3_Mv.y + v3_Pos.z * v3_Mv.z);
	float C = (v3_Pos.x * v3_Pos.x + v3_Pos.y * v3_Pos.y + v3_Pos.z * v3_Pos.z);

	//0����֎~����
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

	//�e�������鎞�Ԃ̃t���[�����v�Z����
	float flame1, flame2;
	//�񎟕������̉��̌����̔��ʎ��ŕ���
	float D = B * B - 4 * A * C;
	if (D > 0)
	{
		float E = sqrtf(D);
		flame1 = (-B - E) / (2 * A);
		flame2 = (-B + E) / (2 * A);
		//����2�Ȃ̂Ő��̐��̍ŏ��l���g��
		flame1 = PlusMin(flame1, flame2);
	}
	else
	{
		//������
		//������Ȃ��̂ō��̈ʒu��_��
		flame1 = 0;
	}

	//�\�z�ʒu��Ԃ�
	return targetPosition + v3_Mv * flame1;
}
//�v���X�̍ŏ��l��Ԃ�(�����}�C�i�X�Ȃ�0)
float CPlayer::PlusMin(float a, float b)
{
	if (a < 0 && b < 0) return 0;
	if (a < 0) return b;
	if (b < 0) return a;
	return a < b ? a : b;
}
float CPlayer::CheckEnemyAngle(const D3DXVECTOR3& cameraDirection, const D3DXVECTOR3& enemyDirection)
{
	// �x�N�g���̐��K��
	D3DXVECTOR3 normalizedCameraDir, normalizedEnemyDir;
	D3DXVec3Normalize(&normalizedCameraDir, &cameraDirection);
	D3DXVec3Normalize(&normalizedEnemyDir, &enemyDirection);
	// �x�N�g���̓��ς��v�Z
	float dotProduct = D3DXVec3Dot(&normalizedCameraDir, &normalizedEnemyDir);
	// ���W�A������x���@�ɕϊ����ĕԂ�
	return acosf(dotProduct) * (180.0f / D3DX_PI);
}