//==================
//�r���{�[�h�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Billboard_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Billboard_H_
//�C���N���[�h
#include "main.h"
#include "object.h"

//�N���X��`
class CBillboard : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CBillboard(int nPriority = 6);

	~CBillboard();

	virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	float GetHeight(void) { return m_fHeight; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	float GetWidth(void) { return m_fWidth; }

	static CBillboard * Create(float fHeight, float fWidth, D3DXVECTOR3 pos,char * pName = NULL);

	
	CBillboard * Get2D() { return this; }

	LPDIRECT3DVERTEXBUFFER9 * GetBuff() { return &m_pVtxBuff; }
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }
	void SetColor(D3DXCOLOR col) { m_Cclor = col; }
protected:
	//�|���S���\���p
	
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
private:
	float m_fHeight;	//����
	float m_fWidth;	//��
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	D3DXCOLOR m_Cclor; //�F

};

#endif // ! _Billboard_H_
