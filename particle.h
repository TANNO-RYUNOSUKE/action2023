//==================
//バレットヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Particle_H_//二重インクルード防止のマクロ
#define _Particle_H_
//インクルード
#include "main.h"
#include "effect.h"
#include"billboard.h"
#include <string>
//クラス定義effect
class CParticle:public CEffect
{
public:
	CParticle();
	~CParticle();

	HRESULT Init(void);
	void Update(void);
	static CParticle * Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, int nEffectLife,float fSize,int nSpeed,int nNum, float fAttenuation = 0.9f, std::string name = "data\\TEXTURE\\effect000.jpg");

private:
	
	int m_nSpeed;//速度
	int m_nAngle;//向き
	int m_nLife;//寿命
	int m_nEffectLife;//子の寿命
	int m_nNum;//数
	std::string m_name;
};

#endif // ! _Particle_H_