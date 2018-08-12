//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  �v���C���[�I�u�W�F�N�g�̏���
//!
//! @date   2018/08/09
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "GameDefine.h"
#include "Player.h"
#include "Mediator.h"
#include "Key.h"
#include <math.h>



//�v���g�^�C�v�錾
void MovePlayer();
void AnimatePlayer();


//�O���[�o���ϐ��̐錾
Player g_player;


//�v���C���[�̏�����
void InitializePlayer() {
	g_player.state = 1;
	g_player.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT-100 };
	g_player.col = RectF{ -14,-31,14,31 };
	g_player.vel = Vector2DF{ 0,0 };
	g_player.speed = 5;
	g_player.is_left = TRUE;
	g_player.sprite_num = 6;
	g_player.graph = Graph{ g_sprite[SPR_STD_GIL],1.0,0.0 };
	g_player.anime_count = 0;
	
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, 6);
}


//�v���C���[�̍X�V
void UpdatePlayer() {
	if (g_player.state) {
		//�v���C���[�̈ړ�
		MovePlayer();
		//�v���C���[�̃A�j���[�V����
		AnimatePlayer();
	}
}


//�v���C���[�̈ړ�
void MovePlayer() {
	
	//���x�̏�����
	//g_player.vel = Vector2DF{ 0,0 };
	//�ړ���̍��W
	Vector2DF next_pos = Vector2DF{ g_player.pos.x,g_player.pos.y };
	

	//�������̈ړ�
	switch (CheckStateKeyLater(KEY_INPUT_LEFT, KEY_INPUT_RIGHT)) {
	case 0:
		g_player.vel.x = 0;
		break;
	case 1:
		//AddVector2DF(g_player.vel, Vector2DF{ -g_player.speed,0 });
		g_player.vel.x = -g_player.speed;
		g_player.is_left = TRUE;
		g_player.anime_count++;
		break;
	case 2:
		//AddVector2DF(g_player.vel, Vector2DF{ g_player.speed,0 });
		g_player.vel.x = g_player.speed;
		g_player.is_left = FALSE;
		g_player.anime_count++;
		break;
	default:
		MessageBox(NULL, "�v���C���[���̓G���[", "", MB_OK);
		break;
	}

	if (CheckHitKeyDown(KEY_INPUT_Z)) {
		g_player.vel.y -= 25;
	}

	g_player.vel.y += 2.4f;

	if (g_player.pos.y + g_player.col.top > FIELD_HEIGHT) {
		g_player.pos.y -= FIELD_HEIGHT;
	}

	////�c�����̈ړ�
	//switch (CheckStateKeyLater(KEY_INPUT_UP, KEY_INPUT_DOWN)) {
	//case 0:
	//	break;
	//case 1:
	//	AddVector2DF(g_player.vel, Vector2DF{ 0,-g_player.speed });
	//	ud_flag = true;
	//	break;
	//case 2:
	//	AddVector2DF(g_player.vel, Vector2DF{ 0,g_player.speed });
	//	ud_flag = true;
	//	break;
	//default:
	//	MessageBox(NULL, "�v���C���[���̓G���[", "", MB_OK);
	//	break;
	//}


	//�}�b�v�Ƃ̓����蔻��
	OrderCollisionObjectMap(&g_player.pos, &g_player.vel, &g_player.col);


	//�ړ��ʂ����W�ɑ���
	AddVector2DF(g_player.pos, g_player.vel);

	//�ړ��͈͊O�Ȃ���W��[�ɖ߂�
	/*if (next_pos.x - g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate < 0) {
		g_player.pos.x = 0 + g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate;
	}
	else if (next_pos.x + g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate > FIELD_WIDTH) {
		g_player.pos.x = FIELD_WIDTH - g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate;

	}
	else {
		g_player.pos.x = next_pos.x;
	}
	if (next_pos.y - g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate < 0) {
		g_player.pos.y = 0 + g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate;
	}
	else if (next_pos.y + g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate > FIELD_HEIGHT) {
		g_player.pos.y = FIELD_HEIGHT - g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate;
	}
	else {
		g_player.pos.y = next_pos.y;
	}*/

}

//�v���C���[�̃A�j���[�V����
void AnimatePlayer() {
	//�����Ă���Ȃ�
	if (g_player.state == 1) {
		//������
		if (g_player.is_left) {
			if (g_player.anime_count % 12 < 6) {
				g_player.sprite_num = 6;
			}
			else {
				g_player.sprite_num = 7;
			}
		}
		//�E����
		else {
			if (g_player.anime_count % 12 < 6) {
				g_player.sprite_num = 4;
			}
			else {
				g_player.sprite_num = 5;
			}
		}
	}
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
}

//�v���C���[�̕`��
void DrawPlayer() {
	if (g_player.state==1) {
		DrawGraphic(g_player.pos, &g_player.graph);
		RectF rect = { g_player.pos.x + g_player.col.left,
			g_player.pos.y + g_player.col.top,
			g_player.pos.x + g_player.col.right,
			g_player.pos.y + g_player.col.bottom };
		DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);
	}
}

//�v���C���[�̍��W���擾����
Vector2DF GetPlayerPos() {
	return g_player.pos;
}

//�v���C���[�̍��W��ݒ肷��
void SetPlayerPos(Vector2DF pos) {
	g_player.pos = pos;
}


//�v���C���[�̓����蔻���ݒ肷��
void SetPlayerCollider(BoxCollider *collider) {
	collider->state = &g_player.state;
	collider->pos = &g_player.pos;
	collider->vel = &g_player.vel;
	collider->col = &g_player.col;
}

//�v���C���[���G�ƏՓ˂����Ƃ��̏���
//void CollisionPlayer() {
//	//���G��ԂȂ珈�����Ȃ�
//	if (g_player.state == 2) {
//		return;
//	}
//	g_player.state = 0;
//	SetSE(SE_MISS);
//	OrderCreateEffect(EFF_PATTERN_2, g_player.pos);
//	//�R���e�B�j���[�̊m�F
//	RequestContinue();
//}

