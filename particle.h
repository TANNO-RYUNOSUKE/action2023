//==================
//�o���b�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Particle_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Particle_H_
//�C���N���[�h
#include "main.h"
#include "effect.h"
#include"billboard.h"
#include <string>
//�N���X��`effect
class CParticle:public CEffect
{
public:
	CParticle();
	~CParticle();

	HRESULT Init(void);
	void Update(void);
	static CParticle * Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, int nEffectLife,float fSize,int nSpeed,int nNum, float fAttenuation = 0.9f, std::string name = "data\\TEXTURE\\effect000.jpg");

private:
	
	int m_nSpeed;//���x
	int m_nAngle;//����
	int m_nLife;//����
	int m_nEffectLife;//�q�̎���
	int m_nNum;//��
	std::string m_name;
};

#endif // ! _Particle_H_