//==================
//�e�N�X�`���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _TEXTURE_H_//��d�C���N���[�h�h�~�̃}�N��
#define _TEXTURE_H_
//�C���N���[�h
#include "main.h"


//�}�N����`
#define NUM_TEXTURE (256) //�e�N�X�`���̐�

//�N���X��`
class CTexture
{
public:
	CTexture();
	~CTexture();

	HRESULT Load(void);
	void Unload(void);

	int Regist(char * pFilename);
	LPDIRECT3DTEXTURE9 Getaddress(int nIdx);

private:
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXTURE];//�e�N�X�`���̏��
	char * m_pNameArray[NUM_TEXTURE];
	static int m_nNumAll; //�e�N�X�`���̑���
};


#endif // ! _TEXTURE_H_
