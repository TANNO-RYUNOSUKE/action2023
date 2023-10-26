//==================
//�X�R�A�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Timer_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Timer_H_
//�C���N���[�h
#include "main.h"
#include "number.h"

//�}�N����`
#define NUM_NUMBER (5)//����
//�N���X��`
class CTimer :public CNumber
{
public:
	CTimer();

	~CTimer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer * Create(void);

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const float fdata) { m_fdata = fdata;}
	void Add(const float fdata) { m_fdata += fdata; }
	float GetTimer(void) { return m_fdata; }

private:
	CNumber * m_apNumber[NUM_NUMBER]; //�i���o�[�I�u�W�F�N�g�ւ̃|�C���^
	float m_fdata;//�����Ă�����

	D3DXVECTOR3 m_pos;//�ꌅ�ڂ̍��W
};

#endif // ! _Timer_H_
