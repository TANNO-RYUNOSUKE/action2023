//==================
//3D�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Pause_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Pause_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"
//�N���X��`
class CPause : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CPause(int nPriority = 6);

	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CPause * Create();

private:
	CObject2D * m_pPause[5];
	float m_fHeigth;
	int m_nChoice;
};

#endif // ! _Pause_H_
