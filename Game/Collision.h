#pragma once




//当たり判定の初期化
void InitializeCollision();

//当たり判定の更新
void UpdateCollision();

//オブジェクトとマップの当たり判定
int CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//オブジェクトと召喚モンスターの当たり判定
BOOL CollisionObjectMinions(Vector2DF *pos, RectF *col);

//オブジェクトと召喚モンスターの当たり判定（当たったものは消す）
BOOL CollisionDeleteObjectMinions(Vector2DF *pos, RectF *col);

//オブジェクトと敵モンスターの当たり判定
BOOL CollisionObjectEnemies(Vector2DF *pos, RectF *col);





