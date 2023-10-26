//==================
//スコアヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Timer_H_//二重インクルード防止のマクロ
#define _Timer_H_
//インクルード
#include "main.h"
#include "number.h"

//マクロ定義
#define NUM_NUMBER (5)//桁数
//クラス定義
class CTimer :public CNumber
{
public:
	CTimer();

	~CTimer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer * Create(void);

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const float fdata) { m_fdata = fdata;}
	void Add(const float fdata) { m_fdata += fdata; }
	float GetTimer(void) { return m_fdata; }

private:
	CNumber * m_apNumber[NUM_NUMBER]; //ナンバーオブジェクトへのポインタ
	float m_fdata;//持っている情報

	D3DXVECTOR3 m_pos;//一桁目の座標
};

#endif // ! _Timer_H_
