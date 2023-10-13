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


//=============================================
//�R���X�g���N�^
//=============================================

CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
}



//=============================================
//�f�X�g���N�^
//=============================================
CObject3D::~CObject3D()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CObject3D::Init(void)
{

	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();


	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, +m_fHeight);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, 1000.0f, +m_fHeight);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 1000.0f, -m_fHeight);
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, 0.0f, -m_fHeight);

	D3DXVECTOR3 nor;
	
	//�@���x�N�g���̐ݒ�
	D3DXVec3Cross(&nor, &(pVtx[1].pos - pVtx[0].pos), &(pVtx[2].pos - pVtx[0].pos));
	pVtx[0].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

	D3DXVec3Cross(&nor, &(pVtx[3].pos - pVtx[1].pos), &(pVtx[0].pos - pVtx[1].pos));
	pVtx[1].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	D3DXVec3Normalize(&pVtx[1].nor, &pVtx[1].nor);

	D3DXVec3Cross(&nor, &(pVtx[0].pos - pVtx[2].pos), &(pVtx[3].pos - pVtx[2].pos));
	pVtx[2].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	D3DXVec3Normalize(&pVtx[2].nor, &pVtx[2].nor);

	D3DXVec3Cross(&nor, &(pVtx[2].pos - pVtx[3].pos), &(pVtx[1].pos - pVtx[3].pos));
	pVtx[3].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	D3DXVec3Normalize(&pVtx[3].nor, &pVtx[3].nor);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();
	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CObject3D * CObject3D::Create(float fHeight, float fWidth,D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority)
{
	CObject3D * pObject3D = NULL;
	
	pObject3D = DBG_NEW CObject3D;
	pObject3D->SetHeight(fHeight);
	pObject3D->SetWidth(fWidth);
	pObject3D->SetPos(pos);
	pObject3D->SetRot(rot);
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CObject3D::Uninit(void)
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
void CObject3D::Update(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^


	//�����蔻��̎v���o
	//D3DXVECTOR3 pos = pPlayer->GetPos();
	//float dot = 0.0f;

	//VERTEX_3D * pVtx;
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//
	//D3DXVECTOR3 nor, vec1, vec2;
	//vec1 = (pVtx[1].pos - pVtx[0].pos);
	//vec2 = (pVtx[2].pos - pVtx[0].pos);
	//D3DXVec3Cross(&nor, &vec1, &vec2);
	//D3DXVec3Normalize(&nor, &nor);
	//D3DXVECTOR3 vecP1, vecP2, vecP3, vec01, vec02,vec03;
	//vecP1 = pos - pVtx[0].pos - GetPos();
	//vecP2 = pos - pVtx[1].pos - GetPos();
	//vecP3 = pos - pVtx[2].pos - GetPos();
	//vec01 = pVtx[1].pos - pVtx[0].pos;
	//vec02 = pVtx[2].pos - pVtx[1].pos;
	//vec03 = pVtx[0].pos - pVtx[2].pos;
	//if ((vec01.z * vecP1.x) - (vec01.x * vecP1.z) > 0)
	//{
	//	if ((vec02.z * vecP2.x) - (vec02.x * vecP2.z) > 0)
	//	{
	//		if ((vec03.z * vecP3.x) - (vec03.x * vecP3.z) > 0)
	//		{
	//			if (nor.y != 0.0f)
	//			{
	//				dot = ((pos.x - pVtx[0].pos.x - GetPos().x)*nor.x + (pos.z - pVtx[0].pos.z - GetPos().z)*nor.z - (pVtx[0].pos.y * nor.y)) / -nor.y;
	//				pPlayer->SetPos(D3DXVECTOR3(pos.x, dot, pos.z));
	//			}
	//		}
	//	}
	//}

	//vec1 = (pVtx[1].pos - pVtx[3].pos);
	//vec2 = (pVtx[2].pos - pVtx[3].pos);
	//D3DXVec3Cross(&nor, &vec1, &vec2);
	//D3DXVec3Normalize(&nor, &nor);
	//
	//vecP1 = pos - pVtx[3].pos - GetPos();
	//vecP2 = pos - pVtx[2].pos - GetPos();
	//vecP3 = pos - pVtx[1].pos - GetPos();
	//vec01 = pVtx[2].pos - pVtx[3].pos;
	//vec02 = pVtx[1].pos - pVtx[2].pos;
	//vec03 = pVtx[3].pos - pVtx[1].pos;
	//if ((vec01.z * vecP1.x) - (vec01.x * vecP1.z) > 0)
	//{
	//	if ((vec02.z * vecP2.x) - (vec02.x * vecP2.z) > 0)
	//	{
	//		if ((vec03.z * vecP3.x) - (vec03.x * vecP3.z) > 0)
	//		{
	//			if (nor.y != 0.0f)
	//			{
	//				dot = ((pos.x - pVtx[3].pos.x - GetPos().x)*nor.x + (pos.z - pVtx[3].pos.z - GetPos().z)*nor.z - (pVtx[3].pos.y * nor.y)) / -nor.y;
	//				pPlayer->SetPos(D3DXVECTOR3(pos.x, dot, pos.z));
	//			}
	//		}
	//	}
	//}

	//m_pVtxBuff->Unlock();

	//pDevice = pRenderer->GetDevice();
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CObject3D::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}

