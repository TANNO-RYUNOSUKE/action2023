//==================
//�}�l�[�W���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _XManager_H_//��d�C���N���[�h�h�~�̃}�N��
#define _XManager_H_
//�C���N���[�h
#include "main.h"
#include "objectX.h"

#define NUM_OBJECTX (128)//�G�l�~�[�̍ő吔
//�N���X��`
class CXManager //�}�l�[�W���N���X
{
public:
	CXManager();
	~CXManager();

	void Init(void);
	void Regist(CObjectX * pObj);
	void Release(int nID);
	CObjectX ** GetX(void) { return &m_apObjectX[0]; }
	int GetNum(void) { return m_nNumALL; }

private:
	static CObjectX * m_apObjectX[NUM_OBJECTX];//�G�l�~�[�̔z��
	int m_nNumALL;//���v��
};

#endif // ! _XManager_H_
