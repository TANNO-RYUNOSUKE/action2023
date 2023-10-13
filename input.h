#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
//====================================
//
//���͏���
//Author:�O�엳�V��
//
//====================================
//�}�N����`
#define NUM_KEY (256) //�L�[�̍ő吔
#define PLAYER_MAX (4) //�v���C���[�̍ő吔

//���̓C���X�^���X
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput; //�{��
	LPDIRECTINPUTDEVICE8 m_pDevice;//�f�o�C�X
};
//====================================
//�L�[�{�[�h
class CInputKeyboard:public CInput//�C���v�b�g�N���X���p��
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	 HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	 void Uninit(void);
	 void Update(void);
	 bool GetPress(int nKey);
	 bool GetTrigger(int nKey);
	 bool GetRelease(int nKey);
	 bool GetRepeat(int nKey);
private:
	BYTE m_aKeyState[NUM_KEY]; //���͏��
	BYTE m_aKeyStateTrigger[NUM_KEY];//���͏��(�g���K�[)
	BYTE m_aKeyStateRelease[NUM_KEY];//���͏��(�����[�X)
	BYTE m_aKeyStateRepeat[NUM_KEY];//���͏��(���s�[�g)
};
//====================================
//�R���g���[���[
class CInputGamePad:public CInput
{
public:
	typedef enum
	{
		Button_UP = 0,		//��L�[
		Button_DOWN,		//���L�[
		Button_LEFT,		//���L�[
		Button_RIGHT,		//�E�L�[
		Button_START,		//�X�^�[�g
		Button_BACK,		//�o�b�N
		Button_LStickKey,	//���g���K�[������
		Button_RStickKey,	//�E�g���K�[������
		Button_LB,			//���w���{�^��
		Button_RB,			//�E�w���{�^��
		Button_UNKOWN_0,	//�����Ȃ�
		Button_UNKOWN_1,	//�����Ȃ�
		Button_A,			//A�{�^��
		Button_B,			//B�{�^��
		Button_X,			//X�{�^��
		Button_Y,			//Y�{�^��
		/*Button_test,*/
		Button_MAX			//�{�^���ő吔
	}JOYKEY;//�L�[�ԍ�

	CInputGamePad();
	~CInputGamePad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(JOYKEY Key, int nPlayer);
	bool GetTrigger(JOYKEY Key, int nPlayer);

	bool GetPedalL(int nPlayer);
	bool GetPedalR(int nPlayer);
	bool GetPedalTriggerL(int nPlayer);
	bool GetPedalTriggerR(int nPlayer);
	D3DXVECTOR3 GetStickL(int nPlayer, float Dead);
	D3DXVECTOR3 GetStickR(int nPlayer, float Dead);

private:
	XINPUT_STATE m_JoykeyState[PLAYER_MAX]; //�L�[���͏��
	XINPUT_STATE m_JoykeyStateTrigger[PLAYER_MAX];//���͏��(�g���K�[)
};
//====================================
//�}�E�X
class CInputMouse:CInput
{
public:

	typedef enum
	{
		MOUSE_LEFT = 0,
		MOUSE_RIGTH,
		MOUSE_CENTER,
		MOUSE_BUTTON1,
		MOUSE_MAX
	}MOUSE;

	CInputMouse();
	~CInputMouse();


	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(MOUSE nKey);
	bool GetTrigger(MOUSE nKey) { return (m_MouseStateTrigger[nKey] & 0x80) ? true : false; }
	bool GetRelease(MOUSE nKey) { return (m_MouseStateRelease[nKey] & 0x80) ? true : false; }
	D3DXVECTOR3 GetMove(void);
private:
	LPDIRECTINPUTDEVICE8 m_pDevMouse;	//�}�E�X�̃f�o�C�X
	DIMOUSESTATE m_mouseState;
	BYTE m_MouseState[MOUSE_MAX];			//���͏��
	BYTE m_MouseStateTrigger[MOUSE_MAX];	//���͏��
	BYTE m_MouseStateRelease[MOUSE_MAX];	//���͏��
};




#endif // !_INPUT_H_