//==================
//3D�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _OBJECT3D_H_//��d�C���N���[�h�h�~�̃}�N��
#define _OBJECT3D_H_
//�C���N���[�h
#include "main.h"
#include "object.h"

//�N���X��`
class CObject3D : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CObject3D(int nPriority = 0);

	~CObject3D();

	virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	float GetHeight(void) { return m_fHeight; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	float GetWidth(void) { return m_fWidth; }

	static CObject3D * Create(float fHeight, float fWidth,D3DXVECTOR3 pos,D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f),int nPriority = 0);




	CObject3D * Get3D(void) { return this; }
	LPDIRECT3DTEXTURE9 * GetTex(void) { return &m_pTexture; }
	LPDIRECT3DVERTEXBUFFER9 * GetBuff(void) { return &m_pVtxBuff; }
	

protected:
	//�|���S���\���p
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
private:
	float m_fHeight;	//����
	float m_fWidth;		//��
	
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X


};

#endif // ! _OBJECT3D_H_
