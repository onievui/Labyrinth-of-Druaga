#pragma once




//当たり判定の初期化
void InitializeCollision();

//当たり判定の更新
void UpdateCollision();

//オブジェクトとマップの当たり判定
int CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);






