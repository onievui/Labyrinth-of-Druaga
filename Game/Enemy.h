#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"






//敵モンスターのプロトタイプの初期化
void InitializePrototypeEnemy(Enemy proto_enemy[]);

//ドルイドの更新
void UpdateEnemyDruid(Enemy *enemy);

//ウィザードの更新
void UpdateEnemyWizard(Enemy *enemy);

//ドルイドの描画
void DrawEnemyDruid(Enemy *enemy);

//ウィザードの描画
void DrawEnemyWizard(Enemy *enemy);

//ドルイドのダメージ処理
BOOL DamageEnemyDruid(Enemy *enemy, int power);

//ウィザードのダメージ処理
BOOL DamageEnemyWizard(Enemy *enemy, int power);

//ドルイドの消滅
void DestroyEnemyDruid(Enemy *enemy);

//ウィザードの消滅
void DestroyEnemyWizard(Enemy *enemy);



