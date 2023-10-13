//========================================================================================
//
// カメラ
// Author: 丹野 竜之介
//
//========================================================================================
#include "camera.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"


//=============================================
//コンストラクタ、デストラクタ
//=============================================
CCamera::CCamera()
{
	m_fLengthCamera = 0;
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRdest = m_posR;
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVdest = m_posR;
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
}

CCamera::~CCamera()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CCamera::Init()
{
	nCntShake = 0;
	m_fLengthCamera = +500;
	m_bDirection = false;
	m_moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRdest = m_posR;
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVdest = m_posR;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.5f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CCamera::Uninit()
{

}
//=============================================
//更新関数
//=============================================
void CCamera::Update()
{
	CInputGamePad * pInputGamePad = CManager::GetInputGamePad();
	CDebugProc * pDeb = CManager::GetDeb();

	pDeb->Print("視点の座標(X:%f,Y:%f,Z:%f)\n", m_posV.x, m_posV.y, m_posV.z);
	pDeb->Print("注視点の座標(X:%f,Y:%f,Z:%f)\n", m_posR.x, m_posR.y, m_posR.z);
	pDeb->Print("カメラの角度(X:%f,Y:%f,Z:%f)\n", m_rot.x, m_rot.y, m_rot.z);
	pDeb->Print("カメラの距離:%f\n", m_fLengthCamera);
	CInputMouse * pMouse = CManager::GetInputMouse();
	//if (pMouse->GetPress(CInputMouse::MOUSE_LEFT) == true)
	//{//視点の移動

	//	m_rot.y -= pMouse->GetMove().x * 0.01f;
	//	m_rot.z -= pMouse->GetMove().y * 0.01f;
	//	m_posV.x = m_posR.x + cosf(m_rot.z) * sinf(m_rot.y) * m_fLengthCamera;
	//	m_posV.z = m_posR.z + cosf(m_rot.z) * cosf(m_rot.y) *m_fLengthCamera;
	//	m_posV.y = m_posR.y + sinf(m_rot.z) *m_fLengthCamera;

	//}
	//
	//if (pMouse->GetPress(CInputMouse::MOUSE_RIGTH) == true)
	//	{//注視点の移動

	//		m_rot.y += pMouse->GetMove().x * 0.003f;
	//		m_rot.z += pMouse->GetMove().y * 0.003f;
	//		m_posR.x = m_posV.x - cosf(m_rot.z) * sinf(m_rot.y) * m_fLengthCamera;
	//		m_posR.z = m_posV.z - cosf(m_rot.z) * cosf(m_rot.y) *m_fLengthCamera;
	//		m_posR.y = m_posV.y - sinf(m_rot.z) *m_fLengthCamera;

	//	}

	//if (CManager::GetHitStop() == 0)
	//{
	//	m_bDirection = false;
	//}
	//if (m_bDirection)
	//{
	//	
	//	float nSplit = 1;
	//	if ((CManager::GetDistance(m_vecCamera) / 2000.0f) != 0)
	//	{
	//		nSplit = (CManager::GetDistance(m_vecCamera) / 2000.0f);
	//	
	//	}
	//	m_rot.y +=  (0.001f / (float)nSplit);
	//	if (CGame::GetMeshfield()->MeshRay(m_posR,m_posV))
	//	{
	//		m_rot.y += (0.1f / (float)nSplit);
	//		m_rot.z += (0.1f / (float)nSplit);
	//	}
	//	
	//	m_posVdest.x = m_posR.x + cosf(m_rot.z) * sinf(m_rot.y) * m_fLengthCamera;
	//	m_posVdest.z = m_posR.z + cosf(m_rot.z) * cosf(m_rot.y) *m_fLengthCamera;
	//	m_posVdest.y = m_posR.y + sinf(m_rot.z) *m_fLengthCamera;
	//}
	//else
	//{
	//	m_rot.y += pInputGamePad->GetStickR(0, 0.1f).x * 0.1f;
	//	m_rot.z += pInputGamePad->GetStickR(0, 0.1f).y * 0.05f;
	//	m_rot.y += pMouse->GetMove().x * 0.006f;
	//	m_rot.z -= pMouse->GetMove().y * 0.003f;
	//	m_posVdest.x = m_posR.x + cosf(m_rot.z) * sinf(m_rot.y) * m_fLengthCamera;
	//	m_posVdest.z = m_posR.z + cosf(m_rot.z) * cosf(m_rot.y) *m_fLengthCamera;
	//	m_posVdest.y = m_posR.y + sinf(m_rot.z) *m_fLengthCamera;
	//}





	m_posR += (m_posRdest - m_posR) * 0.25f;
	m_posV += (m_posVdest - m_posV) * 0.25f;
	if (m_rot.y > 3.14f)
	{
		m_rot.y = -3.14f;
	}
	if (m_rot.y < -3.14f)
	{
		m_rot.y = 3.14f;
	}
	if (m_rot.z > 3.14f / 2)
	{
		m_rot.z = 3.14f / 2;

	}
	if (m_rot.z < -3.14f / 2)
	{
		m_rot.z = -3.14f / 2;

	}
	nCntShake--;

	if (nCntShake <= 0)
	{
		nCntShake = 0;
	}
	else
	{
		m_posR.x += (float)(rand() % nCntShake * 2 - nCntShake);
		m_posR.z += (float)(rand() % nCntShake * 2 - nCntShake);
		m_posR.y += (float)(rand() % nCntShake * 2 - nCntShake);
		m_posV.x += (float)(rand() % nCntShake * 2 - nCntShake);
		m_posV.z += (float)(rand() % nCntShake * 2 - nCntShake);
		m_posV.y += (float)(rand() % nCntShake * 2 - nCntShake);
	}


	//ベクトルを出す
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecCamera = m_posV - m_posR;

	////デバッグカメラ
	//if (pInputKeyboard->GetPress(DIK_W))
	//{
	//	move.x -= sinf(m_rot.y) * 5.0f;
	//	move.z -= cosf(m_rot.y) * 5.0f;

	//}
	//if (pInputKeyboard->GetPress(DIK_S))
	//{
	//	move.x += sinf(m_rot.y) * 5.0f;
	//	move.z += cosf(m_rot.y) * 5.0f;

	//}
	//if (pInputKeyboard->GetPress(DIK_A))
	//{
	//	move.x += sinf(m_rot.y + (D3DX_PI / 2)) * 5.0f;
	//	move.z += cosf(m_rot.y + (D3DX_PI / 2)) * 5.0f;
	//}
	//if (pInputKeyboard->GetPress(DIK_D))
	//{
	//	move.x -= sinf(m_rot.y + (D3DX_PI / 2)) * 5.0f;
	//	move.z -= cosf(m_rot.y + (D3DX_PI / 2)) * 5.0f;
	//}
	//if (pInputKeyboard->GetPress(DIK_LSHIFT))
	//{
	//	move.y -= 5.0f;
	//}
	//if (pInputKeyboard->GetPress(DIK_LCONTROL))
	//{
	//	move.y += 5.0f;
	//}
	//m_posRdest += move;
	//m_posVdest += move;
}
//=============================================
//設定関数
//=============================================
void CCamera::Set()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();

	//プロジェクションマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリクスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		300000.0f);

	//プロジェクションマトリクスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリクスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリクスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
