//=============================================================================
//
// �T�E���h���� [sound.h]
// Author :�O�엳�V��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
//�N���X��`
class CSound
{
public:

	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_SE_MISSILE,
		SOUND_LABEL_SE_SLASH,
		SOUND_LABEL_SE_SLASHHIT,
		SOUND_LABEL_SE_SLASHSWING,
		SOUND_LABEL_SE_DESTRUCT,
		SOUND_LABEL_SE_HIGHSPEED,
		SOUND_LABEL_SE_LOCKON,
		SOUND_LABEL_SE_JUMP,
		SOUND_LABEL_SE_SHOCK,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
private:
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice ;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apdata[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSize[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};



#endif
