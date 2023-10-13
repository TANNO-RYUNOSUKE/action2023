//==================
//マネージャヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _MANAGER_H_//二重インクルード防止のマクロ
#define _MANAGER_H_
//インクルード
#include "main.h"
#include "scene.h"
//前方宣言
class CEnemyManager; //エネミーマネージャー[
class CItemManager; //エネミーマネージャー
class CXManager; //Xマネージャー
class CInputKeyboard; //キーボード
class CInputGamePad;//コントローラー
class CInputMouse;//マウス
class CPlayer;//プレイヤー
class CEnemy;//エネミー
class CDebugProc;//デバッグ
class CExplosion;//爆発
class CRenderer;//レンダラー
class CSound;//サウンド
class CScore;//スコア
class CCamera;//カメラ
class CLight;//ライト
class CTexture;//テクスチャ
class CXFile;//Xファイル
class CMeshfield;//メッシュフィールド
class CFog;//フォグ
class CScene;


//クラス定義
class CManager //マネージャクラス
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hinstance,HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetPause(bool bPause) { m_bPause = bPause; }
	static void SetHitStop(int nStop) { m_nHitStop = nStop; }
	static int GetHitStop(void) { return m_nHitStop; }
	static void SetScore(int nScore) { m_nScoreSave = nScore; }
	static int GetScore(void) { return m_nScoreSave; }
	static	bool GetPause(void) { return m_bPause; }
	static void SetMode(CScene::MODE mode);
	static CScene * GetMode(void);

	static void ReSetItem(void);
	static float GetDistance(D3DXVECTOR3 vec);
	static bool RayTri(const D3DXVECTOR3& startPoint, const D3DXVECTOR3& endPoint, const D3DXVECTOR3& polypos1, const D3DXVECTOR3& polypos2, const D3DXVECTOR3& polypos3,D3DXVECTOR3 * pPos = NULL);

	static CInputKeyboard * GetInputKeyboard(void);
	static CInputGamePad * GetInputGamePad(void);
	static CInputMouse * GetInputMouse(void);
	static CRenderer * GetRenderer(void);

	static CDebugProc * GetDeb(void);
	static CSound * GetSound(void) { return m_pSound; }
	static CTexture * GetTexture(void) { return m_pTexture; }
	static CXFile * GetXFiles(void) { return m_pXFile; }
	static CEnemyManager * GetEnemyManager(void) { return m_pEnemyManager; }
	static CItemManager * GetItemManager(void) { return m_pItemManager; }
	static CXManager * GetXManager(void) { return m_pXManager; }
	static CScene * GetScene(void){ return m_pScene; }

	static int GetLightCount(void) { return m_nLight; }
	static void SetLightCount(int nCount) { m_nLight = nCount; }
private:
	static CRenderer * m_pRenderer; //レンダラーのポインタ
	static CInputKeyboard * m_pInputKeyboard;//キーボードのポインタ
	static CInputGamePad * m_pInputGamepad;//キーボードのポインタ
	static CInputMouse * m_pInputMouse;//キーボードのポインタ
	static CDebugProc * m_pDeb;//デバッグ表示のポインタ
	static CSound * m_pSound;//サウンドポインタ
	static CTexture * m_pTexture;//テクスチャのポインタ
	static CXFile * m_pXFile;
	static CEnemyManager * m_pEnemyManager; //エネミーマネージャのポインタ
	static CItemManager * m_pItemManager; //アイテムマネージャのポインタ
	static CXManager * m_pXManager; //エネミーマネージャのポインタ
	static CScene * m_pScene;//シーン
	static bool m_bPause;
	static int m_nHitStop;
	static int m_nScoreSave;
	static int m_nLight;
};


#endif // ! _MANAGER_H_
