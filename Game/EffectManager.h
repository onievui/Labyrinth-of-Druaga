#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//エフェクトの初期化
void InitializeEffects();

//エフェクトの生成
BOOL CreateEffect(EffectPattern knd, Vector2DF *pos, BOOL isLeft);

//エフェクトの更新
void UpdateEffects();

//エフェクトの描画
void DrawEffects();


