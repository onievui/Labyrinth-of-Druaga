#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "Enemy.h"
#include "Mediator.h"






//�v���g�^�C�v�錾
void DestroyEnemy(int i);


//�O���[�o���ϐ��̐錾
Enemy g_prototype_enemy[ENEMY_PATTERN_NUM];	//�G�����X�^�[�̃v���g�^�C�v
Enemy g_enemy[ENEMY_MAX];					//�G�����X�^�[�I�u�W�F�N�g
int g_active_enemy_num;						//�g�p���̓G�����X�^�[�̐�


//�e�G�����X�^�[�̍X�V�����̊֐��|�C���^
void(*g_update_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy) = {
	UpdateEnemyDruid,
	UpdateEnemyWizard
};

//�e�G�����X�^�[�̕`�揈���̊֐��|�C���^
void(*g_draw_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy) = {
	DrawEnemyDruid,
	DrawEnemyWizard
};

//�e�G�����X�^�[�̃_���[�W�����̊֐��|�C���^
BOOL(*g_damage_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy, int power) = {
	DamageEnemyDruid,
	DamageEnemyWizard
};

//�e�G�����X�^�[�̏��ŏ����̊֐��|�C���^
void(*g_destroy_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy) = {
	DestroyEnemyDruid,
	DestroyEnemyWizard
};


//�G�����X�^�[�̏�����
void InitializeEnemies() {

	//�f�[�^�̏�����
	memset(g_enemy, 0, sizeof(g_enemy));

	//�G�����X�^�[�̃v���g�^�C�v�̏�����
	InitializePrototypeEnemy(g_prototype_enemy);

	//�J�E���^�̃��Z�b�g
	g_active_enemy_num = 0;
}


//�G�����X�^�[�̐���
BOOL CreateEnemies(EnemyList enemy_list[]) {

	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		//�g���邩�ǂ���
		if (enemy_list[i].is_use) {
			//�G���[�`�F�b�N
			if (enemy_list[i].knd < 0 || enemy_list[i].knd >= ENEMY_PATTERN_NUM) {
				MessageBox(NULL, "�G�����X�^�[�̐����ŕs���Ȓl���n����܂���", "", MB_OK);
				return FALSE;
			}
			//�G�����X�^�[�̏�����
			g_enemy[i] = g_prototype_enemy[enemy_list[i].knd];
			g_enemy[i].knd = enemy_list[i].knd;
			g_enemy[i].pos = enemy_list[i].pos;
			//�����ŉ摜���ς��ꍇ
			if (!(g_enemy[i].is_left = enemy_list[i].is_left)) {
				g_enemy[i].sprite_num++;
				//�X�v���C�g�̍Đݒ�
				g_enemy[i].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_enemy[i].sprite_num);
			}
			//�g�p���̐��𑝂₷
			g_active_enemy_num++;
		}
		//���X�g�̏I���Ȃ珈���𔲂���
		else {
			break;
		}
	}

	return TRUE;
}

//�G�����X�^�[�̍X�V
void UpdateEnemies() {
	int i;
	for (i = 0; i < g_active_enemy_num; i++) {
		//�X�V����
		g_update_enemy[g_enemy[i].knd](&g_enemy[i]);
		//�}�b�v�O����
		if (OrderIsOutsideMap(&g_enemy[i].pos, &g_enemy[i].col)) {
			DestroyEnemy(i);
		}
	}
}

//�G�����X�^�[�̕`��
void DrawEnemies() {
	int i;
	for (i = 0; i < g_active_enemy_num; i++) {
		g_draw_enemy[g_enemy[i].knd](&g_enemy[i]);
	}
}

//�G�����X�^�[�̓����蔻��̐ݒ�
void SetEnemiesCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		collider[i].state = &g_enemy[i].state;
		collider[i].pos = &g_enemy[i].pos;
		collider[i].col = &g_enemy[i].col;
		collider[i].vel = &g_enemy[i].vel;
		collider[i].ride = &g_enemy[i].ride;
		collider[i].collision_state = &g_enemy[i].collision_state;
		collider[i].ground_flag = &g_enemy[i].ground_flag;
	}
}

//�G�����X�^�[�̃_���[�W����
BOOL DamageEnemy(int i, int power) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_enemy_num) {
		MessageBox(NULL, "�G�����X�^�[�̃_���[�W�����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//�̗͂�0�Ȃ���ł�����
	if (g_damage_enemy[g_enemy[i].knd](&g_enemy[i], power)) {
		DestroyEnemy(i);
		return TRUE;
	}
	return FALSE;
}

//�G�����X�^�[�̏���
void DestroyEnemy(int i) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_enemy_num) {
		MessageBox(NULL, "�G�����X�^�[�̏��łŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_destroy_enemy[g_enemy[i].knd](&g_enemy[i]);

	//�G�����X�^�[�I�u�W�F�N�g�̔z��Ɍ��Ԃ��ł������ǂ���
	if (g_active_enemy_num != 1 && i != g_active_enemy_num - 1) {
		//�󂢂��ꏊ�ƍŌ���̓G�����X�^�[�����ւ���
		g_enemy[i] = g_enemy[g_active_enemy_num - 1];
		g_enemy[g_active_enemy_num - 1].state = 0;
	}

	//�g�p���̐������炷
	g_active_enemy_num--;

}


