//========================================================================================
//
// ���͏���
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "input.h"
//==============================
//�ÓI�����o
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==============================
//�R���X�g���N�^�A�f�X�g���N�^
//==============================
CInput::CInput()
{
	m_pDevice = NULL;
}

CInput::~CInput()
{
}

//==============================
//����������
//==============================
HRESULT CInput:: Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	
	return S_OK;
}
//======================================
//�I������
//======================================
void  CInput::Uninit(void)
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire(); //�A�N�Z�X����j��
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//==============================
//�R���X�g���N�^�A�f�X�g���N�^
//==============================
CInputKeyboard::CInputKeyboard()
{
	m_aKeyState[0] = {};
	m_aKeyStateRelease[0] = {};
	m_aKeyStateTrigger[0] = {};
	m_aKeyStateRepeat[0] = {};
}

CInputKeyboard::~CInputKeyboard()
{
}
//======================================
//�L�[�{�[�h������
//======================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//���̓f�o�C�X�̐����i�L�[�{�[�h�j
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�̃A�N�Z�X�����擾
	m_pDevice->Acquire();

	return S_OK;
}
//======================================
//�L�[�{�[�h�I��
//======================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//======================================
//�L�[�{�[�h�X�V
//======================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h��PRESS����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//======================================
//�v���X���
//======================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0X80) ? true : false;
}
//======================================
//�g���K�[���
//======================================
bool  CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0X80) ? true : false;
}
//======================================
//�����[�X���
//======================================
bool  CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0X80) ? true : false;
}
//======================================
//���s�[�g���
//======================================
bool  CInputKeyboard::GetRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0X80) ? true : false;
}
//==============================
//�R���X�g���N�^�A�f�X�g���N�^
//==============================
CInputGamePad::CInputGamePad()
{
	m_JoykeyState[0] = {};
	m_JoykeyStateTrigger[0] = {};
}

CInputGamePad::~CInputGamePad()
{
}
//======================================
//�Q�[���p�b�h������
//======================================
HRESULT CInputGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(true);

	//�[���N���A
	ZeroMemory(&m_JoykeyState, sizeof(m_JoykeyState));
	ZeroMemory(&m_JoykeyStateTrigger, sizeof(m_JoykeyStateTrigger));

	return S_OK;
}
//======================================
//�Q�[���p�b�h�I��
//======================================
void CInputGamePad::Uninit(void)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}
//======================================
//�Q�[���p�b�h�X�V
//======================================
void CInputGamePad::Update(void)
{
	int nCount;
	XINPUT_STATE JoykeyState;

	for (nCount = 0; nCount < PLAYER_MAX; nCount++)
	{
		if (XInputGetState(nCount, &JoykeyState) == ERROR_SUCCESS)
		{
			m_JoykeyStateTrigger[nCount].Gamepad.wButtons = (m_JoykeyState[nCount].Gamepad.wButtons ^ JoykeyState.Gamepad.wButtons) & JoykeyState.Gamepad.wButtons;
			m_JoykeyStateTrigger[nCount].Gamepad.bLeftTrigger = (m_JoykeyState[nCount].Gamepad.bLeftTrigger ^ JoykeyState.Gamepad.bLeftTrigger) & JoykeyState.Gamepad.bLeftTrigger;
			m_JoykeyStateTrigger[nCount].Gamepad.bRightTrigger = (m_JoykeyState[nCount].Gamepad.bRightTrigger ^ JoykeyState.Gamepad.bRightTrigger) & JoykeyState.Gamepad.bRightTrigger;

			m_JoykeyState[nCount] = JoykeyState;
		}
	}

}
//======================================
//�v���X���
//======================================
bool CInputGamePad::GetPress(JOYKEY Key, int nPlayer)
{
	return (m_JoykeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//======================================
//�g���K�[���
//======================================
bool CInputGamePad::GetTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoykeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//======================================
//�y�_���v���X���L
//======================================
bool CInputGamePad::GetPedalL(int nPlayer)
{
	return (m_JoykeyState[nPlayer].Gamepad.bLeftTrigger & (0x01 << '\0')) ? true : false;
}
//======================================
//�y�_���v���X���R
//======================================
bool CInputGamePad::GetPedalR(int nPlayer)
{
	return (m_JoykeyState[nPlayer].Gamepad.bRightTrigger & (0x01 << '\0')) ? true : false;
}
//======================================
//�y�_���g���K�[���L
//======================================
bool CInputGamePad::GetPedalTriggerL(int nPlayer)
{
	return (m_JoykeyStateTrigger[nPlayer].Gamepad.bLeftTrigger & (0x01 << '\0')) ? true : false;
}
//======================================
//�y�_���g���K�[���R
//======================================
bool CInputGamePad::GetPedalTriggerR(int nPlayer)
{
	return (m_JoykeyStateTrigger[nPlayer].Gamepad.bRightTrigger & (0x01 << '\0')) ? true : false;
}
//======================================
//�X�e�B�b�N���L
//======================================
D3DXVECTOR3 CInputGamePad::GetStickL(int nPlayer, float Dead)
{
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)m_JoykeyState[nPlayer].Gamepad.sThumbLX / SHRT_MAX;
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)m_JoykeyState[nPlayer].Gamepad.sThumbLY / SHRT_MAX;
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}
//======================================
//�X�e�B�b�N���R
//======================================
D3DXVECTOR3 CInputGamePad::GetStickR(int nPlayer, float Dead)
{
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)m_JoykeyState[nPlayer].Gamepad.sThumbRX / (SHRT_MAX);
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.y = (float)m_JoykeyState[nPlayer].Gamepad.sThumbRY / (SHRT_MAX);
	if (fabsf(Stick.y) < Dead)
	{
		Stick.y = 0.0f;
	}
	Stick.y *= -1;

	return Stick;
}
//==============================
//�R���X�g���N�^�A�f�X�g���N�^
//==============================
CInputMouse::CInputMouse()
{
	m_pDevMouse = NULL;

}

CInputMouse::~CInputMouse()
{
}

//======================================
//�}�E�X������
//======================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���̓f�o�C�X�̐����i�}�E�X�j
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevMouse, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	if (FAILED(m_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	//�}�E�X�̃A�N�Z�X�����擾
	m_pDevMouse->Acquire();

	return S_OK;
}
//======================================
//�}�E�X�I��
//======================================
void CInputMouse::Uninit(void)
{
	//���̓f�o�C�X�̔j��
	if (m_pDevMouse != NULL)
	{
		m_pDevMouse->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X����j��
		m_pDevMouse->Release();
		m_pDevMouse = NULL;
	}

	//Directinput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
//======================================
//�}�E�X�X�V
//======================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE mouse;
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevMouse->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (nCntKey = 0; nCntKey < CInputMouse::MOUSE_MAX; nCntKey++)
		{
			//�g���K�[���
			m_MouseStateTrigger[nCntKey] = (m_mouseState.rgbButtons[nCntKey] ^ mouse.rgbButtons[nCntKey])
				& mouse.rgbButtons[nCntKey];
			m_MouseStateRelease[nCntKey] = (m_mouseState.rgbButtons[nCntKey] ^ mouse.rgbButtons[nCntKey])
				& m_mouseState.rgbButtons[nCntKey];
			//���͏��̕ۑ�
			m_mouseState.rgbButtons[nCntKey] = mouse.rgbButtons[nCntKey];
			m_mouseState.lX = mouse.lX;
			m_mouseState.lY = mouse.lY;
			m_mouseState.lZ = mouse.lZ;
		}
	
	}
	else
	{
		m_pDevMouse->Acquire();
	}
}
//=============================
//�}�E�X�̓���
//=============================
bool CInputMouse::GetPress(MOUSE nKey)
{
	return (m_mouseState.rgbButtons[nKey] & 0x80) ? true : false;
}
//=============================
//�}�E�X�̈ړ��擾
//=============================
D3DXVECTOR3 CInputMouse::GetMove(void)
{
	return D3DXVECTOR3(((float)m_mouseState.lX), (-(float)m_mouseState.lY), (-(float)m_mouseState.lZ));
}