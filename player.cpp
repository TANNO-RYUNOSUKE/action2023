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


//�}�N����`
#define MOVE_PLAYER (2.0f)
#define DASH_PLAYER (6.0f)
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
		CBullet::Create(D3DXVECTOR3(m_apModel[13]->GetMatrix()._41, m_apModel[13]->GetMatrix()._42, m_apModel[13]->GetMatrix()._43), -CBullet::AnglesToVector(GetRot()) * 50.0f, 6, CBullet::TYPE_PLAYER, false);
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
	if ((pInputKeyboard->GetTrigger(DIK_SPACE) || pInputKeyboard->GetTrigger(DIK_W)) && m_bLand == true)
	{
		move.y = JUMP_PLAYER;
		m_bLand = false;
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

	rot.y = atan2f(-move.x, -move.z);
	move.y -= GRAVITY;//�d�͂�^����
	move.x *= 0.9f;//�����W��
	move.z *= 0.9f;//�����W��
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