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
	GRP_TITLE_BG,			//タイトル背景
	GRP_STAGESELECT_BG,		//ステージセレクト背景
	GRP_STAGESELECT_ICON,	//ステージセレクトアイコン
	GRP_ALL_NUM,			//読み込む画像ファイルの数
};

//効果音のID
enum SE_ID {
	SE_NULL,		//仮の効果音
	SE_ALL_NUM,		//読み込む効果音ファイルの数
};

//BGMのID
enum BGM_ID {
	BGM_NULL,		//仮のBGM
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
extern HFNT g_font_g70;
extern HFNT g_font_g150;

//リソースの読み込み
void LoadResources();

//リソースの解放
void DeleteResources();
