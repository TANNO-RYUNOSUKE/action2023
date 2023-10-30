//==================
//�Q�[�gUI�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Fake_BlueScreen_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Fake_BlueScreen_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"

class CFake_BlueScreen :public CObject
{
public:
	CFake_BlueScreen();
	~CFake_BlueScreen();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFake_BlueScreen * Create();
private:
	CObject2D * m_pScreen;
	int m_nLife;
};



#endif // ! _Fake_BlueScreen_H_
