//========================================================================================
//
// バレット
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "bullet.h"
#include "input.h"

#include "enemy.h"
#include "sound.h"
#include "effect.h"
#include "particle.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "player.h"

#include "objectX.h"
#include "Xmanager.h"
#include "scene.h"


LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
//=============================================
//コンストラクタ
//=============================================
CBullet::CBullet(int nPriority):CBillboard(nPriority)
{
	m_nLife = 0;
	m_fHomingPowor = 0.05f;
	m_bHoming = false;
	m_nMoveCount = 0;
	m_nHomingCount = 0;
	m_Type = TYPE_NONE;
	m_pTarget = NULL;
}
//=============================================
//デストラクタ
//=============================================
CBullet::~CBullet()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CBullet::Init()
{

	D3DXVECTOR3 pos1, pos2;
	pos1 = GetPos(); pos2 = GetPos();
	pos1.y += 10.0f;
	pos2.y -= 10.0f;
	
	CBillboard::Init();
	SetType(CObject::TYPE_BULLET);
	m_nMoveCount = 0;
	m_nHomingCount = 0;
	CTexture * pTex = CManager::GetTexture();
	
	m_nIdxTex[0] = pTex->Regist("data\\TEXTURE\\Bullet000.png");

	m_pLight = CObjectLight::Create(D3DLIGHT_POINT, D3DXCOLOR(1.0f, 0.75f, 0.3f, 1.0f), GetPos(), 400);
	m_pLight->GetLight()->Falloff = 1.0f;
	m_pLight->GetLight()->Attenuation0 = 2.0f;
	m_pLight->GetLight()->Attenuation1 = 0.0f;
	m_pLight->GetLight()->Attenuation2 = 0.0f;
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CBullet::Uninit()
{
	
	CBillboard::Uninit();
	
}
//=============================================
//更新関数
//=============================================
void CBullet::Update()
{
	m_pLight->SetPos(GetPos());
	D3DXVECTOR3 vec;
	D3DXVECTOR3 pos1, pos2;
	pos1 = GetPos(); pos2 = GetPos();

	switch (m_Type)
	{
	case CBullet::TYPE_NONE:
		break;
	case CBullet::TYPE_PLAYER:
		m_posOld = GetPos();
	
		pos1.y += 10.0f;
		pos2.y -= 10.0f;

		
		
		CollisionEnemy(GetPos());

	
		break;
	case CBullet::TYPE_ENEMY:
		pos1.y += 10.0f;
		pos2.y -= 10.0f;
	
		if (m_bHoming == true)
		{
			Homing(m_fHomingPowor);
		}
		CollisionPlayer(GetPos());
	
	
		break;
	case CBullet::TYPE_MAX:
		break;
	default:
		break;
	}

	SetPos(GetPos() + GetMove());
	m_nLife--;
	bool bRay = false;
	CXManager * pManger = CManager::GetXManager();
	CObjectX ** pObjectX = CManager::GetXManager()->GetX();
	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			if (pObjectX[i]->Ray(GetPosOld(), GetPos()))
			{

				m_nLife = 0;
				break;
			}
		}
	}
	if (m_nLife <= 0)
	{
		
	
		CParticle::Create(CBullet::GetPos(), D3DXCOLOR(0.3f, 0.6f, 1.0f, 1.0f), 1, 15, 80.0f, 30, 5,1.01f);
		CParticle::Create(CBullet::GetPos(), D3DXCOLOR(0.3f, 0.6f, 1.0f, 1.0f), 1, 15, 480.0f, 300, 1);
		
	
		if (m_pLight != NULL)
		{
			m_pLight->Release();
			m_pLight = NULL;
		}
		
		CObject::Release();
	}
	
}
//=============================================
//描画関数
//=============================================
void CBullet::Draw()
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

	
	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//aブレンディングを通常に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================================
//生成関数
//=============================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, TYPE type, bool bHoming, CEnemy ** pTag)
{
	CBullet * pBullet = NULL;
	pBullet = DBG_NEW  CBullet;
	
	pBullet->SetPos(pos);
	pBullet->m_posOld = pos;;
	pBullet->SetWidth(5.0f);
	pBullet->SetHeight(5.0f);
	pBullet->SetMove(move);
	pBullet->m_fSpeed = CManager::GetDistance(move);
	pBullet->m_Type = type;
	pBullet->m_nLife = nLife;
	pBullet->m_pTarget = pTag;
	pBullet->m_bHoming = bHoming;
	pBullet->Init();
	return pBullet;
}

void CBullet::Homing(float fPower)
{
	CPlayer * pPlayer = CManager::GetScene()->GetPlayer();
	if (pPlayer != NULL)
	{
		float fSpeed = CManager::GetDistance(GetMove());
		D3DXVECTOR3 Move = GetMove();
		D3DXVec3Normalize(&Move, &Move);
	

		D3DXVECTOR3 vec = (pPlayer->GetModelUp()->GetPos()+ pPlayer->GetPos()) - GetPos();
		D3DXVec3Normalize(&vec, &vec);

		Move = VectorToAngles(Move);
	
	
	

		D3DXVECTOR3 fRotMove, fRotDest, fRotDiff = {};
		D3DXVECTOR3 vecEnemy;
	
		vecEnemy = D3DXVECTOR3(atan2f(vec.y, sqrtf(powf(vec.x, 2.0f) + powf(vec.z, 2.0f))), atan2f(vec.x, vec.z), 0.0f);

		fRotDiff = vecEnemy - Move;
		
		
		if (fRotDiff.x < -D3DX_PI)
		{
			fRotDiff.x += D3DX_PI * 2;
		}
		else if (fRotDiff.x > D3DX_PI)
		{
			fRotDiff.x += -D3DX_PI * 2;
		}
		if (fRotDiff.y < -D3DX_PI)
		{
			fRotDiff.y += D3DX_PI * 2;
		}
		else if (fRotDiff.y > D3DX_PI)
		{
			fRotDiff.y += -D3DX_PI * 2;
		}
		Move += fRotDiff * fPower;
		Move = AnglesToVector(Move);
		Move *= m_fSpeed;
	
		SetMove(Move);
	}
}
//=============================================
//コリジョン
//=============================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{

	
	return false;
}
bool CBullet::CollisionPlayer(D3DXVECTOR3 pos)
{
	CPlayer * pPlayer = CManager::GetScene()->GetPlayer();
	if (pPlayer != NULL)
	{
		
			CModel * pModel = pPlayer->GetModelUp();


			D3DXVECTOR3 max = pModel->GetMax() + pPlayer->GetPos();
			D3DXVECTOR3 min = pModel->GetMin() + pPlayer->GetPos();

			if (pos.x <= max.x && pos.y <= max.y && pos.z <= max.z)
			{
				if (pos.x >= min.x && pos.y >= min.y && pos.z >= min.z)
				{
				
					m_nLife = 0;
					pPlayer->AddLife(-1);
					
				
					return true;
				}
			
		}
	}
	return false;
}

// ベクトルを角度に変換する関数
D3DXVECTOR3 CBullet::VectorToAngles(const D3DXVECTOR3& vector)
{
	D3DXVECTOR3 angles;

	// Yaw（ヨー）を計算
	angles.y = atan2(vector.x, vector.z);

	// Pitch（ピッチ）を計算
	angles.x = atan2(vector.y, sqrt(vector.x * vector.x + vector.z * vector.z));

	// Roll（ロール）は0度に設定
	angles.z = 0.0f;



	return angles;
}

// 角度をベクトルに変換する関数
D3DXVECTOR3 CBullet::AnglesToVector(const D3DXVECTOR3& angles)
{
	D3DXVECTOR3 vector;

	// ラジアンを度に変換
	float yaw = (angles.y);
	float pitch = (angles.x);

	// ベクトルを計算
	vector.x = sin(yaw) * cos(pitch);
	vector.y = sin(pitch);
	vector.z = cos(yaw) * cos(pitch);

	return vector;
}