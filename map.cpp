#include "map.h"
#include "manager.h"
#include "scene.h"


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
			D3DXVECTOR3 pos{ 250.0f*i,250.0f*j, 0 };
			switch (nMapID[i + j * c_nObjectX])
			{
			case -1://��
			case 0://��
				break;
			case 1://�v���C���[
				
				if (pPlayer != NULL)
				{
					pos.y -= c_fObjectMinSize;
					pPlayer->SetPos(pos);
				}
				else
				{
					assert(false);
				}
				break;
			case 2://�ʏ�u���b�N
				CObjectX::Create("data\\MODEL\\floor.x", pos);
				break;
			case 3://����
				
				break;
			case 4://�o��
			
				break;
			default:
				assert(false);
				break;
			}
		}
	}
	

	return S_OK;
}