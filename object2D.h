//==================
//2D�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _OBJECT2D_H_//��d�C���N���[�h�h�~�̃}�N��
#define _OBJECT2D_H_
//�C���N���[�h
#include "main.h"
#include "object.h"

//�N���X��`
class CObject2D : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CObject2D(int nPriority = 6);

	~CObject2D();

    virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	float GetHeight(void) { return m_fHeight; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	float GetWidth(void) { return m_fWidth; }

	static CObject2D * Create(D3DXVECTOR3 pos, float fHeight, float fWidth,int nPriority = 0,char * pFileName = NULL);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	void SetVtx(VERTEX_2D  * pVtx);

	CObject2D * Get2D() { return this; }

	LPDIRECT3DVERTEXBUFFER9 * GetBuff() { return &m_pVtxBuff; }

	D3DXCOLOR GetCol(void) { return m_col; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetDisp(bool bDisp) { m_bDisp = bDisp; }
	void SetLife(int nLife) { m_nLife = nLife; }
	D3DXVECTOR2 GetTexMin(void) { return Tex_min; }
	D3DXVECTOR2 GetTexMax(void) { return Tex_max; }
	void SetTexMin(D3DXVECTOR2 pos) { Tex_min = pos; }
	void SetTexMax(D3DXVECTOR2 pos) { Tex_max = pos; }
	void SetName(char * pName) { m_pFileName = pName; }
protected:
	//�|���S���\���p

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
private:
	float m_fHeight;	//����
	float m_fWidth;	//��
	D3DXVECTOR2 Tex_min;
	D3DXVECTOR2 Tex_max;
	D3DXCOLOR m_col;//�F
	char * m_pFileName;//���O
	bool m_bDisp;
	int m_nLife;
};

#endif // ! _OBJECT2D_H_
