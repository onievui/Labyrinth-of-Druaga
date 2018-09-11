#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//召喚モンスターの初期化
void InitializeMinions();

//召喚モンスターの生成
int CreateMinion(SummonAreaData *summon_area_data);

//召喚コストの取得
int GetSummonCost(MinionPattern knd);

//召喚モンスターの画像取得
Sprite GetMinionSprite(MinionPattern knd);

//召喚モンスターの更新
void UpdateMinions();

//召喚モンスターの描画
void DrawMinions();

//召喚モンスターの当たり判定の設定
void SetMinionsCollider(BoxCollider collider[]);

//召喚モンスターの生成・消滅範囲情報の取得
SummonAreaData GetSummonAreaData(MinionPattern knd, Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft);

//召喚モンスターを消す
void DeleteMinion(SummonAreaData *summon_area_data);

//召喚モンスターのダメージ処理
BOOL DamageMinion(int i, int power);

//召喚モンスターの消滅
void DestroyMinion(int i);








