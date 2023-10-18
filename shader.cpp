#include "shader.h"
#include "renderer.h"
#include "manager.h"
//�V�F�[�_�[�t�@�C���ǂݍ���
HRESULT Loadshader(char * path, LPD3DXEFFECT * pEffect)
{

	ID3DXBuffer* pError = NULL;
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	HRESULT hr = D3DXCreateEffectFromFile(
		pDevice,				// �f�o�C�X�ւ̃|�C���^
		path,			// fx�t�@�C���̃p�X
		NULL,                  // �v���v���Z�b�T��`
		NULL,                  // �v���v���Z�b�T��`�t�@�C��
		D3DXSHADER_DEBUG,                     // �t���O
		NULL,                  // �J�X�^���G�t�F�N�g�v�[��
		pEffect,              // �ǂݍ��܂ꂽ�G�t�F�N�g
		&pError                // �G���[���b�Z�[�W
	);
	if (pError)
	{
		OutputDebugStringA((LPCSTR)pError->GetBufferPointer());
		//�f�o�b�O�R���\�[���ɕ\������
		MessageBoxA(NULL, (LPCSTR)pError->GetBufferPointer(), "Shader Error", MB_OK);
	}
	return hr;
}