//==================
//�G�t�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _EFFECT_H_//��d�C���N���[�h�h�~�̃}�N��
#define _EFFECT_H_
//�C���N���[�h
#include "main.h"
#include "billboard.h"


//�N���X��`
class CEffect : public CBillboard //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CEffect(int nPriority = 1);

	~CEffect();

	HRESULT Init(char * pName = "data\\TEXTURE\\effect000.jpg");
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,D3DXCOLOR col,float fsize,float fAttenuation = 0.9f, char * pName = "data\\TEXTURE\\effect000.jpg");


	void SetColor(D3DXCOLOR col) { m_Color = col; }
	D3DXCOLOR GetColor(void) { return m_Color; }


	void SetSize(float fSize) { m_fSize = fSize; }
	float GetSize(void) { return m_fSize; }
	void SetAttenuation(float fAttenuation) { m_fAttenuation = fAttenuation; }
	float GetAttenuation(void) { return m_fAttenuation; }
private:
	float m_fSize;//�傫��
	float m_fMaxSize;
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move;//�ړ���
	D3DXCOLOR m_Color;//�F
	int m_nLife;//����
	int m_nMaxLife;//�����̎����ő�l
	float m_fAttenuation;//������
	char m_pName;
};

#endif // ! _EFFECT_H_