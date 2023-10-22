//========================================================================================
//
// �G�t�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "effect.h"
#include "input.h"

#include "enemy.h"
#include "sound.h"
#include "texture.h"


LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fSize = 0;
}
//=============================================
//�f�X�g���N�^
//=============================================
CEffect::~CEffect()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CEffect::Init(char * pName)
{
	CTexture * pTex = CManager::GetInstance()->GetTexture();

	m_nIdxTex[0] = pTex->Regist(pName);
	CBillboard::Init();
	

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CEffect::Uninit()
{
	
	CBillboard::Uninit();
}
//=============================================
//�X�V�֐�
//=============================================
void CEffect::Update()
{
	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	
	pVtx[0].col = m_Color;
	pVtx[1].col = m_Color;
	pVtx[2].col = m_Color;
	pVtx[3].col = m_Color;
	
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-GetWidth(), +GetHeight(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+GetWidth(), +GetHeight(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-GetWidth(), -GetHeight(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+GetWidth(), -GetHeight(), 0.0f);

	m_pVtxBuff->Unlock();
	SetPos(GetPos() + m_move);
	m_move *= m_fAttenuation;
	SetWidth(GetWidth()  *m_fAttenuation);
	SetHeight(GetHeight() *m_fAttenuation);
	m_Color.a = (float)m_nLife / (float)m_nMaxLife;
	m_nLife--;
	SetMove(GetMove()* 0.95f);
	if (m_nLife <= 0)
	{
		CObject::Release();
	}


}
//=============================================
//�`��֐�
//=============================================
void CEffect::Draw()
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //�t�H�O�̖�����
	//a�u�����f�B���O�����Z�����ɐݒ�

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	CBillboard::Draw();

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 80);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//a�u�����f�B���O��ʏ�ɐݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
}
//=============================================
//�����֐�
//=============================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, D3DXCOLOR col, float fsize, float fAttenuation, char * pName)
{
	CEffect * pEffect = NULL;
	pEffect = DBG_NEW CEffect(6);

	pEffect->m_Color = col;
	pEffect->SetPos(pos);
	pEffect->SetWidth(fsize);
	pEffect->SetHeight(fsize);
	pEffect->m_move = move;
	pEffect->m_nLife = nLife;
	pEffect->m_nMaxLife = nLife;
	pEffect->m_fAttenuation = fAttenuation;
	pEffect->Init(pName);
	return pEffect;
}

