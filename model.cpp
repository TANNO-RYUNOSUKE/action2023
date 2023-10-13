//========================================================================================
//
// 3D���f��(�K�w�\��)
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "manager.h"
#include "texture.h"
#include "xfile.h"

//=============================================
//�R���X�g���N�^
//=============================================

CModel::CModel() 
{
	m_pIdxTex = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	m_dwNumMat = 0;
	
	m_pModelName = {};
	m_pBuffMat = NULL;
	m_pParent = NULL;
	m_pMesh = NULL;
}



//=============================================
//�f�X�g���N�^
//=============================================
CModel::~CModel()
{

}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CModel::Init(void)
{
	int nNumVtx = 0; //���_��
	DWORD dwSizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff = NULL; //���_�o�b�t�@�ւ̃|�C���^
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();


	CTexture * pTex = CManager::GetTexture();
	CXFile * pXFile = CManager::GetXFiles();
	m_nIdxXFile = pXFile->Regist(m_pModelName);
	//x�t�@�C���̓ǂݍ���
	/*if (D3DXLoadMeshFromX(m_pModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh) != D3D_OK)
	{
		return E_FAIL;
	}*/

	//���_�����擾
	nNumVtx = pXFile->GetAddress(m_nIdxXFile)->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(pXFile->GetAddress(m_nIdxXFile)->GetFVF());

	//���_�o�b�t�@�����b�N
	pXFile->GetAddress(m_nIdxXFile)->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_vtxMinModel.x > vtx.x)
		{
			m_vtxMinModel.x = vtx.x;
		}
		if (m_vtxMinModel.y > vtx.y)
		{
			m_vtxMinModel.y = vtx.y;
		}
		if (m_vtxMinModel.z > vtx.z)
		{
			m_vtxMinModel.z = vtx.z;
		}
		if (m_vtxMaxModel.x < vtx.x)
		{
			m_vtxMaxModel.x = vtx.x;
		}
		if (m_vtxMaxModel.y < vtx.y)
		{
			m_vtxMaxModel.y = vtx.y;
		}
		if (m_vtxMaxModel.z < vtx.z)
		{
			m_vtxMaxModel.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;
	}
	//���_�o�b�t�@���A�����b�N
	pXFile->GetAddress(m_nIdxXFile)->UnlockVertexBuffer();

	//�e�N�X�`���̓ǂݍ���

	m_pIdxTex = DBG_NEW  int[(int)pXFile->GetNumMaterial(m_nIdxXFile)];
	*m_pIdxTex = -1;
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^
	pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		m_pIdxTex[nCntMat] = -1;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂��鎞
			m_pIdxTex[nCntMat] = pTex->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CModel * CModel::Create( char * pModelName)
{
	CModel * pObject3D = NULL;
	pObject3D = DBG_NEW  CModel();
	pObject3D->m_pModelName = pModelName;
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CModel::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�e�N�X�`���̔j��
	if (m_pIdxTex != NULL)
	{
		delete[] m_pIdxTex;
		m_pIdxTex = NULL;
	}

}

//=============================================
//�|���S���̍X�V����
//=============================================
void CModel::Update(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CModel::Draw(void)
{

	CTexture * pTex = CManager::GetTexture();
	CXFile * pXFile = CManager::GetXFiles();
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DXMATRIX mtxParent;
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat = NULL; //�}�e���A���f�[�^�ւ̃|�C���^

	
	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
	//���[���h�}�g���N�X�̐ݒ�
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�Z�o�����}�g���N�X���������킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	if (pXFile->GetMaterial(m_nIdxXFile) != NULL)
	{
		pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();

	}

	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		//if (nCntMat == 1)
		//{
		//	D3DMATERIAL9 mat;
		//	ZeroMemory(&mat, sizeof(D3DMATERIAL9));
		//	mat.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̊g�U�F�i���F�j
		//	mat.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̊��F�i���F�j
		//	mat.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̋��ʔ��ːF�i���F�j
		//	mat.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̎��Ȕ����F�i���F�j
		//	mat.Power = 32.0f; // �}�e���A���̋��ʔ��˂̋���

		//	pDevice->SetMaterial(&mat);
		//}
		
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		
	
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTex->Getaddress(m_pIdxTex[nCntMat]));

		//���f��(�p�[�c)�̕`��
		pXFile->GetAddress(m_nIdxXFile)->DrawSubset(nCntMat);
		//m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);


}

