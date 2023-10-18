//==================
//�����_���[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _RENDERER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _RENDERER_H_
//�C���N���[�h
#include "main.h"

//�N���X��`
class CRenderer //�����_���[�N���X
{
public:
	//�R���X�g���N�^�ƃf�X�g���N�^
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	RECT GetTextureRect(IDirect3DTexture9* pSceneTexture);
	LPDIRECT3DDEVICE9 GetDevice(void){return m_pD3DDevice;}
	D3DPRESENT_PARAMETERS GetD3D(void) { return m_pD3Dpa; }

private:						
	LPDIRECT3D9 m_pD3D;						//direct3D�ւ̃|�C���^
	D3DPRESENT_PARAMETERS m_pD3Dpa;
	LPDIRECT3DDEVICE9 m_pD3DDevice;			//direct3D�f�o�C�X�ւ̃|�C���^
	LPD3DXEFFECT pEffect;
	LPD3DXEFFECT pEffectdot;
	LPD3DXEFFECT pEffectDownSample;
	LPD3DXEFFECT pEffectBrightCheck;
	LPD3DXEFFECT pEffectLinear;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 pSceneTexture;
	LPDIRECT3DTEXTURE9 pBloomTexture;
};

#endif // ! _RENDERER_H_
