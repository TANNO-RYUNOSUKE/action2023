//==================
//�i���o�[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _NUMBER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _NUMBER_H_
//�C���N���[�h
#include "main.h"


//�O���錾
class CObject2D;

//�N���X��`
class CNumber
{
public:
	CNumber();

	~CNumber();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber * Create(int nType = 0);

	

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	CObject2D * Get2D(void) { return m_pObbject; }
	void Setdata(const int ndata) { m_ndata = ndata; }
	void SetDisp(const bool bDisp) { m_bDisp = bDisp; }
private:
	bool m_bDisp;
	int m_nType;
	CObject2D * m_pObbject; //2D�I�u�W�F�N�g�ւ̃|�C���^
	int m_ndata;//�����Ă�����

};

#endif // ! _Number_H_
