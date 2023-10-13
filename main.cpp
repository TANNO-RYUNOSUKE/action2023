//========================================================================================
//
// DirectX ��N��
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include"main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "debugproc.h"

//�}�N����`
#define CLASS_NAME "WindowClass"     //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "action02"  //�E�B���h�E�̖��O
#define ID_TIMER (131)
#define TIMER_INTERVAL (1000/60)


//�v���g�^�C�v�錾
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================
//���C���֐�
//=============================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePlev, LPSTR lpCmdline, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	CManager * pManager;
	CDebugProc * pDev;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,//�E�B���h�E�X�^�C��
		WindowPloc, //�E�B���h�E�v���V�[�W��
		0, //�ʏ�g�p���Ȃ�
		0, //�ʏ�g�p���Ȃ�
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�}�E�X�J�[�\��
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd; //�E�B���h�E�n���h��
	MSG msg;

	

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,//�E�B���h�E�����X���W
		CW_USEDEFAULT,//�E�B���h�E�����Y���W
		(rect.right -rect.left),//��
		(rect.bottom - rect.top),//����
		NULL,//�e�E�B���h�E�̃n���h��
		NULL,//���j���[�n���h���܂��͎q�E�B���h�E��ID
		hInstance,//�C���X�^���X�n���h��
		NULL);
	
	
	pManager = DBG_NEW  CManager;
	int nCountFPS = 0;

	//�������ݒ�
	if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))
	{
		return -1;
	};
	pDev = CManager::GetDeb();

	
	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();//���ݎ������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();
	srand(((unsigned int)timeGetTime()));
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	DispatchMessage(&msg);
	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			 //FPS���v��
			    nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60���̂P�b�o��
				dwExecLastTime = dwCurrentTime;
				pDev->Print("FPS:%d\n", nCountFPS);


				//�X�V����
				pManager->Update();

				//�`�揈��
				pManager->Draw();
		
			

				dwFrameCount++; //�t���[���J�E���g�����Z
			
			}
			

		}
	}
	if (pManager != NULL)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}
	UnregisterClass(CLASS_NAME, wcex.hInstance);



	return (int)msg.wParam;

}
//=============================================
//�E�B���h�E�v���V�[�W��
//=============================================
LRESULT CALLBACK WindowPloc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	

	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E��j��
		PostQuitMessage(0);
		break;
	
	case WM_KEYDOWN: //�L�[�������ꂽ��
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j��
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j��
			DestroyWindow(hWnd);
		}
		else if (nID == IDNO)
		{
			return 0;
		}
		break;
	case WM_LBUTTONDOWN: //���N���b�N
						 //�ΏۃE�B���h�E�Ƀt�H�[�J�X
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

