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
#include "GameObjectStruct.h"



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

//マップデータの読み込み
void LoadMapData(const StageId stageId, int map_data[], int *width, int *height, int player_pos[]) {
	
	//エラーチェック
	if (stageId < 0 || stageId >= STAGE_NUM) {
		MessageBox(NULL, "マップの読み込みで不正な値が渡されました", "", MB_OK);
		return;
	}

	int i, fp, loop;
	char fname[64];
	sprintf(fname, "Resources/Texts/stage%d_map.dat", stageId + 1);
	int input[64];
	char inputc[64];
	int knd;			//現在読み込んでいるデータの種類
	int num;			//読み込んでいるデータの件数
	int x, y;			//マップ用データの読み込み位置

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		MessageBox(NULL, "指定されたマップデータが存在しません", "", MB_OK);
		return;
	}
	
	//変数初期化
	loop = 1, knd = 0, num = 0, x = 0, y = 0;

	while (loop) {

		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);	//1文字取得する
			if (inputc[i] == '#') {						//シャープがあればその行を読み飛ばす
				while (FileRead_getc(fp) != '\n');
				i = -1;
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {	//カンマか改行ならそこまでを文字列とする
				inputc[i] = '\0';
				break;
			}
			if (input[i] == EOF) {		//ファイルの終わりなら
				knd = -1;			//終了
			}
		}
		switch (knd) {
		//ステージの大きさ
		case 0:
			if (num == 0) {
				*width = atoi(inputc);
				if (*width > MAP_WIDTH_MAX)
					*width = MAP_WIDTH_MAX;
				num++;
			}
			else {
				*height = atoi(inputc);
				if (*height > MAP_HEIGHT_MAX)
					*height = MAP_HEIGHT_MAX;
				knd = 1;
				num = 0;
			}
			
			break;
		//プレイヤーの初期座標
		case 1:
			if (num == 0) {
				player_pos[0] = atoi(inputc);
				num++;
			}
			else {
				player_pos[1] = atoi(inputc);
				knd = 2;
				num = 0;
			}
			break;
		//マップデータ
		case 2:
			map_data[x+y*MAP_WIDTH_MAX]= atoi(inputc);
			if (input[i] == '\n') {
				x = 0;
				y++;
				if (y == *height) {
					knd = -1;
				}
			}
			else {
				x++;
				if (x == *width) {
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