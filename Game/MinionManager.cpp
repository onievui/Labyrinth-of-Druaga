#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "Minion.h"
#include "Mediator.h"
#include "Fire.h"
#include "Sound.h"





//�v���g�^�C�v�錾
void DestroyMinion(int i);


//�O���[�o���ϐ��̐錾
Minion g_prototype_minion[MINION_PATTERN_NUM];	//���������X�^�[�̃v���g�^�C�v
Minion g_minion[MINION_MAX];					//���������X�^�[�I�u�W�F�N�g
SummonData g_summon_data[MINION_MAX];			//�����p�f�[�^
int g_active_minion_num;						//�g�p���̏��������X�^�[�̐�

//�e���������X�^�[�̍X�V�����̊֐��|�C���^
void(*g_update_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	UpdateMinionSlime,
	UpdateMinionGhost,
	UpdateMinionQuox
};

//�e���������X�^�[�̕`�揈���̊֐��|�C���^
void(*g_draw_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	DrawMinionSlime,
	DrawMinionGhost,
	DrawMinionQuox
};

//�e���������X�^�[�̃_���[�W�����̊֐��|�C���^
BOOL(*g_damage_minion[MINION_PATTERN_NUM])(Minion *minion, int power) = {
	DamageMinionSlime,
	DamageMinionGhost,
	DamageMinionQuox
};

//�e���������X�^�[�̏��ŏ����̊֐��|�C���^
void(*g_destroy_minion[MINION_PATTERN_NUM])(Minion *minion, SummonData *s_dat) = {
	DestroyMinionSlime,
	DestroyMinionGhost,
	DestroyMinionQuox
};


//���������X�^�[�̏�����
void InitializeMinions() {

	//�f�[�^�̏�����
	memset(g_minion, 0, sizeof(g_minion));
	memset(g_summon_data, 0, sizeof(g_summon_data));

	//���������X�^�[�̃v���g�^�C�v�̏�����
	InitializePrototypeMinion(g_prototype_minion,g_summon_data);

	//�J�E���^�̃��Z�b�g
	g_active_minion_num = 0;
}

//���������X�^�[�̐����E���Ŕ͈͏��̎擾
SummonAreaData GetSummonAreaData(MinionPattern knd, Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft) {

	SummonAreaData summon_area_data;

	//�G���[�`�F�b�N
	if (knd < 0 || knd > MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̐����ŕs���Ȓl���n����܂���", "", MB_OK);
		memset(&summon_area_data, 0, sizeof(summon_area_data));
		return summon_area_data;
	}

	//�������[�h�Ȃ�
	if (knd != MINION_PATTERN_NUM) {
		//�����X�y�[�X�̌v�Z
		Vector2DF s_pos = *pl_pos;
		int mx, my;
		s_pos.x += isLeft ? pl_col->left : pl_col->right;
		OrderGetMapPosWithPos(s_pos, &mx, &my);
		mx += isLeft ? -(int)g_summon_data[knd].offset.x : (int)g_summon_data[knd].offset.x;
		my += (int)g_summon_data[knd].offset.y;
		s_pos = OrderGetPosWithMapPos(mx, my);
		summon_area_data.pos = s_pos;
		summon_area_data.area = g_prototype_minion[knd].col;
		//�X�y�[�X���Ȃ��Ȃ疳���ɂ���
		if (OrderIsWallWithPos(s_pos.x, s_pos.y) ||
			OrderCollisionObjectMinions(&s_pos, &g_prototype_minion[knd].col) ||
			OrderCollisionObjectEnemies(&s_pos, &g_prototype_minion[knd].col)) {
			summon_area_data.is_available = FALSE;
			summon_area_data.state = 1;
		}
		//�X�y�[�X������Ȃ�L���ɂ���
		else {
			summon_area_data.is_available = TRUE;
			summon_area_data.state = 0;
		}
	}
	//���Ń��[�h�Ȃ�
	else {
		//�����X�y�[�X�̌v�Z
		Vector2DF pos = *pl_pos;
		RectF col = { -32,-32,32,32 };
		pos.x += isLeft ? pl_col->left - 32 : pl_col->right + 32;
		summon_area_data.pos = pos;
		summon_area_data.area = col;
		//�Ώۂ�����Ȃ�L���ɂ���
		if (OrderCollisionObjectMinions(&pos, &col)) {
			summon_area_data.is_available = TRUE;
			summon_area_data.state = 0;
		}
		//�Ώۂ��Ȃ��Ȃ疳���ɂ���
		else {
			summon_area_data.is_available = FALSE;
			summon_area_data.state = 1;
			//�G�Əd�Ȃ��Ă���Ƃ��͋�ʂ���
			if (OrderCollisionObjectEnemies(&pos, &col)) {
				summon_area_data.state = 2;
			}
		}
	}

	summon_area_data.knd = knd;
	summon_area_data.is_left = isLeft;

	return summon_area_data;
}

//���������X�^�[�̐���
int CreateMinion(SummonAreaData *summon_area_data) {

	//�G���[�`�F�b�N
	if (summon_area_data->knd < 0 || summon_area_data->knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̐����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//���������X�^�[�̋󂫂����邩�ǂ���
	if (g_active_minion_num != MINION_MAX) {
		//�͈͂������Ȃ玸�s
		if (!summon_area_data->is_available) {
			return FALSE;
		}
		
		//���������X�^�[�̏�����
		g_minion[g_active_minion_num] = g_prototype_minion[summon_area_data->knd];
		g_minion[g_active_minion_num].pos = summon_area_data->pos;
		g_minion[g_active_minion_num].is_left = summon_area_data->is_left;
		//�����ŉ摜���ς��ꍇ
		if (!summon_area_data->is_left && g_summon_data[summon_area_data->knd].turn_graph_num) {
			g_minion[g_active_minion_num].sprite_num += g_summon_data[summon_area_data->knd].turn_graph_num;
			//�X�v���C�g�̍Đݒ�
			if (summon_area_data->knd != MINION_QUOX) {
				g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_minion[g_active_minion_num].sprite_num);
			}
			else {
				g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_DRAGON, g_minion[g_active_minion_num].sprite_num);
			}
		}
		

		//�g�p���̐��𑝂₷
		g_active_minion_num++;

		//���ʉ���炷
		SetSE(SE_SUMMON);

		return g_summon_data[summon_area_data->knd].time;
	}
	
	return FALSE;
}

//���������X�^�[�̔z�u
BOOL SetMinion(MonsterList *minion) {

	//�G���[�`�F�b�N
	if (minion->knd < 0 || minion->knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̔z�u�ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//���������X�^�[�̋󂫂����邩�ǂ���
	if (g_active_minion_num != MINION_MAX) {
		
		//���������X�^�[�̏�����
		g_minion[g_active_minion_num] = g_prototype_minion[minion->knd];
		g_minion[g_active_minion_num].pos = minion->pos;
		g_minion[g_active_minion_num].is_left = minion->is_left;
		//�����ŉ摜���ς��ꍇ
		if (!minion->is_left && g_summon_data[minion->knd].turn_graph_num) {
			g_minion[g_active_minion_num].sprite_num += g_summon_data[minion->knd].turn_graph_num;
			//�X�v���C�g�̍Đݒ�
			if (minion->knd != MINION_QUOX) {
				g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_minion[g_active_minion_num].sprite_num);
			}
			else {
				g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_DRAGON, g_minion[g_active_minion_num].sprite_num);
			}
		}


		//�g�p���̐��𑝂₷
		g_active_minion_num++;

		return TRUE;
	}

	return FALSE;
}

//���������X�^�[������
void DeleteMinion(SummonAreaData *summon_area_data) {

	//�͈͂��L���Ȃ珈�����s��
	if (summon_area_data->is_available) {
		//���������X�^�[�Ƃ̓����蔻��
		OrderCollisionDeleteObjectMinions(&summon_area_data->pos, &summon_area_data->area);
	}
}

//�����R�X�g�̎擾
int GetSummonCost(MinionPattern knd) {

	//�G���[�`�F�b�N
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̃R�X�g�擾�ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	return g_summon_data[knd].cost;
}

//���������X�^�[�̉摜�擾
Sprite GetMinionSprite(MinionPattern knd) {

	//�G���[�`�F�b�N
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̉摜�擾�ŕs���Ȓl���n����܂���", "", MB_OK);
		return g_sprite[SPR_STD_MONSTER];
	}

	return g_prototype_minion[knd].graph.sprite;
}

//���������X�^�[�̍X�V
void UpdateMinions() {
	int i;
	for (i = 0; i < g_active_minion_num; i++) {
		//�X�V����
		g_update_minion[g_minion[i].knd](&g_minion[i]);
		//�}�b�v�O����
		if (OrderIsOutsideMap(&g_minion[i].pos, &g_minion[i].col)) {
			DestroyMinion(i);
		}
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
void SetMinionsCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < MINION_MAX; i++) {
		collider[i].state = &g_minion[i].state;
		collider[i].pos = &g_minion[i].pos;
		collider[i].col = &g_minion[i].col;
		collider[i].vel = &g_minion[i].vel;
		collider[i].ride = &g_minion[i].ride;
		collider[i].collision_state = &g_minion[i].collision_state;
		collider[i].ground_flag = &g_minion[i].ground_flag;
	}
}

//���������X�^�[�̃_���[�W����
BOOL DamageMinion(int i, int power) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_minion_num) {
		MessageBox(NULL, "���������X�^�[�̃_���[�W�����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//�̗͂�0�Ȃ���ł�����
	if (g_damage_minion[g_minion[i].knd](&g_minion[i], power)) {
		DestroyMinion(i);
		return TRUE;
	}
	return FALSE;
}

//���������X�^�[�̏���
void DestroyMinion(int i) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_minion_num) {
		MessageBox(NULL, "���������X�^�[�̏��łŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_destroy_minion[g_minion[i].knd](&g_minion[i], &g_summon_data[g_minion[i].knd]);

	//���������X�^�[�I�u�W�F�N�g�̔z��Ɍ��Ԃ��ł������ǂ���
	if (g_active_minion_num != 1 && i != g_active_minion_num - 1) {
		//�󂢂��ꏊ�ƍŌ���̏��������X�^�[�����ւ���
		g_minion[i] = g_minion[g_active_minion_num - 1];
		g_minion[g_active_minion_num - 1].state = 0;
		//����ւ����I�u�W�F�N�g���h���S���Ȃ�q�I�u�W�F�N�g�ɒʒm����
		if (g_minion[i].knd == MINION_QUOX) {
			ChangeFireParentPt(&g_minion[g_active_minion_num - 1], &g_minion[i]);
		}
	}

	//�g�p���̐������炷
	g_active_minion_num--;

}


