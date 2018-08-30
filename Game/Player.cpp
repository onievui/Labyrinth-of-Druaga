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
#define SP_POS_X			(670)	//SP�̕\��X���W
#define SP_POS_Y			(10)	//SP�̕\��Y���W
#define SLIST_POS_X			(50)	//�����\�ȃ����X�^�[�̃��X�g�̕\��X���W
#define SLIST_POS_Y			(40)	//�����\�ȃ����X�^�[�̃��X�g�̕\��Y���W
#define SLIST_DIST_X		(70)	//�����\�ȃ����X�^�[�̃��X�g��X�����̊Ԋu
#define SUMMON_FAILED_TIME	(32)	//�����Ɏ��s�����Ƃ��̑҂�����

#define KEY_INPUT_JUMP		(KEY_INPUT_Z)		//�W�����v�L�[
#define KEY_INPUT_SUMMON	(KEY_INPUT_X)		//����/���ŃL�[
#define KEY_INPUT_SELECT	(KEY_INPUT_LSHIFT)	//���������X�^�[�I���L�[


//�v���g�^�C�v�錾
void ActPlayer();
void PlayerActDead();
void PlayerActStand();
void PlayerActJump();
void PlayerActSummon();
void PlayerActClear();
void AnimatePlayer();
void SummonMinion();



//�O���[�o���ϐ��̐錾
Player g_player;									//�v���C���[�I�u�W�F�N�g
Graph g_sword;										//���I�u�W�F�N�g
int g_summon_time;									//��������ɕK�v�Ȏ���
SummonableList g_summonable[MINION_PATTERN_NUM+1];	//�����\�ȃ����X�^�[�̃��X�g
int g_slist_active_num;								//���X�g�Ŏg�p���̗v�f��
int g_select_summon_type;							//�I�𒆂̏����^�C�v


extern HFNT g_font_g40;



//�v���C���[�̏�����
void InitializePlayer() {
	g_player.state = PLAYER_STATE_STAND;
	g_player.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT-100 };
	g_player.col = RectF{ -14,-31,14,31 };
	g_player.vel = Vector2DF{ 0,0 };
	g_player.ride = nullptr;
	g_player.is_left = TRUE;
	g_player.is_ground = FALSE;
	g_player.sp = 20;
	g_player.sprite_num = 6;
	g_player.graph = Graph{ g_sprite[SPR_STD_GIL],1.0,0.0 };
	g_player.anime_count = 0;
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, 6);

	g_sword = Graph{ g_sprite[SPR_STD_SWORD],1.0,0.0 };
	g_sword.sprite.rect = GetSpriteRect(SPR_STD_SWORD, 6);

	g_summon_time = 0;
	memset(g_summonable, 0, sizeof(g_summonable));
	g_summonable[0].is_use = TRUE;
	g_summonable[0].knd = MINION_PATTERN_NUM;
	g_slist_active_num = 1;
	g_select_summon_type = 0;
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

	//���n���Ă����Ȃ瑬�x��0�ɂ���
	if (g_player.is_ground && g_player.vel.y > 0) {
		g_player.vel.y = 0;
	}

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

	//����Ă���I�u�W�F�N�g�̑��x��������
	if (g_player.ride) {
		AddVector2DF(g_player.vel, *g_player.ride);
	}

	g_player.is_ground = g_player.ground_flag;

	//�����^�C�v�̑I��
	if (CheckHitKeyDown(KEY_INPUT_SELECT)) {
		g_select_summon_type = (g_select_summon_type + 1) % g_slist_active_num;
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
	if (CheckHitKeyDown(KEY_INPUT_SUMMON)) {
		g_player.state = PLAYER_STATE_SUMMON;
		SummonMinion();
		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//�W�����v�����Ȃ������ɉ������ăW�����v��ԂɑJ�ڂ���
	else if (CheckHitKeyDown(KEY_INPUT_JUMP) && g_player.is_ground) {
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
	if (CheckHitKeyDown(KEY_INPUT_SUMMON)) {
		g_player.state = PLAYER_STATE_SUMMON;
		SummonMinion();
		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//�n��ɂ����Ȃ痧����Ԃɂ���
	else if (g_player.is_ground) {
		g_player.state = PLAYER_STATE_STAND;
	}
}

//�v���C���[�̏������
void PlayerActSummon() {
	g_player.vel.x = 0;
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

//�����X�^�[�̏�������
void SummonMinion() {
	//���Ń��[�h�łȂ��Ȃ珢��
	if (g_summonable[g_select_summon_type].knd != MINION_PATTERN_NUM) {
		//�����R�X�g�̎擾
		int cost = OrderGetSummonCost(g_summonable[g_select_summon_type].knd);
		//SP������邩�̊m�F
		if (g_player.sp >= cost) {
			//�����Ɏ��s���Ă����[�V�������s��
			if (!(g_summon_time = OrderCreateMinion(g_summonable[g_select_summon_type].knd, g_player.pos, g_player.col, g_player.is_left))) {
				g_summon_time = SUMMON_FAILED_TIME;
			}
			//����������SP�����炷
			else {
				g_player.sp -= cost;
			}
		}
		//�����Ɏ��s���Ă����[�V�������s��
		else {
			g_summon_time = SUMMON_FAILED_TIME;
		}
	}
	//�����X�^�[�̏��ŏ���
	else {
		OrderDeleteMinion(&g_player.pos, &g_player.col, g_player.is_left);
		g_summon_time = SUMMON_FAILED_TIME;
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

//SP�Ə����\�ȃ����X�^�[�̃��X�g�̕`��
void DrawPlayerUI() {
	//SP�̕`��
	DrawFormatStringFToHandle(SP_POS_X, SP_POS_Y, COLOR_BLUE, g_font_g40, "SP:%d", g_player.sp);
	//�����\�ȃ����X�^�[�̃��X�g�̕`��
	int i;
	for (i = 0; i < g_slist_active_num; i++) {
		int index = (g_select_summon_type + i) % g_slist_active_num;
		//�擪�͑傫���\������
		g_summonable[index].graph.exrate = (i == 0) ? 1.0f : 0.75f;
		//�\���ʒu
		Vector2DF pos = { (float)(SLIST_POS_X + i * SLIST_DIST_X),(float)(SLIST_POS_Y) };
		//�g�̕`��
		DrawBoxAA(pos.x - 32 * g_summonable[index].graph.exrate,
			pos.y - 32 * g_summonable[index].graph.exrate,
			pos.x + 32 * g_summonable[index].graph.exrate,
			pos.y + 32 * g_summonable[index].graph.exrate,
			COLOR_AQUA,
			TRUE);
		//���Ń��[�h�͉摜��\�����Ȃ�
		if (index != 0) {
			DrawGraphic(pos, &g_summonable[index].graph);
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

//�v���C���[�̏����\�����X�^�[��ݒ肷��
void SetPlayerSummonable(BOOL summonable[]) {
	int i;
	for (i = 0; i < MINION_PATTERN_NUM; i++) {
		if (g_summonable[i + 1].is_use = summonable[i]) {
			g_summonable[i + 1].knd = MinionPattern(i);
			g_summonable[i + 1].graph = { g_sprite[SPR_STD_MONSTER],1.0,0.0 };
			g_summonable[i + 1].graph.sprite = OrderGetMinionSprite(MinionPattern(i));
			g_slist_active_num++;
		}
	}
}

//�v���C���[��SP��ݒ肷��
void SetPlayerSp(int sp) {
	g_player.sp = sp;
}

//�v���C���[�̓����蔻���ݒ肷��
void SetPlayerCollider(BoxCollider *collider) {
	collider->state = (int*)&g_player.state;
	collider->pos = &g_player.pos;
	collider->col = &g_player.col;
	collider->vel = &g_player.vel;
	collider->ride = &g_player.ride;
	collider->is_ground = &g_player.is_ground;
	collider->ground_flag = &g_player.ground_flag;
}

//�v���C���[��SP���񕜂���
void AddPlayerSp(int plus) {
	g_player.sp += plus;
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

