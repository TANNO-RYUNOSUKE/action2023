//========================================================================================
//
// �����_���[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "manager.h"
#include "shader.h"

//=============================================
//�R���X�g���N�^
//=============================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//=============================================
//�f�X�g���N�^
//=============================================
CRenderer::~CRenderer()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//DirectX�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct#D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	m_pD3Dpa = d3dpp;
	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//�T���v���[�X�e�[�g�̐ݒ�

	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���T���v�����O�X�e�[�g��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP); // U�����̃��b�s���O�𖳌���
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP); // V�����̃��b�s���O�𖳌���


	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�e��I�u�W�F�N�g�����������͂���

	ID3DXBuffer* pError = NULL;
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);
	VERTEX_2D *pVtx;
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�@���̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtxBuff->Unlock();
	pDevice->CreateTexture(
		SCREEN_WIDTH,          // �e�N�X�`���̕�
		SCREEN_HEIGHT,         // �e�N�X�`���̍���
		1,              // �~�b�v�}�b�v ���x��
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8, // �t�H�[�}�b�g
		D3DPOOL_DEFAULT, // �v�[��
		&pSceneTexture,  // �e�N�X�`�� �I�u�W�F�N�g
		NULL);
	pDevice->CreateTexture(
		DOWNSCALE_SCREEN_WIDTH,          // �e�N�X�`���̕�
		DOWNSCALE_SCREEN_HEIGHT,         // �e�N�X�`���̍���
		1,              // �~�b�v�}�b�v ���x��
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8, // �t�H�[�}�b�g
		D3DPOOL_DEFAULT, // �v�[��
		&pBloomTexture,  // �e�N�X�`�� �I�u�W�F�N�g
		NULL);

	Loadshader("BrightCheck.fx", &pEffectBrightCheck);
	Loadshader("DownSample.fx", &pEffectDownSample);
	Loadshader("BloomEffect.fx", &pEffect);
	Loadshader("dot.fx", &pEffectdot);
	Loadshader("Gauss.fx", &pEffectLinear);



	

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CRenderer::Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������
	
	//DirectX3d�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	//DirectX3d�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
	

}
//=============================================
//�X�V�֐�
//=============================================
void CRenderer::Update(void)
{

	// �E�B���h�E�̃N���C�A���g�̈�̃T�C�Y���擾
	RECT clientRect;




	// �N���C�A���g�̈�̕��ƍ�����\��
	float width = SCREEN_WIDTH;
	float height = SCREEN_HEIGHT;
	VERTEX_2D *pVtx;
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���W
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(width, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(width, height, 0.0f);


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtxBuff->Unlock();


	//�e��I�u�W�F�N�g�̍X�V����
	CObject::UpDateAll();

	
}
//=============================================
//�`��֐�
//=============================================
void CRenderer::Draw(void)
{
	CDebugProc * pDeb = CManager::GetInstance()->GetDeb();
	

	IDirect3DSurface9* pBackBuffer;
	m_pD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	IDirect3DSurface9* pRenderTarget;

	pSceneTexture->GetSurfaceLevel(0, &pRenderTarget);

	m_pD3DDevice->SetRenderTarget(0, pRenderTarget);

	//��ʃN���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//���������ꍇ
	
		CObject::DrawAll();
		
		m_pD3DDevice->SetRenderTarget(0, pBackBuffer);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		m_pD3DDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_2D));


		//���_�t�H�[�}�b�g�̐ݒ�
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		//�|���S���̕`��
		m_pD3DDevice->SetTexture(0, pSceneTexture); // �V�[���̃e�N�X�`����ݒ�
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	

		m_pD3DDevice->SetRenderTarget(0, pRenderTarget);
		// ���ȏ�̋P�x�𔲂��o��
		pEffectBrightCheck->Begin(NULL, 0);
		pEffectBrightCheck->BeginPass(0);
		pEffectBrightCheck->SetTechnique("brightcheck");

		m_pD3DDevice->SetTexture(0, pSceneTexture); // �V�[���̃e�N�X�`����ݒ�
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	

		// �K�E�X�ڂ�����K�p
		pEffect->Begin(NULL, 1);
		pEffect->BeginPass(0);
		pEffect->SetTechnique("GaussianBlur");
		pEffect->SetTexture("InputTexture", pSceneTexture);

		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		
		// �⊮��K�p
		pEffectLinear->Begin(NULL, 2);
		pEffectLinear->BeginPass(0);
		pEffectLinear->SetTechnique("GaussianBlur");
		pEffectLinear->SetTexture("InputTexture", pSceneTexture);

		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		m_pD3DDevice->SetRenderTarget(0, pRenderTarget);
	
		m_pD3DDevice->SetRenderTarget(0, pBackBuffer);

	
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		m_pD3DDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		
		//�|���S���̕`��
	
		// �u���[���V�F�[�_�[�̃s�N�Z�� �V�F�[�_�[�����s

		m_pD3DDevice->SetTexture(0, pSceneTexture); // �V�[���̃e�N�X�`����ݒ�

		//a�u�����f�B���O�����Z�����ɐݒ�
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // �A���t�@�u�����f�B���O��L���ɂ���
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE); // �\�[�X�J���[�̃u�����f�B���O���@��ݒ�
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); // �f�X�e�B�l�[�V�����J���[�̃u�����f�B���O���@��ݒ�


		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//a�u�����f�B���O��ʏ�ɐݒ�
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	
		pEffect->EndPass();
		pEffect->End();

		pEffectBrightCheck->EndPass();
		pEffectBrightCheck->End();

		pEffectLinear->EndPass();
		pEffectLinear->End();
		
		pDeb->Draw();

		//�I��
		m_pD3DDevice->EndScene();
	}

	
	pBackBuffer->Release();
	pRenderTarget->Release();
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

RECT CRenderer::GetTextureRect(IDirect3DTexture9* pSceneTexture)
{
	D3DSURFACE_DESC SauceDesc;
	pSceneTexture->GetLevelDesc(0, &SauceDesc);

	RECT SauceRect;
	SauceRect.left = 0;
	SauceRect.top = 0;
	SauceRect.right = SauceDesc.Width;
	SauceRect.bottom = SauceDesc.Height;

	return SauceRect;
}