//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.cpp
//!
//! @brief  �}�b�v�֘A�̏���
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "Mediator.h"


//�萔�̒�`
//#define MAP_OFFSET_X	(32)	//�}�b�v�̃I�t�Z�b�g
//#define MAP_OFFSET_Y	(32)	//�}�b�v�̃I�t�Z�b�g


//�v���g�^�C�v�錾
extern void LoadMapData(const StageId stageId, MapData *mapdata);	//�}�b�v�f�[�^�̓ǂݍ��� (Load.cpp)


//�O���[�o���ϐ��̐錾
MapData g_mapdata;				//�}�b�v���̍\����
Vector2DF g_camera_offset;		//�J�����̃I�t�Z�b�g


//�}�b�v�̏�����
void InitializeMap() {
	int i, j;

	//�}�b�v�f�[�^�̏�����
	memset(&g_mapdata, 0, sizeof(g_mapdata));

	//�}�b�v�f�[�^�̓ǂݍ���
	LoadMapData(GetSelectStage(), &g_mapdata);

	//�v���C���[�̏������W��ݒ肷��
	MulVector2DF(g_mapdata.player_pos, MAPCHIP_SIZE);
	AddVector2DF(g_mapdata.player_pos, Vector2DF{ MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF });
	OrderSetPlayerPos(g_mapdata.player_pos);
	//�v���C���[�̏����\�ȃ����X�^�[��ݒ肷��
	OrderSetPlayerSummonable(g_mapdata.summonable);
	//�v���C���[��SP��ݒ肷��
	OrderSetPlayerSp(g_mapdata.player_sp);

	//����̏������W��ݒ肷��
	MulVector2DF(g_mapdata.treasure_pos, MAPCHIP_SIZE);
	AddVector2DF(g_mapdata.treasure_pos, Vector2DF{ MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF });
	OrderSetTreasurePos(g_mapdata.treasure_pos);


	//�}�b�v�f�[�^�̏�����
	for (i = 0; i < g_mapdata.width; i++) {
		for (j = 0; j < g_mapdata.height; j++) {
			if (g_mapdata.map[i][j].knd == 0) {
				g_mapdata.map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_1 + (i % 2));
			}
			else {
				g_mapdata.map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_2 + g_mapdata.map[i][j].knd);
			}
			g_mapdata.map[i][j].pos = Vector2DF{ (float)(i*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF),(float)(j*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF) };
			g_mapdata.map[i][j].graphp = GraphP{ &g_sprite[g_mapdata.map[i][j].knd],1.0,0.0 };
		}
	}


	//�I�t�Z�b�g�̏�����
	g_camera_offset = { 0,0 };
}

//�J�����̃I�t�Z�b�g���v�Z����
void UpdateCameraOffset() {
	//�v���C���[���W�̎擾
	Vector2DF pl = OrderGetPlayerPos();

	//�v���C���[�����Ɋ���Ă���ꍇ
	if (pl.x < SCREEN_CENTER_X) {
		g_camera_offset.x = 0;
	}
	//�v���C���[���E�Ɋ���Ă���ꍇ
	else if (g_mapdata.width*MAPCHIP_SIZE - pl.x < SCREEN_CENTER_X) {
		g_camera_offset.x = (float)(g_mapdata.width*MAPCHIP_SIZE - SCREEN_WIDTH);
	}
	//�v���C���[���^�񒆂ɂ���ꍇ
	else {
		g_camera_offset.x = (float)(pl.x - SCREEN_CENTER_X);
	}

	//�v���C���[����Ɋ���Ă���ꍇ
	if (pl.y < SCREEN_CENTER_Y) {
		g_camera_offset.y = 0;
	}
	//�v���C���[�����Ɋ���Ă���ꍇ
	else if (g_mapdata.height*MAPCHIP_SIZE - pl.y < SCREEN_CENTER_Y) {
		g_camera_offset.y = (float)(g_mapdata.height*MAPCHIP_SIZE - SCREEN_HEIGHT);
	}
	//�v���C���[���^�񒆂ɂ���ꍇ
	else {
		g_camera_offset.y = (float)(pl.y - SCREEN_CENTER_Y);
	}
	
}

//�}�b�v�̕`��
void DrawMap() {
	int i, j;
	for (i = 0; i < g_mapdata.width; i++) {
		for (j = 0; j < g_mapdata.height; j++) {
			DrawGraphicToMapP(g_mapdata.map[i][j].pos, &g_mapdata.map[i][j].graphp);
		}
	}
}


//�}�b�v���擾����
MapData GetMap() {
	return g_mapdata;
}

//�w�肵�����W���}�b�v���W�ɕϊ�����
void GetMapPosWithPos(Vector2DF pos, int *x, int *y) {
	*x = (int)(pos.x / MAPCHIP_SIZE);
	*y = (int)(pos.y / MAPCHIP_SIZE);
}

//�w�肵���}�b�v���W�����W�ɕϊ�����
Vector2DF GetPosWithMapPos(int x, int y) {
	Vector2DF ret;
	ret.x = (float)(x*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF);
	ret.y = (float)(y*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF);
	return ret;
}

//�w�肵�����W���ʉߕs�}�X���ǂ���
BOOL IsWallWithPos(float x, float y) {
	int ix = (int)(x / MAPCHIP_SIZE);
	int iy = (int)(y / MAPCHIP_SIZE);
	//�͈͊O���ǂ���
	if (ix < 0 || ix >= g_mapdata.width ||
		iy < 0 || iy >= g_mapdata.height) {
		return FALSE;
	}
	//�ʉ߉\�}�X���ǂ���
	if (g_mapdata.map[ix][iy].knd <= SPR_MAPCHIP1_1 + 1) {
		return FALSE;
	}
	return TRUE;
	
}

//�J�����̃I�t�Z�b�g���擾����
Vector2DF GetCameraOffset() {
	return g_camera_offset;
}

//�}�b�v�O�ɂ��邩�̔���
BOOL IsOutsideMap(Vector2DF *pos, RectF *col) {
	if (
		pos->x + col->right<0 ||
		pos->x + col->left> g_mapdata.width*MAPCHIP_SIZE ||
		pos->y + col->bottom < 0 ||
		pos->y + col->top > g_mapdata.height*MAPCHIP_SIZE
		) {
		return TRUE;
	}
	return FALSE;
}

//��ʉ��ɂ��邩�̔���
BOOL IsUnderMap(Vector2DF *pos, RectF *col) {
	if (pos->y + col->top > g_mapdata.height*MAPCHIP_SIZE) {
		return TRUE;
	}
	return FALSE;
}


