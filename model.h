//==================
//���f���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _MODEL_H_//��d�C���N���[�h�h�~�̃}�N��
#define _MODEL_H_
//�C���N���[�h
#include "main.h"
#include<string.h>
#include<string>
//�N���X��`
class CModel 
{
public:

	CModel();

	~CModel();

	virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	static CModel * Create(char * pModelName);
	void SetParent(CModel * pModel) { m_pParent = pModel; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMin(void) { return m_vtxMinModel; }
	D3DXVECTOR3 GetMax(void) { return m_vtxMaxModel; }
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }
	std::string GetName(void) { return m_pModelName; }
	void SetOffset(D3DXVECTOR3 pos) { m_offset = pos; }
	D3DXVECTOR3 GetOffset() { return m_offset; }
	int * GetAddles() { return m_pIdxTex; }
private:
	int * m_pIdxTex;//�e�N�X�`���̃A�h���X��ێ�����|�C���^
	int  m_nIdxXFile;//���f���̃A�h���X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPD3DXMESH m_pMesh;		//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;			//�}�e���A���̐�
	D3DXVECTOR3 m_vtxMinModel, m_vtxMaxModel;//���f���̍ŏ��ƍő�

	D3DXVECTOR3 m_pos;//���W
	D3DXVECTOR3 m_rot;//�p�x
	D3DXVECTOR3 m_offset;
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X

	CModel * m_pParent;//�e�̃��f��
	std::string m_pModelName;//�ǂݍ��ރ��f���̖��O
};

#endif // ! _MODEL_H_
