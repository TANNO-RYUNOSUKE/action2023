//==================
//�e�N�X�`���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _XFILE_H_//��d�C���N���[�h�h�~�̃}�N��
#define _XFILE_H_
//�C���N���[�h
#include "main.h"
#include <string>

//�}�N����`
#define NUM_XFILE (25600) //�e�N�X�`���̐�

//�N���X��`
class CXFile
{
public:
	CXFile();
	~CXFile();

	HRESULT Load(void);
	void Unload(void);

	int Regist(std::string pFilename);
	LPD3DXMESH GetAddress(int nIdx);
	LPD3DXBUFFER  GetMaterial(int nIdx);
	DWORD GetNumMaterial(int nIdx) { return m_dwNumMat[nIdx]; }
private:
	LPD3DXMESH m_pMesh[NUM_XFILE];		//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER  m_pBuffMat[NUM_XFILE];	//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat[NUM_XFILE];			//�}�e���A���̐�
	std::string pName[NUM_XFILE];
	static int m_nNumAll; //�e�N�X�`���̑���
};


#endif // ! _XFILE_H_