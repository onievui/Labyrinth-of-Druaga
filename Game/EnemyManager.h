#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//敵モンスターの初期化
void InitializeEnemies();

//敵モンスターの生成
BOOL CreateEnemy(MonsterList *enemy_list);

//敵モンスターの更新
void UpdateEnemies();

//敵モンスターの描画
void DrawEnemies();

//敵モンスターの当たり判定の設定
void SetEnemiesCollider(BoxCollider collider[]);

//敵モンスターのダメージ処理
BOOL DamageEnemy(int i, int power);

//敵モンスターの消滅
void DestroyEnemy(int i);

