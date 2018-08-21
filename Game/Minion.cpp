#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "Mediator.h"
#include <math.h>





//���������X�^�[�̃v���g�^�C�v�̏�����
void InitializePrototypeMinion(Minion proto_minion[]) {

	//�X���C��
	proto_minion[MINION_SLIME] =
	{
		MINION_SLIME,
		1,
		1,
		{ 0,0 },
		{ -32,-32,32,32 },
		{ 0,0 },
		TRUE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		12,
		0,
		32
	};

	//�S�[�X�g
	proto_minion[MINION_GHOST] =
	{
		MINION_GHOST,
		1,
		1,
		{ 0,0 },
		{ -32,-32,32,32 },
		{ 0,0 },
		TRUE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		66,
		0,
		64
	};
}


//�X���C���̍X�V
void UpdateMinionSlime(Minion *minion) {

}

//�S�[�X�g�̍X�V
void UpdateMinionGhost(Minion *minion) {

}

//�X���C���̕`��
void DrawMinionSlime(Minion *minion) {

}

//�S�[�X�g�̕`��
void DrawMinionGhost(Minion *minion) {

}

//�X���C���̃_���[�W����
void DamageMinionSlime(Minion *minion, int power) {

}

//�S�[�X�g�̃_���[�W����
void DamageMinionGhost(Minion *minion, int power) {

}

//�X���C���̏���
void DestroyMinionSlime(Minion *minion) {

}

//�S�[�X�g�̏���
void DestroyMinionGhost(Minion *minion) {

}



