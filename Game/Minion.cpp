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
		{ -21,-12,21,12 },
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

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(minion->pos, minion->vel);

	//�d�͂�������
	minion->vel.y += GRAVITY;

	//�}�b�v�Ƃ̓����蔻��
	OrderCollisionObjectMap(&minion->pos, &minion->vel, &minion->col);
	
}

//�S�[�X�g�̍X�V
void UpdateMinionGhost(Minion *minion) {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(minion->pos, minion->vel);

	//�}�b�v�Ƃ̓����蔻��
	OrderCollisionObjectMap(&minion->pos, &minion->vel, &minion->col);
}

//�X���C���̕`��
void DrawMinionSlime(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	/*Vector2DF pos = minion->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + minion->col.left,
	pos.y + minion->col.top,
	pos.x + minion->col.right,
	pos.y + minion->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);*/
}

//�S�[�X�g�̕`��
void DrawMinionGhost(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
}

//�X���C���̃_���[�W����
BOOL DamageMinionSlime(Minion *minion, int power) {
	minion->hp -= power;
	//�̗͂�0�Ȃ�ʒm����
	if (minion->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//�S�[�X�g�̃_���[�W����
BOOL DamageMinionGhost(Minion *minion, int power) {
	minion->hp -= power;
	//�̗͂�0�Ȃ�ʒm����
	if (minion->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//�X���C���̏���
void DestroyMinionSlime(Minion *minion) {
	minion->state = 0;
}

//�S�[�X�g�̏���
void DestroyMinionGhost(Minion *minion) {
	minion->state = 0;
}



