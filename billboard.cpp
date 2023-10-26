//========================================================================================
//
// 3D�I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object3D.h"
#include "manager.h"
#include "billboard.h"
#include "texture.h"

//=============================================
//�R���X�g���N�^
//=============================================

CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	m_Cclor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Tex_min = D3DXVECTOR2(0.0f, 0.0f);
	Tex_max = D3DXVECTOR2(1.0f, 1.0f);
	m_pVtxBuff = NULL;
	m_pName = NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
}



//=============================================
//�f�X�g���N�^
//=============================================
CBillboard::~CBillboard()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CBillboard::Init(void)
{

	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	if (m_pName != NULL)
	{
		CTexture * pTex = CManager::GetInstance()->GetTexture();
		m_nIdxTex[0] = pTex->Regist(m_pName);
	}
	

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, +m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, -m_fHeight, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Cclor;
	pVtx[1].col = m_Cclor;
	pVtx[2].col = m_Cclor;
	pVtx[3].col = m_Cclor;

	m_pVtxBuff->Unlock();
	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CBillboard * CBillboard::Create(float fHeight, float fWidth, D3DXVECTOR3 pos, char * pName)
{
	CBillboard * pObject3D = NULL;

	pObject3D = DBG_NEW CBillboard;
	if (pName != NULL)
	{
		CTexture * pTex = CManager::GetInstance()->GetTexture();
		
		pObject3D->m_nIdxTex[0] = pTex->Regist(pName);
	}

	pObject3D->SetHeight(fHeight);
	pObject3D->SetWidth(fWidth);
	pObject3D->SetPos(pos);
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CBillboard::Uninit(void)
{
	
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CBillboard::Update(void)
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, +m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, -m_fHeight, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(Tex_min.x, Tex_min.y);
	pVtx[1].tex = D3DXVECTOR2(Tex_max.x, Tex_min.y);
	pVtx[2].tex = D3DXVECTOR2(Tex_min.x, Tex_max.y);
	pVtx[3].tex = D3DXVECTOR2(Tex_max.x, Tex_max.y);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_Cclor;
	pVtx[1].col = m_Cclor;
	pVtx[2].col = m_Cclor;
	pVtx[3].col = m_Cclor;

	m_pVtxBuff->Unlock();
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CBillboard::Draw(void)
{


	CTexture * pTex = CManager::GetInstance()->GetTexture();
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX  mtxTrans; //�v�Z�p�}�g���N�X
	D3DXMATRIX mtxView; //�r���[�}�g���N�X�擾�p
	D3DXVECTOR3 pos = GetPos();


	//���C�e�B���O������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
//	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //�t�H�O�̖�����

	//Z�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���N�X�擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y,pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	if (m_nIdxTex != NULL)
	{
		if (m_nIdxTex >= 0)
		{
			pDevice->SetTexture(0, pTex->Getaddress(*(m_nIdxTex)));
		}
	}


	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//Z�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);

	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); //�t�H�O�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
