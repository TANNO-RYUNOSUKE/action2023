//========================================================================================
//
// ���[�V����
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "motion.h"
#include "debugproc.h"
#include "manager.h"
#include <stdio.h>

//=============================================
//�R���X�g���N�^
//=============================================

CMotion::CMotion()
{
	m_bFinish = false;
	m_bLoop = false;
	m_nCounter = 0;
	m_nNumModel = 0;
	m_nkey = 0;
	m_nNumAll = 0;
	m_nType = 0;
	m_bBlend = false;
	for (int i = 0; i < NUM_KEY_MOTION; i++)
	{
		m_Prevkey[i] = {};
	}
	
	//for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	//{
	//	m_ppModel[nCnt] = DBG_NEW CModel*;
	//}
}
	



//=============================================
//�f�X�g���N�^
//=============================================
CMotion::~CMotion()
{
}
void CMotion::Uninit(void)
{
	/*for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_ppModel[nCnt] != NULL)
		{
			delete m_ppModel[nCnt];
			m_ppModel[nCnt] = NULL;
		}
	}*/
}
void CMotion::Update(void)
{
	CDebugProc * pDeb = CManager::GetDeb();
	if (m_nType > -1 && m_nType <= m_nNumAll)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			KEY anim;
			if (m_Info[m_nType].nNumkey != 0)
			{
				if (m_bBlend)
				{
					anim.pos_x = 0.0f;
					anim.pos_y = 0.0f;
					anim.pos_z = 0.0f;
					anim.rot_x = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].rot_x - m_Prevkey[nCnt].rot_x;
					anim.rot_y = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].rot_y - m_Prevkey[nCnt].rot_y;
					anim.rot_z = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].rot_z - m_Prevkey[nCnt].rot_z;
				}
				else
				{
					anim.pos_x = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].pos_x - m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].pos_x;
					anim.pos_y = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].pos_y - m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].pos_y;
					anim.pos_z = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].pos_z - m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].pos_z;
					anim.rot_x = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].rot_x - m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].rot_x;
					anim.rot_y = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].rot_y - m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].rot_y;
					anim.rot_z = m_Info[m_nType].aKeyInfo[(m_nkey + 1) % m_Info[m_nType].nNumkey].aKey[nCnt].rot_z - m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].rot_z;
				}
			}

			if (anim.rot_x < -D3DX_PI)
			{
				anim.rot_x += D3DX_PI * 2;
			}
			else if (anim.rot_x > D3DX_PI)
			{
				anim.rot_x += -D3DX_PI * 2;
			}
			if (anim.rot_y < -D3DX_PI)
			{
				anim.rot_y += D3DX_PI * 2;
			}
			else if (anim.rot_y > D3DX_PI)
			{
				anim.rot_y += -D3DX_PI * 2;
			}
			if (anim.rot_z < -D3DX_PI)
			{
				anim.rot_z += D3DX_PI * 2;
			}
			else if (anim.rot_z > D3DX_PI)
			{
				anim.rot_z += -D3DX_PI * 2;
			}

			//�p�[�c�̈ʒu�A������ݒ�
			D3DXVECTOR3 pos ;
			D3DXVECTOR3 rot;
			if (m_bBlend)
			{
				pos = D3DXVECTOR3(m_Prevkey[nCnt].pos_x,
					m_Prevkey[nCnt].pos_y,
					m_Prevkey[nCnt].pos_z) +
					D3DXVECTOR3(anim.pos_x, anim.pos_y, anim.pos_z) * ((float)m_nCounter / (float)m_Info[m_nType].aKeyInfo[m_nkey].nFrame);
				rot = D3DXVECTOR3(m_Prevkey[nCnt].rot_x,
					 m_Prevkey[nCnt].rot_y,
					 m_Prevkey[nCnt].rot_z) +
					D3DXVECTOR3(anim.rot_x, anim.rot_y, anim.rot_z) *  ((float)m_nCounter / (float)m_Info[m_nType].aKeyInfo[m_nkey].nFrame);
			}
			else
			{
				pos = D3DXVECTOR3(m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].pos_x,
					m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].pos_y,
					m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].pos_z) +
					D3DXVECTOR3(anim.pos_x, anim.pos_y, anim.pos_z) * ((float)m_nCounter / (float)m_Info[m_nType].aKeyInfo[m_nkey].nFrame);
				rot = D3DXVECTOR3(m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].rot_x,
					m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].rot_y,
					m_Info[m_nType].aKeyInfo[m_nkey].aKey[nCnt].rot_z) +
					D3DXVECTOR3(anim.rot_x, anim.rot_y, anim.rot_z) *  ((float)m_nCounter / (float)m_Info[m_nType].aKeyInfo[m_nkey].nFrame);
			}
			//pDeb->Print("���[�V�����p�x(x:%f,y:%f,z:%f)\n", rot.x, rot.y, rot.z);

			(*m_ppModel[nCnt])->SetPos((*m_ppModel[nCnt])->GetOffset() +pos);
			(*m_ppModel[nCnt])->SetRot(rot);
			
		}
		m_nCounter++;
		if (m_nCounter >= m_Info[m_nType].aKeyInfo[m_nkey].nFrame)
		{
			m_bBlend = false;
			m_nkey++;
			m_nCounter = 0;
		}
		if (m_nkey >= m_Info[m_nType].nNumkey)
		{
			if (m_Info[m_nType].bLoop == true)
			{
				m_nkey = 0;
			}
			else
			{
				m_nkey = 0;
				m_nType = 0;
			}
		}
	}
}

void CMotion::SetInfo(INFO Info)
{
	if (m_nNumAll < NUM_INFO)
	{
		m_Info[m_nNumAll] = Info;
		m_nNumAll++;
	}
}




//====================================================================
//���[�V�����̃��[�h����
//====================================================================
void CMotion::Load(char * cFile)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

				 //�t�@�C�����J��
	//pFile = fopen("", "r");

	//�t�@�C�����J��
	pFile = fopen(cFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		int nNum = 0;//���f���̍ő吔
		int nNumMotion = 0;

		char aString[256] = {};				//�S�~��
		char aStartMessage[256] = {};		//�X�^�[�g���b�Z�[�W
		char aModelMessage[256] = {};		//���f���p���b�Z�[�W
		char aCharaSetMessage[128] = {};	//�L�����Z�b�g���b�Z�[�W
		char aPartsSetMessage[128] = {};	//�p�[�c�Z�b�g���b�Z�[�W
		char aMotionSetMessage[128] = {};	//���[�V�����Z�b�g���b�Z�[�W
		char KeySetMessage[128] = {};		//�L�[�Z�b�g���b�Z�[�W
		char KeyStartMessage[128] = {};		//�L�[�X�^�[�g���b�Z�[�W
		char aNameMessage[128] = {};		//�ϐ����̃��b�Z�[�W
		char aPartsEndMessage[128] = {};	//�p�[�c�G���h���b�Z�[�W
		char aCharaEndMessage[128] = {};	//�L�����G���h���b�Z�[�W
		char aEndMessage[128] = {};			//�I�����b�Z�[�W
		char aType[128] = {};				//�I�����b�Z�[�W
		char aBool[128] = {};				//bool�ϊ��p���b�Z�[�W


		CMotion::INFO info;
		// �ǂݍ��݊J�n-----------------------------------------------------
		while (1)
		{//�uSCRIPT�v��T��
			fscanf(pFile, "%s", &aStartMessage[0]);
			if (strcmp(&aStartMessage[0], "SCRIPT") == 0)
			{
				// ���f�����ǂݍ���-----------------------------------------------------
				while (1)
				{//�uNUM_MODEL�v��T��
					fscanf(pFile, "%s", &aModelMessage[0]);
					if (strcmp(&aModelMessage[0], "NUM_MODEL") == 0)
					{

						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &nNum);		//���f�����̐ݒ�
						SetNumModel(nNum);
						

					}
					if (strcmp(&aModelMessage[0], "NUM_MOTION") == 0)
					{

						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &nNumMotion);		//���[�V�������̒��
						break;
					}
				}
				
				for (int nCnt = 0; nCnt < nNum; )
				{
					fscanf(pFile, "%s", &aModelMessage[0]);
					if (strcmp(&aModelMessage[0], "MODEL_FILENAME") == 0)
					{

						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%s", &aCharaSetMessage[0]);		//���f�����̐ݒ�
						
						(*m_ppModel[nCnt]) = CModel::Create(&aCharaSetMessage[0]);
						nCnt++;
						if (nCnt >= NUM_MODEL -1 )
						{
							break;
						}
					}
				}

				//�L�����N�^�[���ǂݍ���-----------------------------------------------------
				while (1)
				{//�uPARTSSET�v��T��
					fscanf(pFile, "%s", &aPartsSetMessage[0]);
					if (strcmp(&aPartsSetMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//�C���f�b�N�X��ݒ�
							}
							if (strcmp(&aNameMessage[0], "PARENT") == 0)
							{
								int nParent;
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nParent);	//�e���f���̃C���f�b�N�X��ݒ�
								if (nParent > -1)
								{
									(*m_ppModel[nCntModel])->SetParent(*m_ppModel[nParent]);
								}
								else
								{
									(*m_ppModel[nCntModel])->SetParent(NULL);
								}
							
							}
							if (strcmp(&aNameMessage[0], "POS") == 0)
							{
								D3DXVECTOR3 pos;
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &pos.x);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &pos.y);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &pos.z);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								(*m_ppModel[nCntModel])->SetPos(pos);
								(*m_ppModel[nCntModel])->SetOffset(pos);
							}
							if (strcmp(&aNameMessage[0], "ROT") == 0)
							{
								D3DXVECTOR3 rot;
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &rot.x);				////�����̏����ݒ�
								fscanf(pFile, "%f", &rot.y);				////�����̏����ݒ�
								fscanf(pFile, "%f", &rot.z);				////�����̏����ݒ�
								(*m_ppModel[nCntModel])->SetRot(rot);
							}
							if (strcmp(&aNameMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= nNum)
						{
							break;
						}
					}
				}

				// ���[�V�������ǂݍ���-----------------------------------------------------
				while (1)
				{//�uMOTIONSET�v��T��
					fscanf(pFile, "%s", &aMotionSetMessage[0]);
					if (strcmp(&aMotionSetMessage[0], "MOTIONSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aNameMessage[0]);
							if (strcmp(&aNameMessage[0], "LOOP") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%s", &aBool[0]);	//���[�v���邩�ǂ�����ݒ�
								info.bLoop = (strcmp(&aBool[0], "1") == 0 ? true : false);			//bool�^�̏�����
							}
							if (strcmp(&aNameMessage[0], "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &info.nNumkey);	//�L�[�̑�����ݒ�
								break;
							}
						}

						// �L�[���ǂݍ���-----------------------------------------------------
						while (1)
						{//�uKEYSET�v��T��
							fscanf(pFile, "%s", &KeySetMessage[0]);
							if (strcmp(&KeySetMessage[0], "KEYSET") == 0)
							{
								while (1)
								{//�uFRAME�v��T��
									fscanf(pFile, "%s", &aNameMessage[0]);
									if (strcmp(&aNameMessage[0], "FRAME") == 0)
									{
										fscanf(pFile, "%s", &aString[0]);
										fscanf(pFile, "%d", &info.aKeyInfo[nCntKeySet].nFrame);	//�L�[�t���[����ݒ�
										break;
									}
								}

								while (1)
								{//�uKEY�v��T��
									fscanf(pFile, "%s", &KeyStartMessage[0]);
									if (strcmp(&KeyStartMessage[0], "KEY") == 0)
									{
										while (1)
										{//�e��ϐ���T��
											fscanf(pFile, "%s", &aNameMessage[0]);
											if (strcmp(&aNameMessage[0], "POS") == 0)
											{

												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &info.aKeyInfo[nCntKeySet].aKey[nCntKey].pos_x);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &info.aKeyInfo[nCntKeySet].aKey[nCntKey].pos_y);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &info.aKeyInfo[nCntKeySet].aKey[nCntKey].pos_z);	//�ʒu��ݒ�
											}
											if (strcmp(&aNameMessage[0], "ROT") == 0)
											{
												fscanf(pFile, "%s", &aString[0]);
												fscanf(pFile, "%f", &info.aKeyInfo[nCntKeySet].aKey[nCntKey].rot_x);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &info.aKeyInfo[nCntKeySet].aKey[nCntKey].rot_y);	//�ʒu��ݒ�
												fscanf(pFile, "%f", &info.aKeyInfo[nCntKeySet].aKey[nCntKey].rot_z);	//�ʒu��ݒ�
												break;
											}
										}
									}
									if (strcmp(&KeyStartMessage[0], "END_KEY") == 0)
									{
										nCntKey++;
										if (nCntKey >= nNum)
										{
											break;
										}
									}
								}
							}
							if (strcmp(&KeySetMessage[0], "END_KEYSET") == 0)
							{
								nCntKey = 0;
								nCntKeySet++;
								if (nCntKeySet >= info.nNumkey)
								{
									break;
								}
							}
						}
					}
					if (strcmp(&aMotionSetMessage[0], "END_MOTIONSET") == 0)
					{
						SetInfo(info);
						nCntKeySet = 0;
						nCntMotion++;
						if (nCntMotion >= nNumMotion)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aStartMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		//if (m_ppModel != NULL)
		//{
		//	delete[] m_ppModel;
		//	m_ppModel = NULL;
		//}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}
