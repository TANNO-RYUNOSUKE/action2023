//==================
//�}�b�v�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Map_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Map_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "objectX.h"
#include "scene.h"
#include "player.h"

class CMap
{
public:
	CMap();
	~CMap();


	static HRESULT Load(char * path,CPlayer * pPlayer);
private:

};

const float c_fObjectMinSize = 250.0f;
const int c_nObjectX = 17;
const int c_nObjectY = 10;

#endif // ! _Map_H_
