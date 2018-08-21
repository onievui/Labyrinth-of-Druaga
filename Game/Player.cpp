//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  �v���C���[�I�u�W�F�N�g�̏���
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "ScenePlay.h"
#include "Mediator.h"
#include "Key.h"
#include <math.h>



//�萔�̒�`
#define SUMMON_FAILED_TIME	(32)	//�����Ɏ��s�����Ƃ��̑҂�����


//�v���g�^�C�v�錾
void ActPlayer();
void PlayerActDead();
void PlayerActStand();
void PlayerActJump();
void PlayerActSummon();
void PlayerActClear();
void AnimatePlayer();


//�O���[�o���ϐ��̐錾
Player g_player;		//�v���C���[�I�u�W�F�N�g
Graph g_sword;			//���I�u�W�F�N�g
int g_summon_time;		//��������ɕK�v�Ȏ���


//�v���C���[�̏�����
void InitializePlayer() {
	g_player.state = PLAYER_STATE_STAND;
	g_player.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT-100 };
	g_player.col = RectF{ -14,-31,14,31 };
	g_player.vel = Vector2DF{ 0,0 };
	g_player.is_left = TRUE;
	g_player.is_ground = FALSE;
	g_player.sprite_num = 6;
	g_player.graph = Graph{ g_sprite[SPR_STD_GIL],1.0,0.0 };
	g_player.anime_count = 0;
	
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, 6);

	g_sword = Graph{ g_sprite[SPR_STD_SWORD],1.0,0.0 };

	g_sword.sprite.rect = GetSpriteRect(SPR_STD_SWORD, 6);

	g_summon_time = 0;
}


//�v���C���[�̍X�V
void UpdatePlayer() {
	if (g_player.state) {
		//�v���C���[�̍s��
		ActPlayer();
		//�v���C���[�̃A�j���[�V����
		AnimatePlayer();
	}
}


//�v���C���[�̍s��
void ActPlayer() {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(g_player.pos, g_player.vel);

	//�v���C���[�̏�Ԃŕ��򂷂�
	switch (g_player.state) {
		//����ł���Ȃ�
	case PLAYER_STATE_DEAD:
		PlayerActDead();
		break;
		//�����Ă���Ȃ�
	case PLAYER_STATE_STAND:
		PlayerActStand();
		break;
		//�W�����v���Ă���i�󒆂ɂ���j�Ȃ�
	case PLAYER_STATE_JUMP:
		PlayerActJump();
		break;
		//�������Ă���Ȃ�
	case PLAYER_STATE_SUMMON:
		PlayerActSummon();
		break;
		//�N���A���Ă���Ȃ�
	case PLAYER_STATE_CLEAR:
		PlayerActClear();
		break;
		//�G���[�`�F�b�N
	default:
		MessageBox(NULL, "�v���C���[�̃A�j���[�V�����ŕs���Ȓl���n����܂���", "", MB_OK);
		break;
	}

	//�d�͂�������
	g_player.vel.y += GRAVITY;

	//�}�b�v�Ƃ̓����蔻��
	if (OrderCollisionObjectMap(&g_player.pos, &g_player.vel, &g_player.col) & ISGROUND) {
		g_player.is_ground = TRUE;
	}
	else {
		g_player.is_ground = FALSE;
	}



}

//�v���C���[�̎��ɏ��
void PlayerActDead() {

}

//�v���C���[�̗������
void PlayerActStand() {
	//�������̈ړ�
	switch (CheckStateKeyLater(KEY_INPUT_LEFT, KEY_INPUT_RIGHT)) {
	//�ړ����Ă��Ȃ��Ȃ�A�j���[�V���������Ȃ�
	case 0:
		g_player.vel.x = 0;
		g_player.anime_count = 0;
		break;
	case 1:
		g_player.vel.x = -PLAYER_WALK_SPEED;
		g_player.is_left = TRUE;
		g_player.anime_count++;
		break;
	case 2:
		g_player.vel.x = PLAYER_WALK_SPEED;
		g_player.is_left = FALSE;
		g_player.anime_count++;
		break;
	default:
		MessageBox(NULL, "�v���C���[���̓G���[", "", MB_OK);
		break;
	}
	//���������Ȃ珢����ԂɑJ�ڂ���
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		g_player.state = PLAYER_STATE_SUMMON;
		if (!(g_summon_time = OrderCreateMinion(MINION_SLIME, g_player.pos, g_player.is_left))) {
			g_summon_time = SUMMON_FAILED_TIME;
		}
		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//�W�����v�����Ȃ������ɉ������ăW�����v��ԂɑJ�ڂ���
	else if (CheckHitKeyDown(KEY_INPUT_Z) && g_player.is_ground) {
		g_player.state = PLAYER_STATE_JUMP;
		g_player.vel.y = PLAYER_JUMP_SPEED;
	}
	//�󒆂ɂ����Ȃ�W�����v��Ԃɂ���
	else if (!g_player.is_ground) {
		g_player.state = PLAYER_STATE_JUMP;
	}
}

//�v���C���[�̃W�����v���
void PlayerActJump() {
	//�������̈ړ�
	switch (CheckStateKeyLater(KEY_INPUT_LEFT, KEY_INPUT_RIGHT)) {
		//�ړ����Ă��Ȃ��Ȃ�A�j���[�V���������Ȃ�
	case 0:
		g_player.vel.x = 0;
		break;
	case 1:
		g_player.vel.x = -PLAYER_WALK_SPEED;
		g_player.is_left = TRUE;
		break;
	case 2:
		g_player.vel.x = PLAYER_WALK_SPEED;
		g_player.is_left = FALSE;
		break;
	default:
		MessageBox(NULL, "�v���C���[���̓G���[", "", MB_OK);
		break;
	}
	//���������Ȃ珢����ԂɑJ�ڂ���
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		g_player.state = PLAYER_STATE_SUMMON;
		if (!(g_summon_time = OrderCreateMinion(MINION_SLIME, g_player.pos, g_player.is_left))) {
			g_summon_time = SUMMON_FAILED_TIME;
		}		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//�n��ɂ����Ȃ痧����Ԃɂ���
	else if (g_player.is_ground) {
		g_player.state = PLAYER_STATE_STAND;
	}
}

//�v���C���[�̏������
void PlayerActSummon() {
	//������
	if (g_summon_time > g_player.anime_count) {
		g_player.anime_count++;
	}
	//�I������
	else {
		if (g_player.is_ground) {
			g_player.state = PLAYER_STATE_STAND;
		}
		else {
			g_player.state = PLAYER_STATE_JUMP;
		}
		g_player.anime_count = 0;
	}
}

//�v���C���[�̃N���A���
void PlayerActClear() {
	g_player.vel.x = 0;
	g_player.anime_count++;
}

//�v���C���[�̃A�j���[�V����
void AnimatePlayer() {

	//�V�����X�v���C�g�ԍ�
	int sprite_num;	

	//�v���C���[�̏�Ԃŕ��򂷂�
	switch (g_player.state) {
	//����ł���Ȃ�
	case PLAYER_STATE_DEAD:
		break;
	//�����Ă���Ȃ�
	case PLAYER_STATE_STAND:
		//������
		if (g_player.is_left) {
			if (g_player.anime_count % 12 < 6) {
				sprite_num = 6;
			}
			else {
				sprite_num = 7;
			}
		}
		//�E����
		else {
			if (g_player.anime_count % 12 < 6) {
				sprite_num = 4;
			}
			else {
				sprite_num = 5;
			}
		}
		break;
	//�W�����v���Ă���i�󒆂ɂ���j�Ȃ�
	case PLAYER_STATE_JUMP:
		//������
		if (g_player.is_left) {
			sprite_num = 7;
		}
		//�E����
		else {
			sprite_num = 5;
		}
		break;
	//�������Ă���Ȃ�
	case PLAYER_STATE_SUMMON:
		sprite_num = g_player.anime_count * 16 / g_summon_time;
		//�t�����ɃA�j���[�V����������
		if (sprite_num >= 8) {
			sprite_num = 15 - sprite_num;
		}
		//�摜�̓s���Œ���
		if (sprite_num >= 6) {
			sprite_num = sprite_num == 6 ? 7 : 6;
		}
		//�����ɂ���ĕς���
		sprite_num += g_player.is_left ? 24 : 32;
		break;
	//�N���A��ԂȂ�
	case PLAYER_STATE_CLEAR:
		if (g_player.is_ground) {
			sprite_num = ((g_player.anime_count % 30) < 15);
		}
		else {
			sprite_num = g_player.sprite_num;
		}
		break;
	//�G���[�`�F�b�N
	default:
		MessageBox(NULL, "�v���C���[�̃A�j���[�V�����ŕs���Ȓl���n����܂���", "", MB_OK);
		break;
	}

	//�X�v���C�g���ύX���ꂩ�ǂ���
	if (g_player.sprite_num != sprite_num) {
		//�X�v���C�g�ԍ��̕ύX
		g_player.sprite_num = sprite_num;
		//������ԂłȂ��Ƃ��̓v���C���[�̃X�v���C�g��ύX���Ȃ�
		if (g_player.state != PLAYER_STATE_SUMMON) {
			//�X�v���C�g�̕ύX
			g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
		}
		//���X�v���C�g�̕ύX
		g_sword.sprite.rect = GetSpriteRect(SPR_STD_SWORD, g_player.sprite_num);
	}
}

//�v���C���[�̕`��
void DrawPlayer() {
	if (g_player.state) {
		//�����ɂ���ĕ\������ς���
		if (g_player.is_left && g_player.state != PLAYER_STATE_CLEAR) {
			DrawGraphicToMap(g_player.pos, &g_sword);
			DrawGraphicToMap(g_player.pos, &g_player.graph);
		}
		else {
			DrawGraphicToMap(g_player.pos, &g_player.graph);
			DrawGraphicToMap(g_player.pos, &g_sword);
		}
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

//�v���C���[�̒n�ʔ����ݒ肷��
void SetPlayerIsGround(BOOL isGround) {
	g_player.is_ground = isGround;
}

//�v���C���[�̓����蔻���ݒ肷��
void SetPlayerCollider(BoxCollider *collider) {
	collider->state = (int*)&g_player.state;
	collider->pos = &g_player.pos;
	collider->vel = &g_player.vel;
	collider->col = &g_player.col;
}

//�v���C���[��������擾�����Ƃ��̏���
void PlayerGetTreasure() {
	//�v���C���[���N���A��Ԃɂ���
	g_player.state = PLAYER_STATE_CLEAR;
	//�X�e�[�W�N���A�̒ʒm
	RequestStageClear();
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

