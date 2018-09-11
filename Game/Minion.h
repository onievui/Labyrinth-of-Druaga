#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"




//召喚モンスターのプロトタイプの初期化
void InitializePrototypeMinion(Minion proto_minion[], SummonData s_data[]);

//スライムの更新
void UpdateMinionSlime(Minion *minion);

//ゴーストの更新
void UpdateMinionGhost(Minion *minion);

//クオックスの更新
void UpdateMinionQuox(Minion *minion);

//スライムの描画
void DrawMinionSlime(Minion *minion);

//ゴーストの描画
void DrawMinionGhost(Minion *minion);

//クオックスの描画
void DrawMinionQuox(Minion *minion);

//スライムのダメージ処理
BOOL DamageMinionSlime(Minion *minion, int power);

//ゴーストのダメージ処理
BOOL DamageMinionGhost(Minion *minion, int power);

//クオックスのダメージ処理
BOOL DamageMinionQuox(Minion *minion, int power);

//スライムの消滅
void DestroyMinionSlime(Minion *minion, SummonData *s_dat);

//ゴーストの消滅
void DestroyMinionGhost(Minion *minion, SummonData *s_dat);

//クオックスの消滅
void DestroyMinionQuox(Minion *minion, SummonData *s_dat);

