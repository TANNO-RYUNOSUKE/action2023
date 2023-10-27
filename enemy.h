//==================
//エネミーヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _ENEMY_H_//二重インクルード防止のマクロ
#define _ENEMY_H_
//インクルード
#include "main.h"
#include "object.h"
#include "model.h"

#include "motion.h"


class CHitBox //ヒットボックス
{
public:
	CHitBox();
	~CHitBox();

	static CHitBox * Create(D3DXVECTOR3 max, D3DXVECTOR3 min, D3DXVECTOR3 pos, CHitBox * pNext = NULL);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetMax() { return m_max; }
	D3DXVECTOR3 GetMin() { return m_min; }
	CHitBox * GetNext() { return m_pNext; }
	void SetShot(int nShot) { m_nShot = nShot; }
	void SetNext(CHitBox * pHitBox) { m_pNext = pHitBox; }
	int GetShot() { return m_nShot; }
	bool GetHit() { return m_bHit; }
	void SetHt(bool bHit) { m_bHit = bHit; }
private:
	int m_nShot;
	bool m_bHit;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_pos;
	CHitBox * m_pNext;
};

//クラス定義
class CEnemy : public CObject //オブジェクトクラスの継承
{
public:
	CEnemy();
	~CEnemy();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_WALKER,
		TYPE_DORONE,
		TYPE_ELITE,
		TYPE_BOSS,
		TYPE_MAX
	};
	enum STATE
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	};

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CEnemy * Create(D3DXVECTOR3 pos,  int nLife);

	CModel *GetModel(void) { return m_apModel[0]; }

	void AddLife(int nAdd) { m_nLife += nAdd; }//ライフに加算
	CEnemy * GetThis() { return this; }

	void SetID(int nID) { m_nID = nID; }
	int GetID(void) { return m_nID; }
	void SetState(STATE State, int nCount) { m_State = State; m_nStateCount = nCount; }
	STATE GetState(void) { return m_State; }
	void Release(void);
	CHitBox * GetHitBox() { return pHitBox; }
protected:
	STATE m_State;
	D3DXVECTOR3 posOld;
	int m_nStateCount;

	int m_nLife; //体力

	D3DXVECTOR3 m_posDest;
	D3DXVECTOR3 m_rotDest;
	CMotion * m_pMotion;//モーションポインタ
	CModel * m_apModel[NUM_MODEL];//使用するモデルのポインタ
	CHitBox * pHitBox;

private:

	//CModel * m_pModel;//モデルのポインタ
	

	D3DXMATRIX m_mtxWorld; //ワールドマトリックス

	int m_nID;//ID
};

//エネミー(歩行戦車)
class CEnemy_Walker : public CEnemy
{
public:
	CEnemy_Walker();
	~CEnemy_Walker();
	enum MOVE
	{
		MOVE_NONE = 0,
		MOVE_WALK,
		MOVE_DAMAGE,
		MOVE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy_Walker * Create(D3DXVECTOR3 pos, int nLife);
private:
	MOVE m_Move;

};


#endif // ! _ENEMY_H_
