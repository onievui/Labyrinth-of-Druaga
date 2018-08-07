#pragma once




//ヘッダファイルの読み込み
#include "Mediator.h"




//グローバル変数の宣言
static StageId g_select_stage;	//選択中のステージ




//グローバル変数の初期化
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	
}

//選択中のステージの設定
void SetSelectStage(StageId stageId) {
	g_select_stage = stageId;
}

//選択中のステージの取得
StageId GetSelectStage() {
	return g_select_stage;
}

