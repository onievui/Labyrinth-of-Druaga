#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "Mediator.h"
#include <math.h>


//�萔�̒�`
#define GHOST_SPEED		(3)		//�S�[�X�g�̈ړ����x



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
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		12,
		0,
		{ 1,32 }
	};
	proto_minion[MINION_SLIME].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_minion[MINION_SLIME].sprite_num);

	//�S�[�X�g
	proto_minion[MINION_GHOST] =
	{
		MINION_GHOST,
		1,
		1,
		{ 0,0 },
		{ -29,-29,29,25 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		66,
		0,
		{ 3,64 }
	};
	proto_minion[MINION_GHOST].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_minion[MINION_GHOST].sprite_num);
}


//�X���C���̍X�V
void UpdateMinionSlime(Minion *minion) {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(minion->pos, minion->vel);

	//���n���Ă����Ȃ瑬�x��0�ɂ���
	if ((minion->collision_state & ISGROUND) && minion->vel.y > 0) {
		minion->vel.y = 0;
	}
	//�㏸���Ă�����n�ʂ��痣�ꂽ�Ƃ݂Ȃ�
	else if (minion->vel.y > 0) {
		minion->ground_flag = FALSE;
	}

	//�������̑��x�����Z�b�g����
	minion->vel.x = 0;
	
	//�}�b�v�Ƃ̒��n����̓K�p
	if ((minion->collision_state |= minion->ground_flag*ISGROUND) & ISGROUND) {
		minion->vel.y = 0;
	}
	else {
		//�d�͂�������
		minion->vel.y += GRAVITY;
	}

	//����Ă���I�u�W�F�N�g�̑��x��������
	if (minion->ride) {
		AddVector2DF(minion->vel, *minion->ride);
	}

}

//�S�[�X�g�̍X�V
void UpdateMinionGhost(Minion *minion) {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(minion->pos, minion->vel);

	//�ړ�����
	if (minion->is_left) {
		minion->vel.x = -GHOST_SPEED;
	}
	else {
		minion->vel.x = GHOST_SPEED;
	}

	//�}�b�v�Ƃ̓����蔻��
	if (minion->is_left && (minion->collision_state & ISLEFT)) {
		minion->is_left = !minion->is_left;
		minion->sprite_num++;
		minion->graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, minion->sprite_num);
		minion->collision_state -= ISLEFT;
	}
	else if (!minion->is_left && (minion->collision_state & ISRIGHT)) {
		minion->is_left = !minion->is_left;
		minion->sprite_num--;
		minion->graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, minion->sprite_num);
		minion->collision_state -= ISRIGHT;
	}
}

//�X���C���̕`��
void DrawMinionSlime(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	
}

//�S�[�X�g�̕`��
void DrawMinionGhost(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	/*Vector2DF pos = minion->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + minion->col.left,
	pos.y + minion->col.top,
	pos.x + minion->col.right,
	pos.y + minion->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);*/
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
	OrderAddPlayerSp(minion->s_dat.cost);
}

//�S�[�X�g�̏���
void DestroyMinionGhost(Minion *minion) {
	minion->state = 0;
	OrderAddPlayerSp(minion->s_dat.cost);
}



