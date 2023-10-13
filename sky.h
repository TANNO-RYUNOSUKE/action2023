//==================
//Xオブジェクトヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Sky_H_//二重インクルード防止のマクロ
#define _Sky_H_
//インクルード
#include "main.h"
#include "object.h"
#include "objectX.h"
//クラス定義
class CSky : public CObjectX //オブジェクトクラスの継承
{
public:

	CSky(int nPriority = 0);

	~CSky();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CSky * Create();

};

#endif // ! _Sky_H_
