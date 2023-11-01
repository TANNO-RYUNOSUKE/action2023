//==================
//�v���C���[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _PLAYER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _PLAYER_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
#include "object2D.h"
#include "objectlight.h"
#include "ui_system_message.h"
#include "billboard.h"

//�}�N����`
#define GRAVITY (0.4f)
#define ENERGY_MAX (3.0f)
//�N���X��`
class CPlayer : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	typedef enum 
	{
		UPPERMOTION_NONE = -1,
		UPPERMOTION_NEUTRAL,
		UPPERMOTION_WALK,
		UPPERMOTION_SHOT,
		UPPERMOTION_ATTACK1,
		UPPERMOTION_ATTACK2,
		UPPERMOTION_ATTACK3,
		UPPERMOTION_MAX
	}UPPERMOTION;

	typedef enum
	{
		LOWERMOTION_NONE = -1,
		LOWERMOTION_NEUTRAL,
		LOWERMOTION_WALK,
		LOWERMOTION_FLIP,
		LOWERMOTION_JUMP,
		LOWERMOTION_DAMAGE,
		LOWERMOTION_DEATH,
		LOWERMOTION_MAX
	}LOWERMOTION;

	typedef enum 
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,
		STATE_DASH,
		STATE_HOVER,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer * Create(void);

	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	void SetLand(bool bLand) { m_bLand = bLand; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	void AddLife(int nAdd) { m_nLife += nAdd; }
	int GetLife() { return m_nLife; }
	void Move(void);
	float CheckEnemyAngle(const D3DXVECTOR3& cameraDirection, const D3DXVECTOR3& enemyDirection);
	static D3DXVECTOR3 LinePrediction(D3DXVECTOR3 shotPosition, D3DXVECTOR3 targetPosition, D3DXVECTOR3 targetPrePosition, float bulletSpeed);
	static float PlusMin(float a, float b);
	CModel * GetModelUp(int nData = 0) { return m_apModel[nData]; }
	void SetState(STATE state, int nCnt) { m_state = state; m_nStateCount = nCnt; }
	STATE GetState() { return m_state; }
	void SetFilterDisp(int nCnt) { m_nFilter = nCnt; }
	void SetInvincivl(int nCnt) { m_nCntInvincivl = nCnt; }
	int GetInvincivl() { return m_nCntInvincivl; }
	CMotion * GetMotion() { return m_pMotionUp; }
	float GetEnergy() { return m_fEnergy; }
private:
	STATE m_state;
	int m_nFilter;
	int m_nStateCount;
	CObject2D * m_pFilterDamage;
	int m_nLife;//�̗�
	int m_nReload;
	CMotion * m_pMotionUp;//���[�V�����|�C���^
	CEnemy ** m_pTarget;
	D3DXVECTOR3 m_posOld;//1�t���[���O�̍��W
	D3DXVECTOR3 m_rotShot; //�ˌ�����
	bool m_bLand;//���n�������ǂ���
	CModel * m_apModel[NUM_MODEL];//�g�p���郂�f���̃|�C���^
	int m_nNumModel;//�g�p���郂�f���̐�
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	CObjectLight * m_pLight;
	CBillboard * m_apTargetUI[2];
	CObject2D * m_pGage[3];
	int m_nCntInvincivl;
	float m_fEnergy;
};

#endif // ! _PLAYER_H_
