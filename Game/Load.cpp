//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Load.cpp
//!
//! @brief  リソースの処理
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once



//ヘッダーファイルの読み込み
#include "Load.h"
#include "GameMain.h"



//グローバル変数の宣言
HGRP g_texture[GRP_ALL_NUM];
HSND g_se[SE_ALL_NUM];
HSND g_bgm[BGM_ALL_NUM];
int g_shader[SHA_ALL_NUM];
HFNT g_font_g30;
HFNT g_font_g40;
HFNT g_font_g70;
HFNT g_font_g150;

//リソースの読み込み
void LoadResources() {
	//フォントの読み込み
	// 読み込むフォントファイルのパス
	LPCSTR font_path = "Resources/Fonts/Protected/GN-Koharuiro_Sunray.ttf";
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	g_font_g30 = CreateFontToHandle("GN-こはるいろサンレイ", 30, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g40 = CreateFontToHandle("GN-こはるいろサンレイ", 40, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g70 = CreateFontToHandle("GN-こはるいろサンレイ", 70, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g150 = CreateFontToHandle("GN-こはるいろサンレイ", 150, 3, DX_FONTTYPE_ANTIALIASING);


	//画像の読み込み
	g_texture[GRP_LOGO1] = LoadGraph("Resources/Textures/Protected/Logo.png");
	g_texture[GRP_LOGO2] = LoadGraph("Resources/Textures/Protected/Logo2.png");
	g_texture[GRP_TITLE] = LoadGraph("Resources/Textures/Protected/title.png");
	g_texture[GRP_TITLE_BG] = LoadGraph("Resources/Textures/Protected/title_bg.png");
	g_texture[GRP_GIL] = LoadGraph("Resources/Textures/Protected/gil.png");
	g_texture[GRP_MAPCHIP1] = LoadGraph("Resources/Textures/Protected/mapchip1.png");



	//効果音の読み込み
	g_bgm[SE_NULL] = LoadSoundMem("Resources/Audio/Protected/NULL");


	//BGMの読み込み
	g_bgm[BGM_NULL] = LoadSoundMem("Resources/Audio/Protected/NULL");


	//シェーダーの読み込み
	g_shader[SHA_WAIPU] = LoadPixelShader("Resources/Shaders/waipu.pso");
}

//リソースの解放
void DeleteResources() {
	//画像の削除
	for (int i = 0; i < GRP_ALL_NUM; i++) {
		DeleteGraph(g_texture[i]);
	}

	//効果音の削除
	for (int i = 0; i < SE_ALL_NUM; i++) {
		DeleteSoundMem(g_se[i]);
	}

	//BGMの削除
	for (int i = 0; i < BGM_ALL_NUM; i++) {
		DeleteSoundMem(g_bgm[i]);
	}

	//シェーダーの削除
	for (int i = 0; i < SHA_ALL_NUM; i++) {
		DeleteShader(g_shader[i]);
	}
	
	//フォントの削除
	DeleteFontToHandle(g_font_g30);
	DeleteFontToHandle(g_font_g40); 
	DeleteFontToHandle(g_font_g70);
	DeleteFontToHandle(g_font_g150);
}