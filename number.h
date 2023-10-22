//==================
//ナンバーヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _NUMBER_H_//二重インクルード防止のマクロ
#define _NUMBER_H_
//インクルード
#include "main.h"


//前方宣言
class CObject2D;

//クラス定義
class CNumber
{
public:
	CNumber();

	~CNumber();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber * Create(int nType = 0);

	

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	CObject2D * Get2D(void) { return m_pObbject; }
	void Setdata(const int ndata) { m_ndata = ndata; }
	void SetDisp(const bool bDisp) { m_bDisp = bDisp; }
private:
	bool m_bDisp;
	int m_nType;
	CObject2D * m_pObbject; //2Dオブジェクトへのポインタ
	int m_ndata;//持っている情報

};

#endif // ! _Number_H_
