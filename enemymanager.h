//==================
//�}�l�[�W���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _ENEMYMANAGER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _ENEMYMANAGER_H_
//�C���N���[�h
#include "main.h"
#include "enemy.h"

#define NUM_ENEMY (64)//�G�l�~�[�̍ő吔

		   //�N���X��`
class CEnemyManager //�}�l�[�W���N���X
{
public:
	CEnemyManager();
	~CEnemyManager();

	void Init(void);
	void Regist(CEnemy * pEnemy);
	void Release(int nID);
	CEnemy ** GetEnemy(void) { return &m_apEnemy[0]; }
	CEnemy ** GetEnemy(int nID) {
		if (nID >= 0)
		{
			return &m_apEnemy[nID];
		}
		else
		{
			return NULL;
		}
	}
	int GetNum(void) { return m_nNumALL; }
private:
	static CEnemy * m_apEnemy[NUM_ENEMY];//�G�l�~�[�̔z��
	int m_nNumALL;//���v��

};

#endif // ! _ENEMYMANAGER_H_
