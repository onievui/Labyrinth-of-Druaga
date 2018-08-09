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
#include "GameMain.h"



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
	g_texture[GRP_MAPCHIP1] = LoadGraph("Resources/Textures/Protected/mapchip1.png");



	//���ʉ��̓ǂݍ���
	g_bgm[SE_NULL] = LoadSoundMem("Resources/Audio/Protected/NULL");


	//BGM�̓ǂݍ���
	g_bgm[BGM_NULL] = LoadSoundMem("Resources/Audio/Protected/NULL");


	//�V�F�[�_�[�̓ǂݍ���
	g_shader[SHA_WAIPU] = LoadPixelShader("Resources/Shaders/waipu.pso");
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