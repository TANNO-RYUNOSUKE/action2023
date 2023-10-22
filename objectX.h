//==================
//X�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _OBJECTX_H_//��d�C���N���[�h�h�~�̃}�N��
#define _OBJECTX_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include <string>
#include <algorithm>
#include<vector>
//�N���X��`
class CObjectX : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CObjectX(int nPriority = 1);

	~CObjectX();

	virtual	HRESULT Init();
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	bool Ray(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXVECTOR3 * pPos = NULL);
	bool Collision(D3DXVECTOR3 prevPosition, D3DXVECTOR3* pCurrentPosition, D3DXVECTOR3* pMovement, bool * pLand = NULL);
	bool CollisionX(D3DXVECTOR3 prevPosition, D3DXVECTOR3* pCurrentPosition, D3DXVECTOR3* pMovement);
	bool CollisionY(D3DXVECTOR3 prevPosition, D3DXVECTOR3* pCurrentPosition, D3DXVECTOR3* pMovement, bool * pLand = NULL);
	bool IntersectTriangle(const D3DXVECTOR3& prevPosition, D3DXVECTOR3* pCurrentPosition, D3DXVECTOR3* pMovement, const D3DXVECTOR3& v1, const D3DXVECTOR3& v2, const D3DXVECTOR3& v3);
	bool IsInsideBoundingBox(D3DXVECTOR3* vertices, D3DXVECTOR3 point, D3DXVECTOR3* pMovement);
	bool IsOnLineSegment(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 point);
	D3DXVECTOR3 CalculateNormal(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2, const D3DXVECTOR3& v3);
	static CObjectX * Create(char * pName, D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), int nPriority = 3);
    void CorrectMovementForPlane(const D3DXVECTOR3& prevPosition, D3DXVECTOR3* pCurrentPosition, D3DXVECTOR3* pMovement, const D3DXVECTOR3& point1, const D3DXVECTOR3& point2, const D3DXVECTOR3& point3);
	void SetID(int nId) { m_nID = nId; }
	int GetID(void) { return m_nID; }

	void SetName(std::string name) { m_pModelName = name; }
	std::string GetName(void) { return m_pModelName; }
protected:
	//�|���S���\���p
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	int m_nID;
	int m_nIdxXFile;
private:
	std::string m_pModelName;//�ǂݍ��ރ��f���̖��O
	
	D3DXVECTOR3 m_vtxMinModel, m_vtxMaxModel;//���f���̍ŏ��ƍő�

	

};

class CDebri : public CObjectX //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CDebri(int nPriority = 3);
	~CDebri();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CDebri * Create(std::string pName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXVECTOR3 rotation, int nLife, int nPriority = 3);
private:
	int m_nLife;
	D3DXVECTOR3 move, rotation;
};
class CAfterImage : public CObjectX //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CAfterImage(int nPriority = 6);
	~CAfterImage();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetColor(D3DXCOLOR col);
	static CAfterImage * Create(std::string pName, D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col, int nLife, int nPriority = 6);
private:
	D3DMATERIAL9 m_pMat; // �V�����}�e���A�������i�[����x�N�^�[
	int m_nLife;
	D3DXCOLOR m_col;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
};

#endif // ! _OBJECTX_H_
