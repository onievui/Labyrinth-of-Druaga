#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "Effect.h"
#include "Mediator.h"
#include "Sound.h"



//�萔�̒�`
#define EFFECT_MAX		(30)	//�G�t�F�N�g�̍ő�o����


//�v���g�^�C�v�錾
void DestroyEffect(int i);



//�O���[�o���ϐ��̐錾
Effect g_prototype_effect[EFFECT_PATTERN_NUM];	//�G�t�F�N�g�̃v���g�^�C�v
Effect g_effect[EFFECT_MAX];					//�G�t�F�N�g�I�u�W�F�N�g
int g_active_effect_num;						//�g�p���̃G�t�F�N�g�̐�



//�e�G�t�F�N�g�̍X�V�����̊֐��|�C���^
BOOL(*g_update_effect[EFFECT_PATTERN_NUM])(Effect *effect) = {
	UpdateEffectGetOrb
};

//�e�G�t�F�N�g�̕`�揈���̊֐��|�C���^
void(*g_draw_effect[EFFECT_PATTERN_NUM])(Effect *effect) = {
	DrawEffectGetOrb
};

//�e�G�t�F�N�g�̏��ŏ����̊֐��|�C���^
void(*g_destroy_effect[EFFECT_PATTERN_NUM])(Effect *effect) = {
	DestroyEffectGetOrb
};


//�G�t�F�N�g�̏�����
void InitializeEffects() {

	//�f�[�^�̏�����
	memset(g_effect, 0, sizeof(g_effect));

	//�G�t�F�N�g�̃v���g�^�C�v�̏�����
	InitializePrototypeEffect(g_prototype_effect);

	//�J�E���^�̃��Z�b�g
	g_active_effect_num = 0;
}

//�G�t�F�N�g�̐���
BOOL CreateEffect(EffectPattern knd, Vector2DF *pos, BOOL isLeft) {

	//�G���[�`�F�b�N
	if (knd < 0 || knd >= EFFECT_PATTERN_NUM) {
		MessageBox(NULL, "�G�t�F�N�g�̐����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//�����͌��ݖ��g�p
	isLeft = 0;

	//�G�t�F�N�g�̋󂫂����邩�ǂ���
	if (g_active_effect_num != EFFECT_MAX) {

		//�G�t�F�N�g�̏�����
		g_effect[g_active_effect_num] = g_prototype_effect[knd];
		g_effect[g_active_effect_num].pos = *pos;
		
		//�g�p���̐��𑝂₷
		g_active_effect_num++;

		return TRUE;
	}

	return FALSE;

}

//�G�t�F�N�g�̍X�V
void UpdateEffects() {
	int i;
	for (i = 0; i < g_active_effect_num; i++) {
		//�X�V����
		if (!g_update_effect[g_effect[i].knd](&g_effect[i])) {
			//���ł̒ʒm����������ł�����
			DestroyEffect(i);
		}
		//�}�b�v�O����
		else if (OrderIsOutsideMap(&g_effect[i].pos, &g_effect[i].col)) {
			DestroyEffect(i);
		}
	}
}

//�G�t�F�N�g�̕`��
void DrawEffects() {
	int i;
	for (i = 0; i < g_active_effect_num; i++) {
		g_draw_effect[g_effect[i].knd](&g_effect[i]);
	}
}

//�G�t�F�N�g�̏���
void DestroyEffect(int i) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_effect_num) {
		MessageBox(NULL, "�G�t�F�N�g�̏��łŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_destroy_effect[g_effect[i].knd](&g_effect[i]);

	//�G�t�F�N�g�I�u�W�F�N�g�̔z��Ɍ��Ԃ��ł������ǂ���
	if (g_active_effect_num != 1 && i != g_active_effect_num - 1) {
		//�󂢂��ꏊ�ƍŌ���̃G�t�F�N�g�����ւ���
		g_effect[i] = g_effect[g_active_effect_num - 1];
		g_effect[g_active_effect_num - 1].state = 0;
	}

	//�g�p���̐������炷
	g_active_effect_num--;

}
