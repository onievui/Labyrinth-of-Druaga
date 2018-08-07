#pragma once




//ヘッダファイルの読み込み
#include "GameEnum.h"
#include "GameObjectStruct.h"




//グローバル変数の初期化
void InitializeMediator();

//選択中のステージの設定
void SetSelectStage(StageId stageId);

//選択中のステージの取得
StageId GetSelectStage();

