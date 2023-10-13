//========================================================================================
//
// エフェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Particle.h"
#include "input.h"

#include "enemy.h"
#include "sound.h"
#include "effect.h"

//=============================================
//コンストラクタ
//=============================================
CParticle::CParticle()
{
 	m_nAngle = 0;

	m_nSpeed = 0;
	m_nEffectLife = 0;
	m_nNum = 0;
	m_nAngle = 624;
}
//=============================================
//デストラクタ
//=============================================
CParticle::~CParticle()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CParticle::Init()
{
	SetWidth(0.0f);
	SetHeight(0.0f);
	CEffect::Init((char *)m_name.c_str());
	return S_OK;
}

//=============================================
//更新関数
//=============================================
void CParticle::Update()
{
	float fRot,fRot2;//角度
	float fMove;//移動量
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife--;
	for (int nCntParticle = 0; nCntParticle < m_nNum; nCntParticle++)
	{
		fRot = (float)(rand() % (m_nAngle * 2 - m_nAngle)) / 100.0f;
		fRot2 = (float)(rand() % (m_nAngle * 2 - m_nAngle)) / 100.0f;
		fMove = (float)(rand() % m_nSpeed) / 10.0f + 2.0f;

		move.x = cosf(fRot + GetRot().x) * sinf(fRot2 +   GetRot().y) * fMove;
		move.y = cosf(fRot + GetRot().x) * cosf(fRot2 +  GetRot().y) *fMove;
		move.z = sinf(fRot + GetRot().x) *fMove; 

		CEffect::Create(CParticle::GetPos(), move, CParticle::m_nEffectLife, CParticle::GetColor(), GetSize(),GetAttenuation(),(char*)m_name.c_str());
	}
	SetPos(GetPos() + GetMove());
	SetMove(GetMove() * 0.9f);
	if (m_nLife <= 0)
	{
		CObject::Release();
	}
}
//=============================================
//生成関数
//=============================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, int nEffectLife, float fSize, int nSpeed, int nNum, float fAttenuation , std::string name)
{
	CParticle * pParticle = NULL;
	pParticle = DBG_NEW  CParticle;
	
	pParticle->SetPos(pos);
	pParticle->SetColor(col);
	pParticle->m_nLife = nLife;
	pParticle->m_nEffectLife = nEffectLife;
	pParticle->SetSize( fSize);
	pParticle->m_nSpeed = nSpeed;
	pParticle->m_nNum = nNum;
	pParticle->SetAttenuation(fAttenuation);
	pParticle->m_name = name;
	pParticle->Init();
	
	return pParticle;
}
