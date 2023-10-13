//========================================================================================
//
// 3D�I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "objectX.h"
#include "manager.h"
#include "texture.h"
#include "xfile.h"
#include "Xmanager.h"
#include<vector>


//=============================================
//�R���X�g���N�^
//=============================================

CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{

	CXManager * pManger = CManager::GetXManager();
	pManger->Regist(this);
	m_pVtxBuff = NULL;
	m_vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	m_vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);

}



//=============================================
//�f�X�g���N�^
//=============================================
CObjectX::~CObjectX()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CObjectX::Init()
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

	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^
	pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
	
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂��鎞
			m_nIdxTex[nCntMat] = pTex->Regist(pMat[nCntMat].pTextureFilename);
		}
	}
	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CObjectX * CObjectX::Create(char * pName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority)
{
	CObjectX * pObject3D = NULL;

	pObject3D = DBG_NEW  CObjectX(nPriority);
	pObject3D->m_pModelName = pName;
	pObject3D->SetPos(pos);
	pObject3D->SetRot(rot);
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CObjectX::Uninit(void)
{
	CXManager * pManger = CManager::GetXManager();
	if (m_nID >= 0)
	{
		pManger->Release(m_nID);
	}

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
void CObjectX::Update(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CObjectX::Draw(void)
{
	CXFile * pXFile = CManager::GetXFiles();
	CTexture * pTex = CManager::GetTexture();
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat = NULL; //�}�e���A���f�[�^�ւ̃|�C���^

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = GetRot();
	pos = GetPos();
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

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	if (pXFile->GetMaterial(m_nIdxXFile) != NULL)
	{
		pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();

	}

	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTex->Getaddress((m_nIdxTex[nCntMat])));

		//���f��(�p�[�c)�̕`��
		pXFile->GetAddress(m_nIdxXFile)->DrawSubset(nCntMat);
		//m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}
//=============================================
//�����蔻��
//=============================================
bool CObjectX::Collision(D3DXVECTOR3 prevPosition, D3DXVECTOR3* pCurrentPosition, D3DXVECTOR3* pMovement,bool * pLand)
{
	
	
			if (pCurrentPosition->x > GetPos().x + m_vtxMinModel.x  && pCurrentPosition->x < GetPos().x + m_vtxMaxModel.x  && pCurrentPosition->z > GetPos().z + m_vtxMinModel.z  && pCurrentPosition->z < GetPos().z + m_vtxMaxModel.z && pCurrentPosition->y > GetPos().y + m_vtxMinModel.y  && pCurrentPosition->y < GetPos().y + m_vtxMaxModel.y)
			{
			

				if (prevPosition.y >= GetPos().y + m_vtxMaxModel.y && pCurrentPosition->y < GetPos().y + m_vtxMaxModel.y)
				{
					if (pLand!= NULL)
					{
						*pLand = true;
					}
				
					pCurrentPosition->y = GetPos().y + +m_vtxMaxModel.y;
					pMovement->y = 0.0f;
				}
				else if (prevPosition.z <= (GetPos().z + m_vtxMinModel.z) && pCurrentPosition->z >(GetPos().z + m_vtxMinModel.z))
				{
					pCurrentPosition->z = GetPos().z + m_vtxMinModel.z;
					pMovement->z = 0.0f;
				}

				else if (prevPosition.x <= (GetPos().x + m_vtxMinModel.x) && pCurrentPosition->x > (GetPos().x + m_vtxMinModel.x))
				{
					pCurrentPosition->x = GetPos().x + m_vtxMinModel.x;
					pMovement->x = 0.0f;
				}
				else if (prevPosition.x >= GetPos().x + m_vtxMaxModel.x && pCurrentPosition->x < GetPos().x + m_vtxMaxModel.x)
				{
					pCurrentPosition->x = GetPos().x + +m_vtxMaxModel.x;
					pMovement->x = 0.0f;
				}
				else if (prevPosition.z >= GetPos().z + m_vtxMaxModel.z && pCurrentPosition->z < GetPos().z + m_vtxMaxModel.z)
				{
					pCurrentPosition->z = GetPos().z + +m_vtxMaxModel.z;
					pMovement->z = 0.0f;
				}
				return true;
			}
		
	
	return false;
}
//=============================================
//���C
//=============================================
bool CObjectX::IntersectTriangle(const D3DXVECTOR3& prevPosition, D3DXVECTOR3* pCurrentPosition, D3DXVECTOR3* pMovement, const D3DXVECTOR3& v1, const D3DXVECTOR3& v2, const D3DXVECTOR3& v3)
{
	// �O�p�`�̖@���x�N�g�����v�Z
	D3DXVECTOR3 normal;
	D3DXVec3Cross(&normal, &(v2 - v1), &(v3 - v1));
	D3DXVec3Normalize(&normal, &normal);

	// �O�p�`�̖ʕ��������v�Z (Ax + By + Cz + D = 0)
	float A = normal.x;
	float B = normal.y;
	float C = normal.z;
	float D = -D3DXVec3Dot(&normal, &v1);

	// �ړ��x�N�g�����擾
	D3DXVECTOR3 moveVector = *pCurrentPosition - prevPosition;

	// �ړ��x�N�g�����O�p�`�̖ʂƌ������邩�`�F�b�N
	float dotProduct = A * moveVector.x + B * moveVector.y + C * moveVector.z;
	if (dotProduct != 0.0f)
	{
		float t = (-D - A * prevPosition.x - B * prevPosition.y - C * prevPosition.z) / dotProduct;

		// t��0����1�̊Ԃɂ���ꍇ�A�����_���v�Z
		if (t >= 0.0f && t <= 1.0f)
		{
			D3DXVECTOR3 intersection = prevPosition + t * moveVector;

			// �����_���O�p�`�̓����ɂ��邩�ǂ����`�F�b�N
			D3DXVECTOR3 edge1 = v2 - v1;
			D3DXVECTOR3 edge2 = v3 - v2;
			D3DXVECTOR3 edge3 = v1 - v3;

			D3DXVECTOR3 c1 = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 c2 = v2 - v1;
			D3DXVECTOR3 c3 = v3 - v1;

			D3DXVECTOR3 p1 = intersection - v1;
			D3DXVECTOR3 p2 = intersection - v2;
			D3DXVECTOR3 p3 = intersection - v3;

			D3DXVECTOR3 test1, test2, test3;

			D3DXVec3Cross(&test1, &c1, &p1);
			D3DXVec3Cross(&test2, &c2, &p2);
			D3DXVec3Cross(&test3, &c3, &p3);

			if (D3DXVec3Dot(&test1, &normal) >= 0 && D3DXVec3Dot(&test2, &normal) >= 0 && D3DXVec3Dot(&test3, &normal) >= 0)
			{
				// �����_���O�p�`�̓����ɂ���ꍇ�A���W��␳
				*pCurrentPosition = intersection;

				// �ړ��x�N�g����␳
				*pMovement = *pMovement - (intersection - prevPosition);

				return true;
			}
		}
	}

	return false;
}

D3DXVECTOR3  CObjectX::CalculateNormal(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2, const D3DXVECTOR3& v3)
{
	D3DXVECTOR3 edge1 = v2 - v1;
	D3DXVECTOR3 edge2 = v3 - v1;

	// �O�ς��v�Z���Ė@���x�N�g���𓾂�
	D3DXVECTOR3 normal;
	D3DXVec3Cross(&normal, &edge1, &edge2);
	D3DXVec3Normalize(&normal, &normal);

	return normal;
}
bool CObjectX::Ray(D3DXVECTOR3 start, D3DXVECTOR3 end,D3DXVECTOR3 * pPos)
{

	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 max = m_vtxMaxModel;
	D3DXVECTOR3 min = m_vtxMinModel;

	D3DXVECTOR3 v1, v2, v3, v4, v5, v6, v7, v8;
	v1 = D3DXVECTOR3(min.x, max.y, max.z);
	v2 = D3DXVECTOR3(max.x, max.y, max.z);
	v3 = D3DXVECTOR3(max.x, max.y, min.z);
	v4 = D3DXVECTOR3(min.x, max.y, min.z);
	v5 = D3DXVECTOR3(min.x, min.y, max.z);
	v6 = D3DXVECTOR3(max.x, min.y, max.z);
	v7 = D3DXVECTOR3(max.x, min.y, min.z);
	v8 = D3DXVECTOR3(min.x, min.y, min.z);

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

	D3DXVec3TransformCoord(&v1, &v1, &m_mtxWorld);
	D3DXVec3TransformCoord(&v2, &v2, &m_mtxWorld);
	D3DXVec3TransformCoord(&v3, &v3, &m_mtxWorld);
	D3DXVec3TransformCoord(&v4, &v4, &m_mtxWorld);
	D3DXVec3TransformCoord(&v5, &v5, &m_mtxWorld);
	D3DXVec3TransformCoord(&v6, &v6, &m_mtxWorld);
	D3DXVec3TransformCoord(&v7, &v7, &m_mtxWorld);
	D3DXVec3TransformCoord(&v8, &v8, &m_mtxWorld);

	

	if (CManager::RayTri(start, end, v3, v7, v4, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v4,v7, v8, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v3, v6, v7, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v3, v2, v6, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v2, v1, v6, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v6, v1, v5, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v1, v8, v5, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v1, v4, v8, pPos))
	{
		return true;
	}

	if (CManager::RayTri(start, end, v1, v2, v3, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v3, v4, v1, pPos))
	{
		return true;
	}

	if (CManager::RayTri(start, end, v5, v6, v7, pPos))
	{
		return true;
	}
	if (CManager::RayTri(start, end, v7, v8, v5, pPos))
	{
		return true;
	}
	return false;
}
CDebri::CDebri(int nPriority) : CObjectX(nPriority)
{
	CXManager * pManger = CManager::GetXManager();
	pManger->Release(m_nID);
}

CDebri::~CDebri()
{
}
HRESULT CDebri::Init()
{
	CObjectX::Init();
	return S_OK;
}
void CDebri::Uninit()
{
	CObjectX::Uninit();
}
void CDebri::Update()
{
	CObjectX::Update();
	SetPos(GetPos() + move);
	SetRot(GetRot() + rotation);
	m_nLife--;
	if (m_nLife <= 0)
	{

		Release();
	}
}
void CDebri::Draw()
{
	CObjectX::Draw();
}
CDebri * CDebri::Create(std::string pName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXVECTOR3 rotation, int nLife, int nPriority )
{
	CDebri * pObject3D = NULL;

	pObject3D = DBG_NEW  CDebri(nPriority);
	pObject3D->SetName(pName);
	pObject3D->SetPos(pos);
	pObject3D->SetRot(rot);
	pObject3D->move = move;
	pObject3D->rotation = rotation;
	pObject3D->m_nLife = nLife;
	pObject3D->Init();
	return pObject3D;
}

