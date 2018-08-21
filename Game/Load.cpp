//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Load.cpp
//!
//! @brief  ���\�[�X�̏���
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once



//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Load.h"
#include "GameObjectStruct.h"



//�O���[�o���ϐ��̐錾
HGRP g_texture[GRP_ALL_NUM];
HSND g_se[SE_ALL_NUM];
HSND g_bgm[BGM_ALL_NUM];
int g_shader[SHA_ALL_NUM];
HFNT g_font_g30;
HFNT g_font_g40;
HFNT g_font_g70;
HFNT g_font_g150;

//���\�[�X�̓ǂݍ���
void LoadResources() {
	//�t�H���g�̓ǂݍ���
	// �ǂݍ��ރt�H���g�t�@�C���̃p�X
	LPCSTR font_path = "Resources/Fonts/Protected/GN-Koharuiro_Sunray.ttf";
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	g_font_g30 = CreateFontToHandle("GN-���͂邢��T�����C", 30, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g40 = CreateFontToHandle("GN-���͂邢��T�����C", 40, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g70 = CreateFontToHandle("GN-���͂邢��T�����C", 70, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g150 = CreateFontToHandle("GN-���͂邢��T�����C", 150, 3, DX_FONTTYPE_ANTIALIASING);


	//�摜�̓ǂݍ���
	g_texture[GRP_LOGO1] = LoadGraph("Resources/Textures/Protected/Logo.png");
	g_texture[GRP_LOGO2] = LoadGraph("Resources/Textures/Protected/Logo2.png");
	g_texture[GRP_TITLE] = LoadGraph("Resources/Textures/Protected/title.png");
	g_texture[GRP_TITLE_BG] = LoadGraph("Resources/Textures/Protected/title_bg.png");
	g_texture[GRP_GIL] = LoadGraph("Resources/Textures/Protected/gil.png");
	g_texture[GRP_SWORD] = LoadGraph("Resources/Textures/Protected/sword.png");
	g_texture[GRP_MONSTER] = LoadGraph("Resources/Textures/Protected/monster.png");
	g_texture[GRP_MAPCHIP1] = LoadGraph("Resources/Textures/Protected/mapchip1.png");
	g_texture[GRP_OBJECT_OTHER] = LoadGraph("Resources/Textures/Protected/object_other.png");


	//���ʉ��̓ǂݍ���
	g_bgm[SE_NULL] = LoadSoundMem("Resources/Audio/Protected/NULL");


	//BGM�̓ǂݍ���
	g_bgm[BGM_NULL] = LoadSoundMem("Resources/Audio/Protected/NULL");


	//�V�F�[�_�[�̓ǂݍ���
	g_shader[SHA_WAIPU] = LoadPixelShader("Resources/Shaders/waipu.pso");
}

//�}�b�v�f�[�^�̓ǂݍ���
void LoadMapData(const StageId stageId, MapData *mapdata) {

	//�G���[�`�F�b�N
	if (stageId < 0 || stageId >= STAGE_NUM) {
		MessageBox(NULL, "�}�b�v�̓ǂݍ��݂ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	int i, fp, loop;
	char fname[64];
	sprintf(fname, "Resources/Texts/stage%d_map.dat", stageId + 1);
	int input[64];
	char inputc[64];
	int knd;			//���ݓǂݍ���ł���f�[�^�̎��
	int num;			//�ǂݍ���ł���f�[�^�̌���
	int x, y;			//�}�b�v�p�f�[�^�̓ǂݍ��݈ʒu

	fp = FileRead_open(fname);//�t�@�C���ǂݍ���
	if (fp == NULL) {
		MessageBox(NULL, "�w�肳�ꂽ�}�b�v�f�[�^�����݂��܂���", "", MB_OK);
		return;
	}

	//�ϐ�������
	loop = 1, knd = 0, num = 0, x = 0, y = 0;

	while (loop) {

		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);	//1�����擾����
			if (inputc[i] == '#') {						//�V���[�v������΂��̍s��ǂݔ�΂�
				while (FileRead_getc(fp) != '\n');
				i = -1;
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {	//�J���}�����s�Ȃ炻���܂ł𕶎���Ƃ���
				inputc[i] = '\0';
				break;
			}
			if (input[i] == EOF) {		//�t�@�C���̏I���Ȃ�
				knd = -1;			//�I��
			}
		}
		switch (knd) {
		//�X�e�[�W�̑傫��
		case 0:
			if (num == 0) {
				mapdata->width = atoi(inputc);
				if (mapdata->width > MAP_WIDTH_MAX)
					mapdata->width = MAP_WIDTH_MAX;
				else if (mapdata->width < 1)
					mapdata->width = 1;
				num++;
			}
			else {
				mapdata->height = atoi(inputc);
				if (mapdata->height > MAP_HEIGHT_MAX)
					mapdata->height = MAP_HEIGHT_MAX;
				else if (mapdata->height < 1)
					mapdata->height = 1;
				knd = 1;
				num = 0;
			}

			break;
		//�v���C���[�̏������W
		case 1:
			if (num == 0) {
				mapdata->player_init_pos.x = (float)atof(inputc);
				num++;
			}
			else {
				mapdata->player_init_pos.y = (float)atof(inputc);
				knd = 2;
				num = 0;
			}
			break;
		//����̍��W
		case 2:
			if (num == 0) {
				mapdata->treasure_pos.x = (float)atof(inputc);
				num++;
			}
			else {
				mapdata->treasure_pos.y = (float)atof(inputc);
				knd = 3;
				num = 0;
			}
			break;
		//�}�b�v�f�[�^
		case 3:
			//map_data[x + y*MAP_WIDTH_MAX] = atoi(inputc);
			mapdata->map[x][y].knd = (SPR_ID)atoi(inputc);
			if (input[i] == '\n') {
				x = 0;
				y++;
				if (y == mapdata->height) {
					knd = -1;
				}
			}
			else {
				x++;
				if (x == mapdata->width) {
					while (FileRead_getc(fp) != '\n');
				}
			}
			break;
		case -1:
			loop = 0;
			break;

		}
	}
	FileRead_close(fp);

}

//���\�[�X�̉��
void DeleteResources() {
	//�摜�̍폜
	for (int i = 0; i < GRP_ALL_NUM; i++) {
		DeleteGraph(g_texture[i]);
	}

	//���ʉ��̍폜
	for (int i = 0; i < SE_ALL_NUM; i++) {
		DeleteSoundMem(g_se[i]);
	}

	//BGM�̍폜
	for (int i = 0; i < BGM_ALL_NUM; i++) {
		DeleteSoundMem(g_bgm[i]);
	}

	//�V�F�[�_�[�̍폜
	for (int i = 0; i < SHA_ALL_NUM; i++) {
		DeleteShader(g_shader[i]);
	}
	
	//�t�H���g�̍폜
	DeleteFontToHandle(g_font_g30);
	DeleteFontToHandle(g_font_g40); 
	DeleteFontToHandle(g_font_g70);
	DeleteFontToHandle(g_font_g150);
}