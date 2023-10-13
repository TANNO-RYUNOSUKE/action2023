//==================
//�}�l�[�W���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _MANAGER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _MANAGER_H_
//�C���N���[�h
#include "main.h"
#include "scene.h"
//�O���錾
class CEnemyManager; //�G�l�~�[�}�l�[�W���[[
class CItemManager; //�G�l�~�[�}�l�[�W���[
class CXManager; //X�}�l�[�W���[
class CInputKeyboard; //�L�[�{�[�h
class CInputGamePad;//�R���g���[���[
class CInputMouse;//�}�E�X
class CPlayer;//�v���C���[
class CEnemy;//�G�l�~�[
class CDebugProc;//�f�o�b�O
class CExplosion;//����
class CRenderer;//�����_���[
class CSound;//�T�E���h
class CScore;//�X�R�A
class CCamera;//�J����
class CLight;//���C�g
class CTexture;//�e�N�X�`��
class CXFile;//X�t�@�C��
class CMeshfield;//���b�V���t�B�[���h
class CFog;//�t�H�O
class CScene;


//�N���X��`
class CManager //�}�l�[�W���N���X
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
	static CRenderer * m_pRenderer; //�����_���[�̃|�C���^
	static CInputKeyboard * m_pInputKeyboard;//�L�[�{�[�h�̃|�C���^
	static CInputGamePad * m_pInputGamepad;//�L�[�{�[�h�̃|�C���^
	static CInputMouse * m_pInputMouse;//�L�[�{�[�h�̃|�C���^
	static CDebugProc * m_pDeb;//�f�o�b�O�\���̃|�C���^
	static CSound * m_pSound;//�T�E���h�|�C���^
	static CTexture * m_pTexture;//�e�N�X�`���̃|�C���^
	static CXFile * m_pXFile;
	static CEnemyManager * m_pEnemyManager; //�G�l�~�[�}�l�[�W���̃|�C���^
	static CItemManager * m_pItemManager; //�A�C�e���}�l�[�W���̃|�C���^
	static CXManager * m_pXManager; //�G�l�~�[�}�l�[�W���̃|�C���^
	static CScene * m_pScene;//�V�[��
	static bool m_bPause;
	static int m_nHitStop;
	static int m_nScoreSave;
	static int m_nLight;
};


#endif // ! _MANAGER_H_
