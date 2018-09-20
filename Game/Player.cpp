//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  �v���C���[�I�u�W�F�N�g�̏���
//!
//! @date   2018/09/15
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "ScenePlay.h"
#include "Mediator.h"
#include "Key.h"
#include "Sound.h"
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
#define KEY_INPUT_S_AREA	(KEY_INPUT_A)		//�����E���Ŕ͈͕\���L�[


//�v���g�^�C�v�錾
void ActPlayer();
void PlayerActMiss();
void PlayerActStand();
void PlayerActJump();
void PlayerActSummon();
void PlayerActClear();
void AnimatePlayer();
void SummonMinion();
void PlayerMiss(BOOL is_damage);



//�O���[�o���ϐ��̐錾
Player g_player;									//�v���C���[�I�u�W�F�N�g
Graph g_sword;										//���I�u�W�F�N�g
int g_summon_time;									//��������ɕK�v�Ȏ���
SummonableList g_summonable[MINION_PATTERN_NUM+1];	//�����\�ȃ����X�^�[�̃��X�g
int g_slist_active_num;								//���X�g�Ŏg�p���̗v�f��
int g_select_summon_type;							//�I�𒆂̏����^�C�v
SummonAreaData g_summon_area;						//�����E���Ŕ͈͏��
BOOL g_use_summon_area;								//�����E���Ŕ͈͕\���t���O
BOOL g_is_walking;									//������������ǂ���
BOOL g_was_walking;									//�O����������ǂ���
BOOL g_is_damage;									


extern HFNT g_font_g40;



//�v���C���[�̏�����
void InitializePlayer() {
	g_player.state = PLAYER_STATE_STAND;
	g_player.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT-100 };
	g_player.col = RectF{ -14,-31,14,31 };
	g_player.vel = Vector2DF{ 0,0 };
	g_player.ride = NULL;
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
	g_summonable[0].graph = Graph{ g_sprite[SPR_DELETE_ICON],1.0,0.0 };
	g_slist_active_num = 1;
	g_select_summon_type = 0;
	memset(&g_summon_area, 0, sizeof(g_summon_area));
	g_use_summon_area = GetUseSummonArea();

	g_is_walking = FALSE;
	g_was_walking = FALSE;

	g_is_damage = FALSE;
}


//�v���C���[�̍X�V
void UpdatePlayer() {
	//�v���C���[�������Ă���ꍇ
	if (g_player.state) {
		//�v���C���[�̍s��
		ActPlayer();
		//�}�b�v�̉��ɏo�Ȃ��悤�ɂ���
		OrderClampMap(&g_player.pos, &g_player.col);
		//�}�b�v�ł̎��S����
		if (OrderIsUnderMap(&g_player.pos,&g_player.col)) {
			PlayerMiss(FALSE);
		}
		//�����E���Ŕ͈͂̕\���ؑ�
		if (CheckHitKeyDown(KEY_INPUT_S_AREA)) {
			g_use_summon_area = !g_use_summon_area;
			SetUseSummonArea(g_use_summon_area);
		}
	}
	//�v���C���[������ł���ꍇ
	else {
		PlayerActMiss();
	}
	//�v���C���[�̃A�j���[�V����
	AnimatePlayer();

	//�����n�߂�����ʉ���炷
	if (g_is_walking && !g_was_walking) {
		SetSE(SE_WALK);
	}
	//�����ĂȂ��Ȃ���ʉ����~�߂�
	else if (!g_is_walking && g_was_walking) {
		StopSE(SE_WALK);
	}
	//�t���O�̍X�V
	g_was_walking = g_is_walking;
	g_is_walking = FALSE;


}


//�v���C���[�̍s��
void ActPlayer() {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(g_player.pos, g_player.vel);

	//���n���Ă����Ȃ瑬�x��0�ɂ���
	if (g_player.is_ground && g_player.vel.y > 0) {
		g_player.vel.y = 0;
	}

	//�����E���Ŕ͈͏��̎擾
	g_summon_area = OrderGetSummonAreaData(g_summonable[g_select_summon_type].knd, &g_player.pos, &g_player.col, g_player.is_left);

	//�v���C���[�̏�Ԃŕ��򂷂�
	switch (g_player.state) {
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

	//�}�b�v�Ƃ̒��n����̓K�p
	g_player.is_ground = g_player.ground_flag;

	//�����^�C�v�̑I��
	if (CheckHitKeyDown(KEY_INPUT_SELECT)) {
		g_select_summon_type = (g_select_summon_type + 1) % g_slist_active_num;
	}

}

//�v���C���[�̃~�X���
void PlayerActMiss() {
	//��ɔ��ŗ�������
	if (g_player.anime_count == 0) {
		//�������Ȃ��΂Ȃ�
		if (g_is_damage) {
			g_player.vel.y = PLAYER_JUMP_SPEED*1.5f;
		}
	}
	else {
		g_player.vel.y += GRAVITY;
	}

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(g_player.pos, g_player.vel);

	g_player.vel.x = 0;
	g_player.anime_count++;
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
		g_is_walking = TRUE;
		break;
	case 2:
		g_player.vel.x = PLAYER_WALK_SPEED;
		g_player.is_left = FALSE;
		g_player.anime_count++;
		g_is_walking = TRUE;
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
	case PLAYER_STATE_MISS:
		sprite_num = g_player.sprite_num;
		g_player.graph.angle += PI2 / 20.0f;
		break;
	//�����Ă���Ȃ�
	case PLAYER_STATE_STAND:
		//������
		if (g_player.is_left) {
			if ((g_player.anime_count+5) % 12 < 6) {
				sprite_num = 6;
			}
			else {
				sprite_num = 7;
			}
		}
		//�E����
		else {
			if ((g_player.anime_count + 5) % 12 < 6) {
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
		//������Ԃ̂Ƃ��̓v���C���[�̃X�v���C�g��ύX���Ȃ�
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
			if (!(g_summon_time = OrderCreateMinion(&g_summon_area))) {
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
			SetSE(SE_SWORD);
		}
	}
	//�����X�^�[�̏��ŏ���
	else {
		OrderDeleteMinion(&g_summon_area);
		g_summon_time = SUMMON_FAILED_TIME;
		SetSE(SE_SWORD);
	}
}

//�v���C���[�̕`��
void DrawPlayer() {
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

//�v���C���[�֌W�̏��̕`��
void DrawPlayerUI() {
	//SP�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(SP_POS_X - 10, SP_POS_Y, SP_POS_X + 100, SP_POS_Y + 35, COLOR_AQUA, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatStringFToHandle(SP_POS_X, SP_POS_Y, COLOR_BLUE, g_font_g40, "SP:%d", g_player.sp);

	//�����\�ȃ����X�^�[�̃��X�g�̕`��
	int i;
	for (i = 0; i < g_slist_active_num; i++) {
		int index = (g_select_summon_type + i) % g_slist_active_num;
		//�擪�͑傫���\������
		g_summonable[index].graph.exrate = (i == 0) ? 1.0f : 0.75f;
		//�\���ʒu
		Vector2DF pos = { (float)(SLIST_POS_X + i * SLIST_DIST_X),(float)(SLIST_POS_Y) };
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		//�g�̕`��
		DrawBoxAA(pos.x - 32 * g_summonable[index].graph.exrate,
			pos.y - 32 * g_summonable[index].graph.exrate,
			pos.x + 32 * g_summonable[index].graph.exrate,
			pos.y + 32 * g_summonable[index].graph.exrate,
			COLOR_WHITE,
			TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//���Ń��[�h�̓����X�^�[�̉摜��\�����Ȃ�
		if (index != 0) {
			//�����R�X�g�̎擾
			int cost = OrderGetSummonCost(g_summonable[index].knd);
			int r, g, b;
			//�R�X�g�s���Ȃ�
			if (cost > g_player.sp) {
				GetDrawBright(&r, &g, &b);
				SetDrawBright(r * 2 / 5, g * 2 / 5,b * 2 / 5);
			}
			DrawGraphic(pos, &g_summonable[index].graph);
			float exrate = g_summonable[index].graph.exrate;
			DrawFormatStringFToHandle(pos.x + 15 * exrate, pos.y + 8 * exrate, COLOR_YELLOW, g_font_g30, "%d", cost);
			if (cost > g_player.sp) {
				SetDrawBright(r, g, b);
			}
		}
		//���ŃA�C�R���̕`��
		else {
			g_summonable[index].graph.exrate *= 0.8f;
			DrawGraphic(pos, &g_summonable[index].graph);
		}
	}

	//�����E���Ŕ͈͏��̕`��
	if (g_use_summon_area) {
		if (g_player.state == PLAYER_STATE_STAND || g_player.state == PLAYER_STATE_JUMP) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
			int color = g_summon_area.state == 0 ? COLOR_BLUE : COLOR_RED;
			Vector2DF pos = g_summon_area.pos;
			SubVector2DF(pos, OrderGetCameraOffset());
			DrawBoxAA(pos.x + g_summon_area.area.left,
				pos.y + g_summon_area.area.top,
				pos.x + g_summon_area.area.right,
				pos.y + g_summon_area.area.bottom,
				color,
				TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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

//�v���C���[�̌�����ݒ肷��
void SetPlayerDirection(BOOL isLeft) {
	g_player.is_left = isLeft;
	//�X�v���C�g�̕ύX
	g_player.sprite_num = (isLeft ? 6 : 4);
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
	
}

//�v���C���[�̏����\�����X�^�[��ݒ肷��
void SetPlayerSummonable(BOOL summonable[]) {
	int i;
	for (i = 0; i < MINION_PATTERN_NUM; i++) {
		if (g_summonable[g_slist_active_num].is_use = summonable[i]) {
			g_summonable[g_slist_active_num].knd = MinionPattern(i);
			g_summonable[g_slist_active_num].graph = { g_sprite[SPR_STD_MONSTER],1.0,0.0 };
			g_summonable[g_slist_active_num].graph.sprite = OrderGetMinionSprite(MinionPattern(i));
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
	collider->collision_state = &g_player.is_ground;
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
	g_player.anime_count = 0;
	//�X�e�[�W�N���A�̒ʒm
	RequestStageClear();
}

//�v���C���[�����񂾎��̏���
void PlayerMiss(BOOL is_damage) {
	//���o���s�����̔���
	g_is_damage = is_damage;
	//�v���C���[���~�X��Ԃɂ���
	g_player.state = PLAYER_STATE_MISS;
	g_player.anime_count = 0;
	//�X�e�[�W���s�̒ʒm
	RequestStageFailed();
}

//�v���C���[���_���[�W����ƏՓ˂����Ƃ��̏���
void CollisionPlayer() {
	//���񂾂Ƃ��̏������Ăяo��
	PlayerMiss(TRUE);
}
