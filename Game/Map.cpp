//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.cpp
//!
//! @brief  �}�b�v�֘A�̏���
//!
//! @date   2018/08/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "GameDefine.h"
#include "Mediator.h"



//�萔�̒�`
#define MAP_OFFSET_X	(32)	//�}�b�v�̃I�t�Z�b�g
#define MAP_OFFSET_Y	(32)	//�}�b�v�̃I�t�Z�b�g



//�v���g�^�C�v�錾



//�O���[�o���ϐ��̐錾
Map g_map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	//�}�b�v�\����
MapAll g_mapall;							//�}�b�v�S�̂̍\����
int g_map_width, g_map_height;				//�}�b�v�̏c����
Vector2DF g_camera_offset;					//�J�����̃I�t�Z�b�g




//�}�b�v�̏�����
void InitializeMap() {
	int i, j;
	int map_data[MAP_WIDTH_MAX*MAP_HEIGHT_MAX];
	int player_pos[2];
	Vector2DF player_pos2;

	//�}�b�v�f�[�^�̓ǂݍ���
	LoadMapData(GetSelectStage(), map_data, &g_map_width, &g_map_height, player_pos);

	//�v���C���[�̏������W��ݒ肷��
	player_pos2.x = (float)(player_pos[0] * MAPCHIP_SIZE + MAP_OFFSET_X);
	player_pos2.y = (float)(player_pos[1] * MAPCHIP_SIZE + MAP_OFFSET_Y);
	OrderSetPlayerPos(player_pos2);


	//�}�b�v�f�[�^�̏�����
	for (i = 0; i < g_map_width; i++) {
		for (j = 0; j < g_map_height; j++) {
			int knd = map_data[i + j*g_map_width];
			if (knd == 0) {
				g_map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_1 + (i % 2));
			}
			else {
				g_map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_2 + knd);
			}
			g_map[i][j].pos = Vector2DF{ (float)(i*MAPCHIP_SIZE + MAP_OFFSET_X),(float)(j*MAPCHIP_SIZE + MAP_OFFSET_Y) };
			g_map[i][j].graphp = GraphP{ &g_sprite[g_map[i][j].knd],1.0,0.0 };
		}
	}
	g_mapall.map = g_map;

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
	else if (g_map_width*MAPCHIP_SIZE - pl.x < SCREEN_CENTER_X) {
		g_camera_offset.x = (float)(g_map_width*MAPCHIP_SIZE - SCREEN_WIDTH);
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
	else if (g_map_height*MAPCHIP_SIZE - pl.y < SCREEN_CENTER_Y) {
		g_camera_offset.y = (float)(g_map_height*MAPCHIP_SIZE - SCREEN_HEIGHT);
	}
	//�v���C���[���^�񒆂ɂ���ꍇ
	else {
		g_camera_offset.y = (float)(pl.y - SCREEN_CENTER_Y);
	}
	
}

//�}�b�v�̕`��
void DrawMap() {
	int i, j;
	for (i = 0; i < g_map_width; i++) {
		for (j = 0; j < g_map_height; j++) {
			DrawGraphicToMapP(g_map[i][j].pos, &g_map[i][j].graphp);
		}
	}
}


//�}�b�v���擾����
MapAll GetMap() {
	return g_mapall;
}

//�w�肵�����W���ʉߕs�}�X���ǂ���
BOOL IsMapPosWall(float x, float y) {
	int ix = (int)(x / MAPCHIP_SIZE);
	int iy = (int)(y / MAPCHIP_SIZE);
	//�͈͊O���ǂ���
	if (ix < 0 || ix >= g_map_width ||
		iy < 0 || iy >= g_map_height) {
		return FALSE;
	}
	//�ʉ߉\�}�X���ǂ���
	if (g_map[ix][iy].knd <= SPR_MAPCHIP1_1 + 1) {
		return FALSE;
	}
	return TRUE;
}

//�J�����̃I�t�Z�b�g���擾����
Vector2DF GetCameraOffset() {
	return g_camera_offset;
}





