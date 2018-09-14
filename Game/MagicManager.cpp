#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "Magic.h"
#include "Mediator.h"






//�v���g�^�C�v�錾
void DestroyMagic(int i);


//�O���[�o���ϐ��̐錾
Magic g_prototype_magic[MAGIC_PATTERN_NUM];	//�G�̖��@�̃v���g�^�C�v
Magic g_magic[MAGIC_MAX];					//�G�̖��@�I�u�W�F�N�g
int g_active_magic_num;						//�g�p���̓G�̖��@�̐�


//�e�G�̖��@�̍X�V�����̊֐��|�C���^
void(*g_update_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	UpdateMagicWhite,
	UpdateMagicGreen
};

//�e�G�̖��@�̕`�揈���̊֐��|�C���^
void(*g_draw_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	DrawMagicWhite,
	DrawMagicGreen
};

//�e�G�̖��@�̕ǏՓˏ����̊֐��|�C���^
BOOL(*g_collision_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	CollisionMagicWhite,
	CollisionMagicGreen
};

//�e�G�̖��@�̏��ŏ����̊֐��|�C���^
void(*g_destroy_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	DestroyMagicWhite,
	DestroyMagicGreen
};


//�G�̖��@�̏�����
void InitializeMagics() {

	//�f�[�^�̏�����
	memset(g_magic, 0, sizeof(g_magic));

	//�G�̖��@�̃v���g�^�C�v�̏�����
	InitializePrototypeMagic(g_prototype_magic);

	//�J�E���^�̃��Z�b�g
	g_active_magic_num = 0;
}


//�G�̖��@�̐���
BOOL CreateMagic(MagicPattern knd, Vector2DF *pos, BOOL isLeft) {

	//�G���[�`�F�b�N
	if (knd < 0 || knd >= MAGIC_PATTERN_NUM) {
		MessageBox(NULL, "�G�̖��@�̐����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//�G�̖��@�̋󂫂����邩�ǂ���
	if (g_active_magic_num != MAGIC_MAX) {

		//�G�̖��@�̏�����
		g_magic[g_active_magic_num] = g_prototype_magic[knd];
		g_magic[g_active_magic_num].pos = *pos;
		//�����ňړ�������ς���
		if (isLeft) {
			g_magic[g_active_magic_num].vel.x *= -1;
		}

		//�g�p���̐��𑝂₷
		g_active_magic_num++;

		return TRUE;
	}

	return FALSE;
	
}

//�G�̖��@�̍X�V
void UpdateMagics() {
	int i;
	for (i = 0; i < g_active_magic_num; i++) {
		//�X�V����
		g_update_magic[g_magic[i].knd](&g_magic[i]);
		//�}�b�v�O����
		if (OrderIsOutsideMap(&g_magic[i].pos, &g_magic[i].col)) {
			DestroyMagic(i);
		}
	}
}

//�G�̖��@�̕`��
void DrawMagics() {
	int i;
	for (i = 0; i < g_active_magic_num; i++) {
		g_draw_magic[g_magic[i].knd](&g_magic[i]);
	}
}

//�G�̖��@�̓����蔻��̐ݒ�
void SetMagicsCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < MAGIC_MAX; i++) {
		collider[i].state = &g_magic[i].state;
		collider[i].pos = &g_magic[i].pos;
		collider[i].col = &g_magic[i].col;
		collider[i].vel = &g_magic[i].vel;
		collider[i].ride = NULL;
		collider[i].collision_state = NULL;
		collider[i].ground_flag = NULL;
	}
}

//�G�̖��@�̕ǏՓˏ���
BOOL CollisionMagic(int i) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_magic_num) {
		MessageBox(NULL, "�G�̖��@�̃_���[�W�����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//������Ȃ�ʒm����
	if (g_collision_magic[g_magic[i].knd](&g_magic[i])) {
		DestroyMagic(i);
		return TRUE;
	}
	return FALSE;
}

//�G�̖��@�̏���
void DestroyMagic(int i) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_magic_num) {
		MessageBox(NULL, "�G�̖��@�̏��łŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_destroy_magic[g_magic[i].knd](&g_magic[i]);

	//�G�̖��@�I�u�W�F�N�g�̔z��Ɍ��Ԃ��ł������ǂ���
	if (g_active_magic_num != 1 && i != g_active_magic_num - 1) {
		//�󂢂��ꏊ�ƍŌ���̓G�̖��@�����ւ���
		g_magic[i] = g_magic[g_active_magic_num - 1];
		g_magic[g_active_magic_num - 1].state = 0;
	}

	//�g�p���̐������炷
	g_active_magic_num--;

}

//�G�̖��@�̃_���[�W�ʂ̎擾
int GetMagicPower(int i) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_magic_num) {
		MessageBox(NULL, "�G�̖��@�̃_���[�W�ʂ̎擾�ŕs���Ȓl���n����܂���", "", MB_OK);
		return 0;
	}

	return g_magic[i].power;
}

