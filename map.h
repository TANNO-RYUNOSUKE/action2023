//==================
//マップヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Map_H_//二重インクルード防止のマクロ
#define _Map_H_
//インクルード
#include "main.h"
#include "object.h"
#include "objectX.h"
#include "scene.h"
#include "player.h"

class CMap
{
public:
	CMap();
	~CMap();


	static HRESULT Load(char * path,CPlayer * pPlayer);
private:

};

const float c_fObjectMinSize = 250.0f;
const int c_nObjectX = 17;
const int c_nObjectY = 10;

#endif // ! _Map_H_
