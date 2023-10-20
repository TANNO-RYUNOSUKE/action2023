//==================
//�o���b�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _BULLET_H_//��d�C���N���[�h�h�~�̃}�N��
#define _BULLET_H_
//�C���N���[�h
#include "main.h"
#include "billboard.h"
#include "objectlight.h"

//�N���X��`
class CBullet : public CBillboard //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CBullet(int nPriority = 2);
	CBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nLife);
	~CBullet();
	enum TYPE
	{
		TYPE_NONE =0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,TYPE type,bool bHoming,CEnemy ** pTag = NULL);

	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }

	void LinerHoming(void);
	void Homing(float fPower);
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetTag(CEnemy ** pEnemy) { m_pTarget = pEnemy; }
	static D3DXVECTOR3 VectorToAngles(const D3DXVECTOR3& vector);
	static D3DXVECTOR3 AnglesToVector(const D3DXVECTOR3& angles);
	void SetPowor(float fHoming) { m_fHomingPowor = fHoming; }
private:
	TYPE m_Type;
	bool CollisionEnemy(D3DXVECTOR3 pos);
	bool CollisionPlayer(D3DXVECTOR3 pos);
	CEnemy ** m_pTarget;
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_posOld;//1�t���[���O�̍��W
	int m_nLife;//����
	bool  m_bHoming;
	float m_fHomingPowor;
	int m_nHomingCount; //�z�[�~���O�̊Ǘ�
	int m_nMoveCount;//�O���ύX�̉�
	float m_fSpeed;

};

#endif // ! _BULLET_H_