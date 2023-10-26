//==================
//ゲートUIヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Gate_UI_H_//二重インクルード防止のマクロ
#define _Gate_UI_H_
//インクルード
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "billboard.h"
class CGate_UI :public CBillboard
{
public:
	CGate_UI();
	~CGate_UI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGate_UI * Create(D3DXVECTOR3 pos);
private:

};



#endif // ! _Gate_UI_H_
