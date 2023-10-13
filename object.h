//==================
//�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _OBJECT_H_//��d�C���N���[�h�h�~�̃}�N��
#define _OBJECT_H_
//�C���N���[�h
#include "main.h"

//�}�N����`
#define NUM_OBJECT (2560) //�I�u�W�F�N�g�̍ő吔
#define NUM_PRIORITY (8) //�D�揇�ʂ̍ő�

//�N���X��`
class CObject //�I�u�W�F�N�g�̒��ۃN���X
{
public:
	typedef enum
	{
		TYPE_NONE = 0,//��̃^�C�v
		TYPE_ENEMY,//�G
		TYPE_PLAYER,//�v���C���[
		TYPE_BULLET,//�e
		TYPE_BLOCK,//�u���b�N
		TYPE_ITEM,//�A�C�e��
		TYPE_MAX,//�ő�l
	}TYPE;//�^�C�v

	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init(void) = 0;

	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	
	static void ReleaseAll(void);
	static void DrawAll(void);
	static void UpDateAll(void);

	D3DXVECTOR3 GetPos();// { return m_pos; }//���W�擾
	D3DXVECTOR3 * GetPosAddress() { return  &m_pos; }//���W�擾
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }//���W�ݒ�
	D3DXVECTOR3 GetRot() { return m_rot; }//�p�x�擾
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }//�p�x�ݒ�
	D3DXVECTOR3 GetMove() { return m_move; }//�ړ��擾
	D3DXVECTOR3 * GetMoveAddress() { return &m_move; }//�ړ��擾
	void SetMove(const D3DXVECTOR3 move) {  m_move = move; }//�ړ��ݒ�

	void SetType(const TYPE type) { m_Type = type; }//�^�C�v�̐ݒ�
	TYPE GetType(void) { return m_Type; }//�^�C�v�̎擾

	virtual D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	virtual void SetLand(bool bLand) {};

	virtual float GetHeight(void) { return 0.0f; }
	virtual float GetWidth(void) { return 0.0f; }
	virtual void SetLife(int nLife) { };
	virtual D3DXMATRIX GetMatrix(void) {D3DXMATRIX mtx;  D3DXMatrixIdentity(&mtx); return mtx;}
	//int GetID(void) { return m_nID; }
	
	static CObject * GetTop(int nPriority) {
		if (nPriority >= 0 && nPriority < NUM_PRIORITY) { return m_apTop[nPriority]; }
		else
		{
			return NULL;
		}
	}
	CObject * GetNext(){ return m_pNext; }
	void SetNext(CObject * pNext) { m_pNext = pNext; }
	CObject * GetPrev() { return m_pPrev; }
	void SetPrev(CObject * pPrev) { m_pPrev = pPrev; }
	
	virtual void Release(void);
protected:
	int m_nIdxTex[16];//�e�N�X�`���̃A�h���X��ێ�
private:
	//static CObject * m_apObject[NUM_PRIORITY][NUM_OBJECT];//�I�u�W�F�N�g�̃|�C���^
	static CObject * m_apTop[NUM_PRIORITY];//�I�u�W�F�N�g�̐擪
	static CObject * m_apCur[NUM_PRIORITY];//�I�u�W�F�N�g�̍Ō��
	static CObject * m_pStaticNext;//���̃I�u�W�F�N�g
	CObject * m_pPrev;//�����̑O�̃|�C���^
	CObject * m_pNext;//�����̎��̃|�C���^
	static int m_nNumALL;//���v��
	
	int m_nPriority;//�I�u�W�F�N�g�̗D�揇��
	D3DXVECTOR3 m_pos; //���W
	D3DXVECTOR3 m_move; //�ړ����x
	D3DXVECTOR3 m_rot; //����
	TYPE m_Type; //�^�C�v
	
};


#endif // ! _OBJECT_H_
