#include "enemymanager.h"
 CEnemy *CEnemyManager::m_apEnemy[NUM_ENEMY] = {};

 //==============================
 //�R���X�g���N�^,�f�X�g���N�^
 //==============================
CEnemyManager::CEnemyManager()
{
	
}
CEnemyManager::~CEnemyManager()
{

}
void CEnemyManager::Init(void)
{
	m_nNumALL = 0;

	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		m_apEnemy[nCnt] = NULL;
	}
	
}
//==============================
//�o�^����
//==============================
void CEnemyManager::Regist(CEnemy * pEnemy)
{
	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		if (m_apEnemy[nCnt] == NULL)
		{
			m_apEnemy[nCnt] = pEnemy;
			m_apEnemy[nCnt]->SetID(nCnt);
			m_nNumALL++;
			break;
		}
	}
}
//==============================
//�������
//==============================
void CEnemyManager::Release(int nID)
{
	if (m_apEnemy[nID] != NULL)
	{
		m_apEnemy[nID] = NULL;
		m_nNumALL--;
	}
}

