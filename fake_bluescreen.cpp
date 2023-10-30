//========================================================================================
//
// ÉQÅ[ÉgUI
// Author: íOñÏ ó≥îVâÓ
//
//========================================================================================
#include "Fake_BlueScreen.h"
#include "manager.h"
#include "renderer.h"
#include "enemymanager.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "scene.h"

CFake_BlueScreen::CFake_BlueScreen() :CObject(6)
{
}

CFake_BlueScreen::~CFake_BlueScreen()
{
}
//=============================================
//èâä˙âªä÷êî
//=============================================
HRESULT CFake_BlueScreen::Init()
{
	m_nLife = 120;
	m_pScreen = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH* 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_HEIGHT , SCREEN_WIDTH, 6, "data\\TEXTURE\\UI\\fake_bluescreen.png");
	CSound * pSound = CManager::GetInstance()->GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_DEATH);
	return S_OK;
}
//=============================================
//èIóπä÷êî
//=============================================
void CFake_BlueScreen::Uninit()
{
}
//=============================================
//çXêVä÷êî
//=============================================
void CFake_BlueScreen::Update()
{
	m_nLife--;
	if (m_nLife <= 0)
	{
		CGame::GetFade()->FadeOut(CGame::MODE_RESULT);
	}

}
//=============================================
//ï`âÊä÷êî
//=============================================
void CFake_BlueScreen::Draw()
{
	
}

CFake_BlueScreen * CFake_BlueScreen::Create()
{
	CFake_BlueScreen * pObject2D = NULL;
	pObject2D = DBG_NEW  CFake_BlueScreen();
	
	pObject2D->Init();
	return pObject2D;
}