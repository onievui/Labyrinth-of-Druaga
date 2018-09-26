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
#include "GameObjectStruct.h"



//グローバル変数の宣言
HGRP g_texture[GRP_ALL_NUM];
HSND g_se[SE_ALL_NUM];
HSND g_bgm[BGM_ALL_NUM];
int g_shader[SHA_ALL_NUM];
HFNT g_font_g30;
HFNT g_font_g40;
HFNT g_font_g50;
HFNT g_font_g60;
HFNT g_font_g70;
HFNT g_font_o30;


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
	g_font_g50 = CreateFontToHandle("GN-こはるいろサンレイ", 50, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g60 = CreateFontToHandle("GN-こはるいろサンレイ", 60, 3, DX_FONTTYPE_ANTIALIASING);
	g_font_g70 = CreateFontToHandle("GN-こはるいろサンレイ", 70, 3, DX_FONTTYPE_ANTIALIASING);

	font_path = "Resources/Fonts/Protected/onryou.TTF";
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	g_font_o30 = CreateFontToHandle("怨霊", 30, 3, DX_FONTTYPE_ANTIALIASING);


	//画像の読み込み
	g_texture[GRP_LOGO1]        = LoadGraph("Resources/Textures/Protected/Logo.png");
	g_texture[GRP_LOGO2]        = LoadGraph("Resources/Textures/Protected/Logo2.png");
	g_texture[GRP_TITLE]        = LoadGraph("Resources/Textures/Protected/title.png");
	g_texture[GRP_BG]           = LoadGraph("Resources/Textures/Protected/bg.png");
	g_texture[GRP_GIL]          = LoadGraph("Resources/Textures/Protected/gil.png");
	g_texture[GRP_GIL_SLIME]    = LoadGraph("Resources/Textures/Protected/gil_1_slime.png");
	g_texture[GRP_GIL_GHOST]    = LoadGraph("Resources/Textures/Protected/gil_2_ghost.png");
	g_texture[GRP_GIL_QUOX]     = LoadGraph("Resources/Textures/Protected/gil_3_quox.png");
	g_texture[GRP_SWORD]        = LoadGraph("Resources/Textures/Protected/sword.png");
	g_texture[GRP_SWORD_SLIME]  = LoadGraph("Resources/Textures/Protected/sword_1_slime.png");
	g_texture[GRP_SWORD_GHOST]  = LoadGraph("Resources/Textures/Protected/sword_2_ghost.png");
	g_texture[GRP_SWORD_QUOX]   = LoadGraph("Resources/Textures/Protected/sword_3_quox.png");
	g_texture[GRP_DELETE_ICON]  = LoadGraph("Resources/Textures/Protected/delete_icon.png");
	g_texture[GRP_MONSTER]      = LoadGraph("Resources/Textures/Protected/monster.png");
	g_texture[GRP_DRAGON]       = LoadGraph("Resources/Textures/Protected/dragon.png");
	g_texture[GRP_FIRE]         = LoadGraph("Resources/Textures/Protected/fire.png");
	g_texture[GRP_MAGIC]        = LoadGraph("Resources/Textures/Protected/magic.png");
	g_texture[GRP_MAPCHIP1]     = LoadGraph("Resources/Textures/Protected/mapchip1.png");
	g_texture[GRP_OBJECT_OTHER] = LoadGraph("Resources/Textures/Protected/object_other.png");
	g_texture[GRP_EFFECT1]      = LoadGraph("Resources/Textures/Protected/effect1.png");


	//効果音の読み込み
	g_se[SE_START]         = LoadSoundMem("Resources/Audio/Protected/se_start.wav");
	g_se[SE_CLEAR]         = LoadSoundMem("Resources/Audio/Protected/se_clear.wav");
	g_se[SE_HIGHSCORE]     = LoadSoundMem("Resources/Audio/Protected/se_high_score.wav");
	g_se[SE_PAUSE]         = LoadSoundMem("Resources/Audio/Protected/se_pause.wav");
	g_se[SE_MISS]          = LoadSoundMem("Resources/Audio/Protected/se_miss.wav");
	g_se[SE_WALK]          = LoadSoundMem("Resources/Audio/Protected/se_gil_walk.wav");
	g_se[SE_SWORD]         = LoadSoundMem("Resources/Audio/Protected/se_sword.wav");
	g_se[SE_SUMMON]        = LoadSoundMem("Resources/Audio/Protected/se_summon.wav");
	g_se[SE_ORB]           = LoadSoundMem("Resources/Audio/Protected/se_orb.wav");
	g_se[SE_FIRE]          = LoadSoundMem("Resources/Audio/Protected/se_fire.wav");
	g_se[SE_MINION_STRIKE] = LoadSoundMem("Resources/Audio/Protected/se_minion_strike.wav");
	g_se[SE_MAGIC]         = LoadSoundMem("Resources/Audio/Protected/se_magic.wav");
	g_se[SE_ENEMY_STRIKE]  = LoadSoundMem("Resources/Audio/Protected/se_enemy_strike.wav");
	g_se[SE_ENEMY_GUARD]   = LoadSoundMem("Resources/Audio/Protected/se_enemy_guard.wav");


	//BGMの読み込み
	g_bgm[BGM_TITLE]  = LoadSoundMem("Resources/Audio/Protected/bgm_title.wav");
	g_bgm[BGM_SELECT] = LoadSoundMem("Resources/Audio/Protected/bgm_select.wav");
	g_bgm[BGM_INGAME] = LoadSoundMem("Resources/Audio/Protected/bgm_ingame.wav");


	//シェーダーの読み込み
	g_shader[SHA_WAIPU] = LoadPixelShader("Resources/Shaders/waipu.pso");
}

//クリアデータの読み込み
void LoadClearData(AllClearData *all_clear_data) {

	int i, fp, loop;
	char fname[64] = "Resources/Texts/clear_time.dat";
	int input[64];
	char inputc[64];
	int knd;			//現在読み込んでいるデータの種類
	int num;			//読み込んでいるデータの件数

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		MessageBox(NULL, "クリアデータが存在しません", "", MB_OK);
		return;
	}

	//変数初期化
	loop = 1, knd = 0, num = 0;

	while (loop) {

		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);	//1文字取得する
			if (inputc[i] == '#') {						//シャープがあればその行を読み飛ばす
				while (FileRead_getc(fp) != '\n');
				i = -1;
				continue;
			}
			if (input[i] == '.' || input[i] == '\n') {	//ピリオドか改行ならそこまでを文字列とする
				inputc[i] = '\0';
				break;
			}
			if (input[i] == EOF) {		//ファイルの終わりなら
				knd = -1;			//終了
			}
		}
		switch (knd) {
			//トータルタイム
		case 0:
			//秒
			if (num == 0) {
				all_clear_data->total_second = atoi(inputc);
				num++;
			}
			//小数点以下
			else {
				all_clear_data->total_decimal = atoi(inputc);
				knd = 1;
				num = 0;
			}

			break;
			//各ステージのタイム
		case 1:
			//秒
			if (num % 2 == 0) {
				//クリア済みかを確認
				if (all_clear_data->clear_data[num / 2].second = atoi(inputc)) {
					all_clear_data->clear_data[num / 2].is_clear = TRUE;
				}
				else {
					all_clear_data->clear_data[num / 2].is_clear = FALSE;
				}
			}
			//小数点以下
			else {
				all_clear_data->clear_data[num / 2].decimal = atoi(inputc);
			}
	
			num++;

			//最後のデータなら処理を抜けさせる
			if (num == STAGE_NUM * 2)
				knd = -1;

			break;
		case -1:
			loop = 0;
			break;

		}
	}
	FileRead_close(fp);

}

//クリアデータの更新
void WriteClearData(AllClearData *all_clear_data) {
	
	int i;
	char lines[50][256];
	char fname[256] = "Resources/Texts/clear_time.dat";
	FILE *fp;
	
	fp = fopen(fname, "r");

	if (fp == NULL) {
		MessageBox(NULL, "クリアデータが存在しません", "", MB_OK);
		return;
	}
	else {
		//一行ずつ読み込む
		for (i = 0; i < 50; i++) {
			if (!fgets(lines[i], sizeof(lines[i]), fp))
				break;
		}
		fclose(fp);
		//データの更新
		i = 1;
		sprintf(lines[i], "%d.%02d\n", all_clear_data->total_second, all_clear_data->total_decimal);
		for (i = 0; i < STAGE_NUM; i++) {
			sprintf(lines[3 + i * 2], "%d.%02d\n", all_clear_data->clear_data[i].second, all_clear_data->clear_data[i].decimal);
		}
		//データの出力
		fp = fopen(fname, "w");
		if (fp == NULL) {
			MessageBox(NULL, "クリアデータが存在しません", "", MB_OK);
			return;
		}
		for (i = 0; i < STAGE_NUM * 2 + 2; i++) {
			fprintf(fp, lines[i]);
		}
		fclose(fp);
	}
}


//マップデータの読み込み
void LoadMapData(const StageId stageId, MapData *mapdata) {

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
		//プレイヤーの初期座標、向き
		case 1:
			if (num == 0) {
				mapdata->player_pos.x = (float)atof(inputc);
				num++;
			}
			else if (num == 1) {
				mapdata->player_pos.y = (float)atof(inputc);
				num++;
			}
			else {
				mapdata->player_is_left = atoi(inputc);
				knd = 2;
				num = 0;
			}
			break;
		//お宝の座標
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
		//召喚可能なモンスター
		case 3:
			mapdata->summonable[num] = atoi(inputc);
			num++;
			if (input[i] == '\n' || num == MINION_PATTERN_NUM) {
				knd = 4;
				num = 0;
			}

			break;
		//初期SP
		case 4:
			mapdata->player_sp = atoi(inputc);
			knd = 5;
			break;
		//マップデータ
		case 5:
			mapdata->map[x][y].knd = (SPR_ID)atoi(inputc);
			if (input[i] == '\n') {
				x = 0;
				y++;
				if (y == mapdata->height) {
					knd = 6;
				}
			}
			else {
				x++;
				if (x == mapdata->width) {
					while (FileRead_getc(fp) != '\n');
					x = 0;
					y++;
					if (y == mapdata->height) {
						knd = 6;
					}
				}
			}
			if (mapdata->width == 0) {
				break;
			}
			break;
		//敵モンスター出現データ
		case 6:
			switch (num % 4) {
			//種類
			case 0:
				mapdata->enemy_list[num / 4].is_use = TRUE;
				mapdata->enemy_list[num / 4].knd = (EnemyPattern)atoi(inputc);
			//X座標
			case 1:
				mapdata->enemy_list[num / 4].pos.x = (float)atoi(inputc);
				break;
			//Y座標
			case 2:
				mapdata->enemy_list[num / 4].pos.y = (float)atoi(inputc);
				break;
			//向き
			case 3:
				mapdata->enemy_list[num / 4].is_left = atoi(inputc);
				break;
			}
			num++;
			//最大登録数に到達したら処理を抜けさせる
			if (num == ENEMY_MAX * 4)
				knd = -1;
			break;
		case -1:
			loop = 0;
			break;

		}
	}
	FileRead_close(fp);

}

//ガイドデータの読み込み
void LoadGuideData(const StageId stageId, Guide guide[]) {

	//エラーチェック
	if (stageId < 0 || stageId >= STAGE_NUM) {
		MessageBox(NULL, "マップの読み込みで不正な値が渡されました", "", MB_OK);
		return;
	}

	int i, fp, loop;
	char fname[64];
	sprintf(fname, "Resources/Texts/guide_data/stage%d_guide.dat", stageId + 1);
	int input[64];
	char inputc[64];
	int knd;			//現在読み込んでいるデータの種類
	int num;			//読み込んでいるデータの件数
	
	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		//ガイドがないときは処理しない
		return;
	}

	//変数初期化
	loop = 1, knd = 0, num = 0;

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
			//ガイドのX座標
		case 0:
			guide[num].state = 1;
			guide[num].pos.x = (float)atof(inputc);
			knd++;
			break;
			//ガイドのY座標
		case 1:
			guide[num].pos.y = (float)atof(inputc);
			knd++;
			break;
			//ガイドのテキスト
		case 2:
			strcpy(guide[num].text, inputc);
			knd++;
			break;
			//文字色
		case 3:
			guide[num].color = (unsigned int)strtol(inputc, NULL, 16);
			knd++;
			break;
			//フォント
		case 4:
			switch (atoi(inputc)) {
				//怨霊 30
			case 0:
				guide[num].font = g_font_o30;
				break;
			default:
				MessageBox(NULL, "フォントの指定で不正な値が渡されました", "", MB_OK);
				break;
			}
			knd = 0;
			num++;
			//最大登録数に到達したら処理を抜けさせる
			if (num == GUIDE_MAX)
				knd = -1;
			break;
		case -1:
			//ループを抜ける
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
	DeleteFontToHandle(g_font_g50);
	DeleteFontToHandle(g_font_g60);
	DeleteFontToHandle(g_font_g70);
	DeleteFontToHandle(g_font_o30);
}