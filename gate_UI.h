//==================
//�Q�[�gUI�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Gate_UI_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Gate_UI_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "billboard.h"
class CGate_UI :public CBillboard
{
public:
	CGate_UI();
	~CGate_UI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGate_UI * Create(D3DXVECTOR3 pos);
private:

};



#endif // ! _Gate_UI_H_
