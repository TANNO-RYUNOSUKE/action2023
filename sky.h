//==================
//X�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Sky_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Sky_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "objectX.h"
//�N���X��`
class CSky : public CObjectX //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CSky(int nPriority = 0);

	~CSky();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CSky * Create();

};

#endif // ! _Sky_H_
