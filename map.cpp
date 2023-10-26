#include "map.h"
#include "manager.h"
#include "scene.h"
#include "gate_UI.h"
#include "Xmanager.h"
#include "objectX.h"
#include <stdio.h>
#include <assert.h>
//====================================-----
//�}�b�v���[�_�[

CMap::CMap()
{
}

CMap::~CMap()
{
}


HRESULT CMap::Load(char * path, CPlayer * pPlayer)
{
	CObjectX ** pObjectX = CManager::GetInstance()->GetXManager()->GetX();

	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			pObjectX[i]->Release();
		}
	}
	//�ϐ��錾
	int nMapID[c_nObjectX * c_nObjectY] = {};
	int nCount = 0;;
	//�t�@�C���|�C���^�錾
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen(path, "r");
	//�t�@�C����ǂݍ���
	if (pFile != NULL)
	{//�t�@�C�����J�����Ȃ�
	
	 //�t�@�C���ɓǂݍ���
		for (; fscanf(pFile, "%d,\n", &nMapID[nCount]) != EOF; )
		{
			nCount++;
			if (nCount >= c_nObjectX * c_nObjectY -1)
			{
				break;
			}
		}
	}
	else
	{
		return E_FAIL;
	}
	//�t�@�C�������
	fclose(pFile);

	for (int i = 0; i < c_nObjectX ; i++)
	{
		for (int j = 0; j < c_nObjectY; j++)
		{
			D3DXVECTOR3 pos{ 550.0f*i,-400.0f*j, 0 };
			switch (nMapID[i + j * c_nObjectX])
			{
			case -1://��
			case 0://��
				break;
			case 1://�v���C���[
				CObjectX::Create("data\\MODEL\\corridor_ceiling.x", pos);
				CObjectX::Create("data\\MODEL\\corridor_wall.x", pos);
				CObjectX::Create("data\\MODEL\\corridor_floor.x", pos);
				if (pPlayer != NULL)
				{
					pos.y += 100.0f;
					pos.x += 240.0f;
					pPlayer->SetPos(pos);
				}
				else
				{
					assert(false);
				}
				break;
			case 2://�ʏ�u���b�N
				CObjectX::Create("data\\MODEL\\corridor_ceiling.x", pos);
				CObjectX::Create("data\\MODEL\\corridor_wall.x", pos);
				CObjectX::Create("data\\MODEL\\corridor_floor.x", pos);
				break;
			case 3://���
			
				CObjectX::Create("data\\MODEL\\corridor_wall.x", pos);
				CObjectX::Create("data\\MODEL\\corridor_floor.x", pos);
				break;
			case 4://����
				CObjectX::Create("data\\MODEL\\corridor_ceiling.x", pos);
				CObjectX::Create("data\\MODEL\\corridor_wall.x", pos);
			
				break;
			case 5://��������
				CObjectX::Create("data\\MODEL\\corridor_wall.x", pos);
				break;
			case 6://��������֎~
				CObjectX::Create("data\\MODEL\\corridor_block.x", pos);
				break;
			case 7://�o��
				CObjectX::Create("data\\MODEL\\corridor_ceiling.x", pos);
				CObjectX::Create("data\\MODEL\\corridor_floor.x", pos);
				CObjectX::Create("data\\MODEL\\gate.x", pos);
				pos.y += 150.0f;
				pos.x += 240.0f;
				
				CGate_UI::Create(pos);
				break;
			default:
				assert(false);
				break;
			}
		}
	}
	

	return S_OK;
}