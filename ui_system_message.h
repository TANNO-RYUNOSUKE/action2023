//================================
//UIメッセージヘッダ
//================================
#include "main.h"
#include "object2D.h"
#ifndef _UI_System_Message_H_
#define _UI_System_Message_H_

#define NUM_UI_System_Message (4)
class CUI_System_Message
{
public:
	CUI_System_Message();
	~CUI_System_Message();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetPalam(int nData) { m_nPalam = nData; }
private:
	CObject2D * m_pWindow;
	CObject2D * m_pUI[NUM_UI_System_Message];
	int m_nPalam;
	int m_nCnt;
	int m_nInterval;
};


#endif // !_UI_System_Message_H_