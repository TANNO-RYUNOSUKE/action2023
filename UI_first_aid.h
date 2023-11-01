//==================
//ゲートUIヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _UI_first_aid_H_//二重インクルード防止のマクロ
#define _UI_first_aid_H_
//インクルード
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "billboard.h"

#define NUM_AID_UI (2)

class CUI_first_aid :public CBillboard
{
public:
	CUI_first_aid();
	~CUI_first_aid();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUI_first_aid * GetInstance() {
		if (pInstance == NULL) { pInstance = Create(D3DXVECTOR3(0.0f,0.0f,0.0f)); return pInstance; }
		else
		{
			return pInstance;
		}
	}

	static CUI_first_aid * CUI_first_aid::Create(D3DXVECTOR3 pos);

private:
	static CUI_first_aid * pInstance;
	int m_nChoice;
	CObject2D * m_pUI[NUM_AID_UI];
	CBillboard * m_pCircle;
};



#endif // ! _UI_first_aid_H_
