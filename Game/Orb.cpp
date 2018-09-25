#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "Mediator.h"
#include "Sound.h"
#include <math.h>



//�萔�̒�`
#define ORB_SPAWNER_MAX				(8)		//�I�[�u�X�|�i�[�̍ő�o����
#define ORB_SPAWNER_SPEED			(6)		//�I�[�u�̐����Ԋu

#define ORB_APPEAR_ROTATE_SPEED		(8)		//�I�[�u�̏o���������̉�]�Ԋu
#define ORB_MOVE_ROTATE_SPEED		(5)		//�I�[�u�̒ǔ����̉�]�Ԋu

#define ORB_APPEAR_SPEED			(2)		//�I�[�u���o�������Ƃ��̑��x
#define ORB_MOVE_SPEED				(18)	//�I�[�u���v���C���[�Ɍ������Ƃ��̑��x

#define ORB_APPEAR_TIME				(30)	//�I�[�u�̏o����Ԃ��I���܂ł̎���


//�I�[�u�̏��
enum OrbState {
	ORB_STATE_NONE,		//���g�p���
	ORB_STATE_APPEAR,	//�o�����
	ORB_STATE_CHASE,	//�ǔ����
};



OrbSpawner g_orb_spawner[ORB_SPAWNER_MAX];	//�I�[�u�X�|�i�[�I�u�W�F�N�g
OrbSpawner g_prototype_orb_spawner;			//�I�[�u�X�|�i�[�̃v���g�^�C�v

Orb g_orb[ORB_MAX];			//�I�[�u�I�u�W�F�N�g
Orb g_prototype_orb;		//�I�[�u�̃v���g�^�C�v


//�I�[�u�̏�����
void InitializeOrbs() {

	//�f�[�^�̏�����
	memset(g_orb_spawner, 0, sizeof(g_orb_spawner));
	memset(g_orb, 0, sizeof(g_orb));

	//�v���g�^�C�v�̍쐬
	g_prototype_orb_spawner =
	{
		1,
		0,
		{ 0,0 },
		0
	};

	g_prototype_orb =
	{
		ORB_STATE_APPEAR,
		0,
		{ 0,0 },
		{-20,-20,20,20},
		{ 0,0 },
		0,
		1,
		{ g_sprite[SPR_STD_MONSTER],0.75,0.0 },
		33
	};
	g_prototype_orb.graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_prototype_orb.sprite_num);
}

//�I�[�u�X�|�i�[�̐���
BOOL CreateOrbSpawner(Vector2DF *pos, int sp) {
	int i;
	for (i = 0; i < ORB_SPAWNER_MAX; i++) {
		//���g�p���ǂ���
		if (!g_orb_spawner[i].state) {
			g_orb_spawner[i] = g_prototype_orb_spawner;
			g_orb_spawner[i].pos = *pos;
			g_orb_spawner[i].sp = sp;
			return TRUE;
		}
	}
	return FALSE;
}

//�I�[�u�̐���
BOOL CreateOrb(Vector2DF *pos, int sp) {
	int i;
	for (i = 0; i < ORB_SPAWNER_MAX; i++) {
		//���g�p���ǂ���
		if (!g_orb[i].state) {
			g_orb[i] = g_prototype_orb;
			g_orb[i].pos = *pos;
			g_orb[i].sp = sp;
			g_orb[i].angle = GetRand(10000) / 10000.0f*PI2;
			return TRUE;
		}
	}
	return FALSE;
}

//�I�[�u�X�|�i�[�̍X�V
void UpdateOrbSpawner() {
	int i;
	for (i = 0; i < ORB_SPAWNER_MAX; i++) {
		if (g_orb_spawner[i].state) {
			//�I�[�u�̐��������Ȃ�
			if (g_orb_spawner[i].count%ORB_SPAWNER_SPEED == 0) {
				//�I�[�u�𐶐�����
				CreateOrb(&g_orb_spawner[i].pos, 1);
				//�c��SP�����炷
				g_orb_spawner[i].sp--;
				//�c��SP���Ȃ��Ȃ�������ł���
				if (g_orb_spawner[i].sp <= 0) {
					g_orb_spawner[i].state = 0;
				}
			}
			g_orb_spawner[i].count++;
		}
	}
}

//�I�[�u�̍X�V
void UpdateOrbs() {
	int i;
	for (i = 0; i < ORB_MAX; i++) {
		if (g_orb[i].state) {
			
			//���W�ɑ��x�𑫂�
			AddVector2DF(g_orb[i].pos, g_orb[i].vel);

			//�o����Ԃ̎�
			if (g_orb[i].state == ORB_STATE_APPEAR) {
				float t = g_orb[i].count * 1.0f / ORB_APPEAR_TIME;
				t = t*(2 - t);
				CalcVector2DF(g_orb[i].vel, ORB_APPEAR_SPEED * t, g_orb[i].angle);
				//��]�A�j���[�V����
				if (g_orb[i].count % ORB_APPEAR_ROTATE_SPEED == ORB_APPEAR_ROTATE_SPEED - 1) {
					g_orb[i].graph.angle += PI / 2;
				}
			}
			//�ǔ���Ԃ̎�
			else {
				Vector2DF pos = OrderGetPlayerPos();
				g_orb[i].angle = atan2f(pos.y - g_orb[i].pos.y, pos.x - g_orb[i].pos.x);
				CalcVector2DF(g_orb[i].vel, ORB_MOVE_SPEED, g_orb[i].angle);
				//��]�A�j���[�V����
				if (g_orb[i].count % ORB_MOVE_ROTATE_SPEED == ORB_MOVE_ROTATE_SPEED - 1) {
					g_orb[i].graph.angle += PI / 2;
				}
			}
			
			//�o����Ԃ��I�������ǔ���Ԃɂ���
			if (g_orb[i].count == ORB_APPEAR_TIME) {
				g_orb[i].state = ORB_STATE_CHASE;
			}

			g_orb[i].count++;
		}
	}
}

//�I�[�u�̕`��
void DrawOrbs() {
	int i;
	for (i = 0; i < ORB_MAX; i++) {
		if (g_orb[i].state) {
			DrawGraphicToMap(g_orb[i].pos, &g_orb[i].graph);
		}
	}
}

//�I�[�u�̓����蔻��̐ݒ�
void SetOrbsCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < ORB_MAX; i++) {
		collider[i].state = &g_orb[i].state;
		collider[i].pos = &g_orb[i].pos;
		collider[i].col = &g_orb[i].col;
		collider[i].vel = &g_orb[i].vel;
	}
}

//�I�[�u�̏��ŏ���
void DestroyOrb(int i) {
	//SP���񕜂�����
	OrderAddPlayerSp(g_orb[i].sp);
	g_orb[i].state = ORB_STATE_NONE;
	SetSE(SE_ORB);
}