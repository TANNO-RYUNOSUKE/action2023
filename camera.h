//==================
//�J�����w�b�_�[
//Author: �O�� ���V��
//==================
#include "main.h"

#ifndef _Camera_H_
#define _Camera_H_

class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Set(void);


	void SetRDest(D3DXVECTOR3 pos) { m_posRdest = pos; }
	void SetVDest(D3DXVECTOR3 pos) { m_posVdest = pos; }
	void SetShake(int nCnt) { nCntShake = nCnt; }
	int GetShake(void) { return nCntShake; }
	void SetLenght(float fLength) { m_fLengthCamera = fLength; }
	float GetLenght(void) { return m_fLengthCamera; }
	void SetDirection(bool bDirection) { m_bDirection = bDirection; }
	D3DXVECTOR3 GetRot() { return m_rot; }//�����̎擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetVec(void) { return m_vecCamera; }
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	void SetPosV(D3DXVECTOR3 pos) {  m_posV = pos; }
	void SetPosR(D3DXVECTOR3 pos) {  m_posR = pos; }
private:
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_posVdest;		//���_�̖ړI�n
	D3DXVECTOR3 m_posRdest;		//�����_�̖ړI�n
	D3DXVECTOR3 m_vecU;			//������x�N�g��
	D3DXVECTOR3 m_vecCamera;	//�J�����̌����Ă������
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_rotDest;		//�����ڕW
	D3DXVECTOR3 m_moveV;		//���_�̈ړ����x
	D3DXVECTOR3 m_moveR;		//�����_�̈ړ����x
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���N�X
	float m_fLengthCamera; //�J�����̋���
	D3DXVECTOR3 m_rotOld;
	int nCntShake;
	bool m_bDirection;
};



#endif // !_Camera_H_
