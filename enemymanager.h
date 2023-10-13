//==================
//マネージャヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _ENEMYMANAGER_H_//二重インクルード防止のマクロ
#define _ENEMYMANAGER_H_
//インクルード
#include "main.h"
#include "enemy.h"

#define NUM_ENEMY (64)//エネミーの最大数

		   //クラス定義
class CEnemyManager //マネージャクラス
{
public:
	CEnemyManager();
	~CEnemyManager();

	void Init(void);
	void Regist(CEnemy * pEnemy);
	void Release(int nID);
	CEnemy ** GetEnemy(void) { return &m_apEnemy[0]; }
	CEnemy ** GetEnemy(int nID) {
		if (nID >= 0)
		{
			return &m_apEnemy[nID];
		}
		else
		{
			return NULL;
		}
	}
	int GetNum(void) { return m_nNumALL; }
private:
	static CEnemy * m_apEnemy[NUM_ENEMY];//エネミーの配列
	int m_nNumALL;//合計数

};

#endif // ! _ENEMYMANAGER_H_
