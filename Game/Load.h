//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Load.h
//!
//! @brief  リソースのヘッダファイル
//!
//! @date   2018/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once



//定数の定義

//画像のID
enum GRP_ID {
	GRP_LOGO1,				//ロゴ画像1
	GRP_LOGO2,				//ロゴ画像2
	GRP_TITLE,				//タイトル画像
	GRP_BG,					//背景画像
	GRP_STAGESELECT_BG,		//ステージセレクト背景
	GRP_STAGESELECT_ICON,	//ステージセレクトアイコン
	GRP_GIL,				//プレイヤー画像
	GRP_SWORD,				//剣画像
	GRP_MONSTER,			//モンスター画像
	GRP_DRAGON,				//ドラゴン画像
	GRP_FIRE,				//ドラゴンの炎画像
	GRP_MAGIC,				//モンスター魔法画像
	GRP_MAPCHIP1,			//マップチップ画像1
	GRP_OBJECT_OTHER,		//その他オブジェクト画像
	GRP_ALL_NUM,			//読み込む画像ファイルの数
};

//効果音のID
enum SE_ID {
	SE_START,			//ステージ開始効果音
	SE_CLEAR,			//ステージクリア効果音
	SE_HIGHSCORE,		//ハイスコア効果音
	SE_PAUSE,			//ポーズ効果音
	SE_MISS,			//ミス効果音
	SE_WALK,			//歩き効果音
	SE_SWORD,			//剣効果音
	SE_SUMMON,			//召喚効果音
	SE_FIRE,			//ドラゴンの炎効果音
	SE_MINION_STRIKE,	//召喚モンスター消滅効果音
	SE_MAGIC,			//敵の魔法効果音
	SE_ENEMY_STRIKE,	//敵モンスター消滅効果音
	SE_ALL_NUM,			//読み込む効果音ファイルの数
};

//BGMのID
enum BGM_ID {
	BGM_TITLE,		//タイトルBGM
	BGM_SELECT,		//ステージセレクトBGM
	BGM_INGAME,		//プレイ中BGM
	BGM_ALL_NUM,	//読み込むBGMファイルの数
};

//シェーダーのID
enum SHADER_ID {
	SHA_WAIPU,		//ワイプシェーダー
	SHA_ALL_NUM,	//読み込むシェーダーの数
};

//グローバル変数の宣言
extern HGRP g_texture[GRP_ALL_NUM];
extern HSND g_se[SE_ALL_NUM];
extern HSND g_bgm[BGM_ALL_NUM];
extern int g_shader[SHA_ALL_NUM];
extern HFNT g_font_g30;
extern HFNT g_font_g40;
extern HFNT g_font_g50;
extern HFNT g_font_g60;
extern HFNT g_font_g70;

//リソースの読み込み
void LoadResources();

//リソースの解放
void DeleteResources();
