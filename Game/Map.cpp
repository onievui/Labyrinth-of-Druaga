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



//�萔�̒�`
#define MAP_WIDTH_NUM	(12)	//�}�b�v�̉���
#define MAP_HEIGHT_NUM	(9)		//�}�b�v�̏c��

#define MAPCHIP_SIZE		(64)	//�}�b�v�`�b�v�̑傫��
#define MAPCHIP_SIZE_HALF	(32)	//�}�b�v�`�b�v�̑傫���̔���

#define MAP_OFFSET_X	(32)	//�}�b�v�̃I�t�Z�b�g
#define MAP_OFFSET_Y	(32)	//�}�b�v�̃I�t�Z�b�g



//�v���g�^�C�v�錾



//�O���[�o���ϐ��̐錾
Map g_map[MAP_WIDTH_NUM][MAP_HEIGHT_NUM];


//�}�b�v�̏�����
void InitializeMap() {
	int i, j;
	for (i = 0; i < MAP_WIDTH_NUM; i++) {
		for (j = 0; j < MAP_HEIGHT_NUM; j++) {
			g_map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_1 + GetRand(10));
			g_map[i][j].pos = Vector2DF{ (float)(i*MAPCHIP_SIZE + MAP_OFFSET_X),(float)(j*MAPCHIP_SIZE + MAP_OFFSET_Y) };
			g_map[i][j].graphp = GraphP{ &g_sprite[g_map[i][j].knd],1.0,0.0 };
		}
	}
}



//�}�b�v�̕`��
void DrawMap() {
	int i, j;
	for (i = 0; i < MAP_WIDTH_NUM; i++) {
		for (j = 0; j < MAP_HEIGHT_NUM; j++) {
			DrawGraphicP(g_map[i][j].pos, &g_map[i][j].graphp);
		}
	}
}

