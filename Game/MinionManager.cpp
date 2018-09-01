#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "Minion.h"
#include "Mediator.h"






//�v���g�^�C�v�錾
void DestroyMinion(int i);


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
BOOL(*g_damage_minion[MINION_PATTERN_NUM])(Minion *minion, int power) = {
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
int CreateMinion(MinionPattern knd, Vector2DF pl_pos, RectF pl_col, BOOL isLeft) {

	//�G���[�`�F�b�N
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̐����ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	//���������X�^�[�̋󂫂����邩�ǂ���
	if (g_active_minion_num != MINION_MAX) {
		//�����X�y�[�X�����邩�ǂ���
		Vector2DF s_pos = pl_pos;
		int mx, my;
		s_pos.x += isLeft ? pl_col.left : pl_col.right;
		OrderGetMapPosWithPos(s_pos, &mx, &my);
		mx += isLeft ? -1 : 1;
		s_pos = OrderGetPosWithMapPos(mx, my);
		if (OrderIsWallWithPos(s_pos.x, s_pos.y)) {
			//�X�y�[�X���Ȃ��Ȃ玸�s
			return FALSE;
		}
		
		//���������X�^�[�̏�����
		g_minion[g_active_minion_num] = g_prototype_minion[knd];
		g_minion[g_active_minion_num].pos = s_pos;
		g_minion[g_active_minion_num].is_left = isLeft;
		//�����ŉ摜���ς��ꍇ
		if (!isLeft && knd == MINION_GHOST) {
			g_minion[g_active_minion_num].sprite_num++;
			//�X�v���C�g�̍Đݒ�
			g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_minion[g_active_minion_num].sprite_num);
		}
		

		//�g�p���̐��𑝂₷
		g_active_minion_num++;

		return g_prototype_minion[knd].s_dat.time;
	}
	
	return FALSE;
}

//���������X�^�[������
void DeleteMinion(Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft) {

	//�����͈͂̍쐬
	Vector2DF pos = *pl_pos;
	RectF col = { -32,-32,32,32 };
	pos.x += isLeft ? pl_col->left - 32: pl_col->right + 32;

	//�G�Ƃ̓����蔻��
	OrderCollisionObjectMinions(&pos, &col);

}

//�����R�X�g�̎擾
int GetSummonCost(MinionPattern knd) {

	//�G���[�`�F�b�N
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "���������X�^�[�̃R�X�g�擾�ŕs���Ȓl���n����܂���", "", MB_OK);
		return FALSE;
	}

	return g_prototype_minion[knd].s_dat.cost;
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
		collider[i].is_ground = &g_minion[i].is_ground;
		collider[i].ground_flag = &g_minion[i].ground_flag;
	}
}

//���������X�^�[�̃_���[�W����
void DamageMinion(int i, int power) {

	//�G���[�`�F�b�N
	if (i < 0 || i >= g_active_minion_num) {
		MessageBox(NULL, "���������X�^�[�̃_���[�W�����ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	//�̗͂�0�Ȃ���ł�����
	if (g_damage_minion[g_minion[i].knd](&g_minion[i], power)) {
		DestroyMinion(i);
	}

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


