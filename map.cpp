#include "map.h"
#include "manager.h"
#include "scene.h"


#include <stdio.h>
#include <assert.h>
//====================================-----
//マップローダー

CMap::CMap()
{
}

CMap::~CMap()
{
}


HRESULT CMap::Load(char * path, CPlayer * pPlayer)
{

	//変数宣言
	int nMapID[c_nObjectX * c_nObjectY] = {};
	int nCount = 0;;
	//ファイルポインタ宣言
	FILE *pFile;

	//ファイルを開く
	pFile = fopen(path, "r");
	//ファイルを読み込み
	if (pFile != NULL)
	{//ファイルが開けたなら
	
	 //ファイルに読み込み
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
	//ファイルを閉じる
	fclose(pFile);

	for (int i = 0; i < c_nObjectX ; i++)
	{
		for (int j = 0; j < c_nObjectY; j++)
		{
			D3DXVECTOR3 pos{ 250.0f*i,250.0f*j, 0 };
			switch (nMapID[i + j * c_nObjectX])
			{
			case -1://空白
			case 0://空白
				break;
			case 1://プレイヤー
				
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
			case 2://通常ブロック
				CObjectX::Create("data\\MODEL\\floor.x", pos);
				break;
			case 3://入口
				
				break;
			case 4://出口
			
				break;
			default:
				assert(false);
				break;
			}
		}
	}
	

	return S_OK;
}