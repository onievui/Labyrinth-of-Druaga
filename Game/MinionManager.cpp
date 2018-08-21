#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "Minion.h"



//�O���[�o���ϐ��̐錾
Minion g_prototype_minion[MINION_PATTERN_NUM];	//���������X�^�[�̃v���g�^�C�v
Minion g_minion[MINION_MAX];					//���������X�^�[�I�u�W�F�N�g
int g_active_minion_num;						//�g�p���̏��������X�^�[�̐�

//�e���������X�^�[�̍X�V�����̊֐��|�C���^
void(*g_update_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	UpdateMinionSlime,
	UpdateMinionGhost
};

//�e���������X�^�[�̕`�揈���̊֐��|�C���^
void(*g_draw_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	DrawMinionSlime,
	DrawMinionGhost
};

//�e���������X�^�[�̃_���[�W�����̊֐��|�C���^
void(*g_damage_minion[MINION_PATTERN_NUM])(Minion *minion, int power) = {
	DamageMinionSlime,
	DamageMinionGhost
};

//�e���������X�^�[�̏��ŏ����̊֐��|�C���^
void(*g_destroy_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	DestroyMinionSlime,
	DestroyMinionGhost
};




//���������X�^�[�̏�����
void InitializeMinions() {

	//���������X�^�[�I�u�W�F�N�g�̏�����
	memset(g_minion, 0, sizeof(g_minion));

	//���������X�^�[�̃v���g�^�C�v�̏�����
	InitializePrototypeMinion(g_prototype_minion);

	//�J�E���^�̃��Z�b�g
	g_active_minion_num = 0;
}

//���������X�^�[�̐���
int CreateMinion(MinionPattern knd, Vector2DF pos, BOOL isLeft) {

	//�G���[�`�F�b�N
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̐����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//���������X�^�[�̋󂫂����邩�ǂ���
	if (g_active_minion_num != MINION_MAX) {
		//���������X�^�[�̏�����
		g_minion[g_active_minion_num] = g_prototype_minion[knd];
		g_minion[g_active_minion_num].pos = pos;
		g_minion[g_active_minion_num].is_left = isLeft;
		if (!isLeft && knd == MINION_GHOST) {
			g_minion[g_active_minion_num].sprite_num++;
		}
		//�X�v���C�g�̐ݒ�
		g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_minion[g_active_minion_num].sprite_num);

		//�g�p���̐��𑝂₷
		g_active_minion_num++;

		return g_minion[g_active_minion_num].summon_time;
	}
	
	return FALSE;
}

//���������X�^�[�̍X�V
void UpdateMinions() {
	int i;
	for (i = 0; i < g_active_minion_num; i++) {
		g_update_minion[g_minion[i].knd](&g_minion[i]);
	}
}

//���������X�^�[�̕`��
void DrawMinions() {
	int i;
	for (i = 0; i < g_active_minion_num; i++) {
		g_draw_minion[g_minion[i].knd](&g_minion[i]);
	}
}

//���������X�^�[�̓����蔻��̐ݒ�
void SetEnemysCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < MINION_MAX; i++) {
		collider->state = &g_minion[i].state;
		collider->pos = &g_minion[i].pos;
		collider->vel = &g_minion[i].vel;
		collider->col = &g_minion[i].col;
	}
}

//���������X�^�[�̃_���[�W����
void DamageMinion(int i, int power) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_minion_num) {
		MessageBox(NULL, "���������X�^�[�̃_���[�W�����ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_damage_minion[g_minion[i].knd](&g_minion[i], power);

}

//���������X�^�[�̏���
void DestroyMinion(int i) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_minion_num) {
		MessageBox(NULL, "���������X�^�[�̏��łŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_destroy_minion[g_minion[i].knd](&g_minion[i]);

	//���������X�^�[�I�u�W�F�N�g�̔z��Ɍ��Ԃ��ł������ǂ���
	if (g_active_minion_num != 1 && i != g_active_minion_num - 1) {
		//�󂢂��ꏊ�ƍŌ���̏��������X�^�[�����ւ���
		g_minion[i] = g_minion[g_active_minion_num - 1];
		g_minion[g_active_minion_num - 1].state = 0;
	}

	//�g�p���̐������炷
	g_active_minion_num--;

}


