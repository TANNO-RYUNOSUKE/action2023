//==================
//3Dオブジェクトヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Pause_H_//二重インクルード防止のマクロ
#define _Pause_H_
//インクルード
#include "main.h"
#include "object.h"
#include "object2D.h"
//クラス定義
class CPause : public CObject //オブジェクトクラスの継承
{
public:

	CPause(int nPriority = 6);

	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CPause * Create();

private:
	CObject2D * m_pPause[5];
	float m_fHeigth;
	int m_nChoice;
};

#endif // ! _Pause_H_
