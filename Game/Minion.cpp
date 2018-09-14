#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "Mediator.h"
#include "Fire.h"


//�萔�̒�`
#define GHOST_SPEED		(3)		//�S�[�X�g�̈ړ����x



//���������X�^�[�̃v���g�^�C�v�̏�����
void InitializePrototypeMinion(Minion proto_minion[], SummonData s_data[]) {

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
		0
	};
	s_data[MINION_SLIME] =
	{
		1,
		32,
		{1,0},
		FALSE
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
		0
	};
	s_data[MINION_GHOST] =
	{
		3,
		64,
		{ 1,0 },
		1
	};
	proto_minion[MINION_GHOST].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_minion[MINION_GHOST].sprite_num);

	//�N�I�b�N�X
	proto_minion[MINION_QUOX] =
	{
		MINION_QUOX,
		1,
		5,
		{ 0,0 },
		{ -31,-26,31,32 },//{ -25,-15,25,32 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_DRAGON],1.0,0.0 },
		5,
		0,
	};
	s_data[MINION_QUOX] =
	{
		5,
		64,
		{ 1,0 },
		3
	};
	proto_minion[MINION_QUOX].graph.sprite.rect = GetSpriteRect(SPR_STD_DRAGON, proto_minion[MINION_QUOX].sprite_num);
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
	if (minion->ground_flag) {
		//���n���Ă��锻��ɂ���
		minion->collision_state |= ISGROUND;
		//���x��0�ɂ���
		minion->vel.y = 0;
	}
	else {
		//���n���Ă��Ȃ�����ɖ߂�
		minion->collision_state &= ~ISGROUND;
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

//�N�I�b�N�X�̍X�V
void UpdateMinionQuox(Minion *minion) {



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

	//60�t���[���o�߂�����130�t���[��1�񉊂�f��
	if (minion->anime_count % 130 == 60) {
		//���𐶐�����
		CreateFire(minion);
		//����f���o���Ă���摜�ɕύX����
		minion->sprite_num = 26 + !minion->is_left;
		minion->graph.sprite.rect = GetSpriteRect(SPR_STD_DRAGON, minion->sprite_num);
	}


	//�}�b�v�Ƃ̒��n����̓K�p
	if (minion->ground_flag) {
		//���n���Ă��锻��ɂ���
		minion->collision_state |= ISGROUND;
		//���x��0�ɂ���
		minion->vel.y = 0;
	}
	else {
		//���n���Ă��Ȃ�����ɖ߂�
		minion->collision_state &= ~ISGROUND;
		//�d�͂�������
		minion->vel.y += GRAVITY;
	}

	//����Ă���I�u�W�F�N�g�̑��x��������
	if (minion->ride) {
		AddVector2DF(minion->vel, *minion->ride);
	}

	minion->anime_count++;

}

//�X���C���̕`��
void DrawMinionSlime(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	
}

//�S�[�X�g�̕`��
void DrawMinionGhost(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
}

//�N�I�b�N�X�̕`��
void DrawMinionQuox(Minion *minion) {
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

//�N�I�b�N�X�̃_���[�W����
BOOL DamageMinionQuox(Minion *minion, int power) {
	minion->hp -= power;
	//�̗͂�0�Ȃ�ʒm����
	if (minion->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//�X���C���̏���
void DestroyMinionSlime(Minion *minion, SummonData *s_dat) {
	minion->state = 0;
	OrderAddPlayerSp(s_dat->cost);
}

//�S�[�X�g�̏���
void DestroyMinionGhost(Minion *minion, SummonData *s_dat) {
	minion->state = 0;
	OrderAddPlayerSp(s_dat->cost);
}

//�N�I�b�N�X�̏���
void DestroyMinionQuox(Minion *minion, SummonData *s_dat) {
	minion->state = 0;
	OrderAddPlayerSp(s_dat->cost);
	//�q�I�u�W�F�N�g�̉�������
	DestroyFire(minion);
}



