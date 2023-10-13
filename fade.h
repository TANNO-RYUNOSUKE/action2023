//==================
//�t�F�[�h�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _FADE_H_//��d�C���N���[�h�h�~�̃}�N��
#define _FADE_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "scene.h"

class CFade :public CObject2D
{
public:
	CFade();
	~CFade();
	enum STATE
	{
		STATE_NONE = 0,
		STATE_FADEIN,
		STATE_FADEOUT,
		STATE_MAX
	};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void FadeOut(CScene::MODE mode) {
		if (m_State == STATE_NONE)
		{
			m_modenext = mode; m_State = STATE_FADEOUT;
		}
	}
	STATE GetState(void) { return m_State; }
	void FadeIn(void);
private:
	STATE m_State;
	CScene::MODE m_modenext;
};



#endif // ! _FADE_H_
