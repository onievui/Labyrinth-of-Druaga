#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "MagicManager.h"
#include "Sound.h"


//�萔�̒�`



//�G�����X�^�[�̃v���g�^�C�v�̏�����
void InitializePrototypeEnemy(Enemy proto_enemy[]) {

	//�h���C�h
	proto_enemy[ENEMY_DRUID] =
	{
		ENEMY_DRUID,
		1,
		0,
		1,
		{ 0,0 },
		{ -18,-30,18,30 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		46,
		0
	};
	proto_enemy[ENEMY_DRUID].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_enemy[ENEMY_DRUID].sprite_num);

	//�E�B�U�[�h
	proto_enemy[ENEMY_WIZARD] =
	{
		ENEMY_WIZARD,
		1,
		0,
		1,
		{ 0,0 },
		{ -18,-30,18,30 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		50,
		0
	};
	proto_enemy[ENEMY_WIZARD].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_enemy[ENEMY_WIZARD].sprite_num);
	
}


//�h���C�h�̍X�V
void UpdateEnemyDruid(Enemy *enemy) {



	//�ړ��ʂ����W�ɑ���
	AddVector2DF(enemy->pos, enemy->vel);

	//���n���Ă����Ȃ瑬�x��0�ɂ���
	if ((enemy->collision_state & ISGROUND) && enemy->vel.y > 0) {
		enemy->vel.y = 0;
	}
	//�㏸���Ă�����n�ʂ��痣�ꂽ�Ƃ݂Ȃ�
	else if (enemy->vel.y > 0) {
		enemy->ground_flag = FALSE;
	}

	//�������̑��x�����Z�b�g����
	enemy->vel.x = 0;

	//60�t���[����1�񔒖��@�������o��
	if (enemy->count % 60 == 59) {
		CreateMagic(MAGIC_WHITE, &enemy->pos, enemy->is_left);
	}

	//�}�b�v�Ƃ̒��n����̓K�p
	if (enemy->ground_flag) {
		//���n���Ă��锻��ɂ���
		enemy->collision_state |= ISGROUND;
		//���x��0�ɂ���
		enemy->vel.y = 0;
	}
	else {
		//���n���Ă��Ȃ�����ɖ߂�
		enemy->collision_state &= ~ISGROUND;
		//�d�͂�������
		enemy->vel.y += GRAVITY;
	}

	//����Ă���I�u�W�F�N�g�̑��x��������
	if (enemy->ride) {
		AddVector2DF(enemy->vel, *enemy->ride);
	}


	enemy->count++;

}

//�E�B�U�[�h�̍X�V
void UpdateEnemyWizard(Enemy *enemy) {



	//�ړ��ʂ����W�ɑ���
	AddVector2DF(enemy->pos, enemy->vel);

	//���n���Ă����Ȃ瑬�x��0�ɂ���
	if ((enemy->collision_state & ISGROUND) && enemy->vel.y > 0) {
		enemy->vel.y = 0;
	}
	//�㏸���Ă�����n�ʂ��痣�ꂽ�Ƃ݂Ȃ�
	else if (enemy->vel.y > 0) {
		enemy->ground_flag = FALSE;
	}

	//�������̑��x�����Z�b�g����
	enemy->vel.x = 0;

	//60�t���[����1��Ζ��@�������o��
	if (enemy->count % 60 == 59) {
		CreateMagic(MAGIC_GREEN, &enemy->pos, enemy->is_left);
	}

	//�}�b�v�Ƃ̒��n����̓K�p
	if (enemy->ground_flag) {
		//���n���Ă��锻��ɂ���
		enemy->collision_state |= ISGROUND;
		//���x��0�ɂ���
		enemy->vel.y = 0;
	}
	else {
		//���n���Ă��Ȃ�����ɖ߂�
		enemy->collision_state &= ~ISGROUND;
		//�d�͂�������
		enemy->vel.y += GRAVITY;
	}

	//����Ă���I�u�W�F�N�g�̑��x��������
	if (enemy->ride) {
		AddVector2DF(enemy->vel, *enemy->ride);
	}


	enemy->count++;

}

//�h���C�h�̕`��
void DrawEnemyDruid(Enemy *enemy) {
	DrawGraphicToMap(enemy->pos, &enemy->graph);
	/*Vector2DF pos = enemy->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + enemy->col.left,
	pos.y + enemy->col.top,
	pos.x + enemy->col.right,
	pos.y + enemy->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_BLUE, 0);*/
}

//�E�B�U�[�h�̕`��
void DrawEnemyWizard(Enemy *enemy) {
	DrawGraphicToMap(enemy->pos, &enemy->graph);
}

//�h���C�h�̃_���[�W����
BOOL DamageEnemyDruid(Enemy *enemy, int power) {
	enemy->hp -= power;
	//�̗͂�0�Ȃ�ʒm����
	if (enemy->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//�E�B�U�[�h�̃_���[�W����
BOOL DamageEnemyWizard(Enemy *enemy, int power) {
	enemy->hp -= power;
	//�̗͂�0�Ȃ�ʒm����
	if (enemy->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//�h���C�h�̏���
void DestroyEnemyDruid(Enemy *enemy) {
	enemy->state = 0;
	SetSE(SE_ENEMY_STRIKE);
}

//�E�B�U�[�h�̏���
void DestroyEnemyWizard(Enemy *enemy) {
	enemy->state = 0;
	SetSE(SE_ENEMY_STRIKE);
}




