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

	 void SetPause(bool bPause) { m_bPause = bPause; }
	 void SetHitStop(int nStop) { m_nHitStop = nStop; }
	 int GetHitStop(void) { return m_nHitStop; }
	 void SetScore(int nScore) { m_nScoreSave = nScore; }
	 int GetScore(void) { return m_nScoreSave; }
		bool GetPause(void) { return m_bPause; }
	 void SetMode(CScene::MODE mode);
	 CScene * GetMode(void);

	 void ReSetItem(void);
	 float GetDistance(D3DXVECTOR3 vec);
	 bool RayTri(const D3DXVECTOR3& startPoint, const D3DXVECTOR3& endPoint, const D3DXVECTOR3& polypos1, const D3DXVECTOR3& polypos2, const D3DXVECTOR3& polypos3,D3DXVECTOR3 * pPos = NULL);

	 CInputKeyboard * GetInputKeyboard(void);
	 CInputGamePad * GetInputGamePad(void);
	 CInputMouse * GetInputMouse(void);
	 CRenderer * GetRenderer(void);

	 CDebugProc * GetDeb(void);
	 CSound * GetSound(void) { return m_pSound; }
	 CTexture * GetTexture(void) { return m_pTexture; }
	 CXFile * GetXFiles(void) { return m_pXFile; }
	 CEnemyManager * GetEnemyManager(void) { return m_pEnemyManager; }
	 CItemManager * GetItemManager(void) { return m_pItemManager; }
	 CXManager * GetXManager(void) { return m_pXManager; }
	 CScene * GetScene(void){ return m_pScene; }

	 int GetLightCount(void) { return m_nLight; }
	 void SetLightCount(int nCount) { m_nLight = nCount; }
	 int GetStageCount(void) { return m_nStageCount; }
	 void SetStageCount(int nCount) { m_nStageCount = nCount; }

	 static CManager * GetInstance() {
		 if (pInstance == NULL) { pInstance = DBG_NEW CManager; return pInstance; }
		 else
		 {
			 return pInstance;
		 }
	 }
private:
	static CManager * pInstance;
	CRenderer * m_pRenderer; //�����_���[�̃|�C���^
	CInputKeyboard * m_pInputKeyboard;//�L�[�{�[�h�̃|�C���^
	CInputGamePad * m_pInputGamepad;//�L�[�{�[�h�̃|�C���^
	CInputMouse * m_pInputMouse;//�L�[�{�[�h�̃|�C���^
	CDebugProc * m_pDeb;//�f�o�b�O�\���̃|�C���^
	CSound * m_pSound;//�T�E���h�|�C���^
	CTexture * m_pTexture;//�e�N�X�`���̃|�C���^
	CXFile * m_pXFile;
	CEnemyManager * m_pEnemyManager; //�G�l�~�[�}�l�[�W���̃|�C���^
	CItemManager * m_pItemManager; //�A�C�e���}�l�[�W���̃|�C���^
	CXManager * m_pXManager; //�G�l�~�[�}�l�[�W���̃|�C���^
	CScene * m_pScene;//�V�[��
	bool m_bPause;
	int m_nHitStop;
	int m_nScoreSave;
	int m_nLight;
	int m_nStageCount;
};


#endif // ! _MANAGER_H_
