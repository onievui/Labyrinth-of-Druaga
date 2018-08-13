#pragma once



//ヘッダファイルの読み込み
#include "Mediator.h"
#include "GameDefine.h"
#include  <math.h>



//グローバル変数の宣言
BoxCollider g_player_collider[PLAYER_MAX];				//プレイヤーの当たり判定



//プロトタイプ宣言
BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2);



//当たり判定の初期化
void InitializeCollision() {
	OrderSetPlayerCollider(g_player_collider);
}

//当たり判定
void UpdateCollision() {
	
}


////オブジェクトとマップの当たり判定
//BOOL CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
//	int i, j;
//	BoxCollider obj1, obj2;
//	BOOL ret = FALSE;
//	int state = 1;
//	Vector2DF vel2 = { 0,0 };
//	RectF col2 = { -MAPCHIP_SIZE_HALF,-MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF };
//
//	obj1.state = obj2.state = &state;
//	obj1.pos = pos;
//	obj1.vel = vel;
//	obj1.col = col;
//	obj2.vel = &vel2;
//	obj2.col = &col2;
//
//	MapAll mapall = OrderGetMap();	//マップの取得
//
//
//	for (i = 0; i < MAP_WIDTH_MAX; i++) {
//		for (j = 0; j < MAP_HEIGHT_MAX; j++) {
//			if (mapall.map[i][j].knd > SPR_MAPCHIP1_1+1) {
//				obj2.pos = &mapall.map[i][j].pos;
//				if (CollisionMovingAABB(&obj1, &obj2)) {
//					ret = TRUE;
//				}
//			}
//		}
//	}
//
//	return ret;
//}

//オブジェクトとマップの当たり判定
int CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	float tempF;//計算用

	//移動前の座標
	RectF rect0 = {
		pos->x + col->left,
		pos->y + col->top,
		pos->x + col->right - 1,
		pos->y + col->bottom - 1,
	};
	//移動後の座標
	RectF rect1 = {
		vel->x + rect0.left,
		vel->y + rect0.top,
		vel->x + rect0.right,
		vel->y + rect0.bottom,
	};

	//マップ縦横方向判定
	BOOL mL = OrderIsMapPosWall(rect1.left,rect0.top)     || OrderIsMapPosWall(rect1.left, rect0.bottom);
	BOOL mR = OrderIsMapPosWall(rect1.right, rect0.top)   || OrderIsMapPosWall(rect1.right, rect0.bottom);
	BOOL mU = OrderIsMapPosWall(rect0.left, rect1.top)    || OrderIsMapPosWall(rect0.right, rect1.top);
	BOOL mD = OrderIsMapPosWall(rect0.left, rect1.bottom) || OrderIsMapPosWall(rect0.right, rect1.bottom);

	//マップ斜め方向判定
	if (!mL && !mU) { mL = mU = OrderIsMapPosWall(rect1.left, rect1.top); }
	if (!mL && !mD) { mL = mD = OrderIsMapPosWall(rect1.left, rect1.bottom); }
	if (!mR && !mU) { mR = mU = OrderIsMapPosWall(rect1.right, rect1.top); }
	if (!mR && !mD) { mR = mD = OrderIsMapPosWall(rect1.right, rect1.bottom); }

	//座標をブロックの縁に合わせる
	if (mL && !mR) {
		tempF = ceilf(rect1.left / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->left;		//左
		if (pos->x > tempF)pos->x = tempF;
	}
	if (!mL && mR ) {
		tempF = floorf(rect1.right / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->right;	//右
		if (pos->x < tempF)pos->x = tempF;
	}
	if (mU && !mD) {
		tempF = ceilf(rect1.top / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->top;		//上
		if (pos->y > tempF)pos->y = tempF;
	}
	if (!mU && mD) {
		tempF = floorf(rect1.bottom / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->bottom;	//下
		if (pos->y < tempF)pos->y = tempF;
	}

	//判定による加速停止処理
	if (mL) if (vel->x<0)vel->x = 0;
	if (mR) if (vel->x>0)vel->x = 0;
	if (mU) if (vel->y<0)vel->y = 0;
	if (mD) if (vel->y>0)vel->y = 0;

	//１方向でも衝突していたらTRUEを返す
	return mL + mR*2 + mU*4 + mD*8;
}



//オブジェクトと動く矩形同士の当たり判定
//BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
//	Vector2DF vel = *obj1->vel;		//相対速度の計算
//	SubVector2DF(vel, *obj2->vel);
//
//	float xtMin, xtMax, ytMin, ytMax, tMin, tMax;
//	BOOL xFlag, yFlag;
//
//	if (vel.x != 0) {
//		xtMin = (obj2->pos->x - obj1->pos->x - (obj1->col->right - obj2->col->left)) / vel.x;	// X軸についてのtの上限
//		xtMax = (obj2->pos->x - obj1->pos->x + (obj2->col->right - obj1->col->left)) / vel.x;	// X軸についてのtの下限
//		xFlag = TRUE;
//		if (vel.x < 0) {	// 分母の符号が負だった場合の不等号反転への対処
//			float swap = xtMin;
//			xtMin = xtMax;
//			xtMax = swap;
//		}
//	}
//	else {
//		xFlag = FALSE;
//	}
//	
//
//	if (vel.y != 0) {
//		ytMin = (obj2->pos->y - obj1->pos->y - (obj1->col->bottom - obj2->col->top)) / vel.y;	// Y軸についてのtの上限
//		ytMax = (obj2->pos->y - obj1->pos->y + (obj2->col->bottom - obj1->col->top)) / vel.y;	// Y軸についてのtの下限
//		yFlag = TRUE;
//		if (vel.y < 0) {	// 分母の符号が負だった場合の不等号反転への対処
//			float swap = ytMin;
//			ytMin = ytMax;
//			ytMax = swap;
//		}
//	}
//	else {
//		yFlag = FALSE;
//	}
//	
//
//	if (!xFlag) {
//		if (!yFlag) {
//			//return CollisionAABB(obj1, obj2);	//速度0なら通常のAABBを行う
//		}
//		xtMin = ytMin;
//		xtMax = ytMax;
//	}
//	else if (!yFlag) {
//		ytMin = xtMin;
//		ytMax = xtMax;
//	}
//
//	// 下限同士、上限同士で範囲を絞り込む
//	tMin = xtMin > ytMin ? xtMin : ytMin;
//	tMax = xtMax < ytMax ? xtMax : ytMax;
//
//	// tMin < t < tMax と 0 < t < 1 に共通範囲があれば衝突
//	if (tMin < tMax && tMin <= 1 && 0 <= tMax) {
//		// この下にある速度調整処理用にtの下限が0未満の場合は0に設定
//		tMin = tMin < 0 ? 0 : tMin;
//		xtMin = xtMin < 0 ? 0 : xtMin;
//		ytMin = ytMin < 0 ? 0 : ytMin;
//
//		// X軸方向の衝突の場合、速度のX成分のみを補正
//		if (tMin == xtMin) {
//			obj1->vel->x *= tMin;
//			obj2->vel->x *= tMin;
//		}
//		// Y軸方向の衝突の場合、速度のY成分のみを補正
//		if (tMin == ytMin) {
//			obj1->vel->y *= tMin;
//			obj2->vel->y *= tMin;
//		}
//		
//		return TRUE;
//	}
//	return FALSE;
//}


//オブジェクトと動く矩形同士の当たり判定
BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
	Vector2DF vel = *obj1->vel;		//相対速度の計算
	SubVector2DF(vel, *obj2->vel);

	float t, tx, ty;	//衝突するまでの時間
	BOOL xflag, yflag;	//衝突したかの判定

	t = tx = ty = 999;
	xflag = yflag = FALSE;

	Vector2DF point = { obj1->pos->x + obj1->col->left,
						obj1->pos->y + obj1->col->top };
	RectF rect = { obj2->pos->x + obj2->col->left - (obj1->col->right- obj1->col->left),
					obj2->pos->y + obj2->col->top - (obj1->col->bottom - obj1->col->top),
					obj2->pos->x + obj2->col->right,
					obj2->pos->y + obj2->col->bottom };

	//X方向の速度が0でないなら時間を求める
	if (vel.x != 0) {
		float lineX = (vel.x > 0) ? rect.left : rect.right;
		tx = (lineX - point.x) / vel.x;

		if ((tx >= 0) && (tx <= 1.0f)){
			t = tx;
			xflag = TRUE;
		}
		else if (point.x >= rect.left && point.x <= rect.right) {
			xflag = TRUE;
		}
	}
	//X方向の速度が0なら当たっているかを求める
	else {	
		if (point.x >= rect.left && point.x <= rect.right) {
			if (point.x == rect.left || point.x == rect.right) {
				xflag = FALSE;
			}
			else {
				xflag = TRUE;
			}
		}
	}

	//Y方向の速度が0でないなら時間を求める
	if (vel.y != 0) {
		float lineY = (vel.y > 0) ? rect.top : rect.bottom;
		ty = (lineY - point.y) / vel.y;

		if ((ty >= 0) && (ty <= 1.0f)){
			t = t < ty ? t : ty;
			yflag = TRUE;
		}
		else if(point.y >= rect.top && point.y <= rect.bottom) {
			yflag = TRUE;
		}
	}
	//Y方向の速度が0なら当たっているかを求める
	else {
		if (point.y >= rect.top && point.y <= rect.bottom) {
			yflag = TRUE;
		}
	}

	//衝突しているなら
	if (xflag && yflag && t != 999) {
		//X方向に先に衝突したなら
		if (t == tx) {
			obj1->vel->x *= tx;
			obj2->vel->x *= tx;
		}
		//Y方向に先に衝突したなら
		if (t == ty) {
			obj1->vel->y *= ty;
			obj2->vel->y *= ty;
		}
		return TRUE;
	}
	return FALSE;
}
/*
//オブジェクトと動く矩形同士の当たり判定
BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
	Vector2DF vel = *obj1->vel;		//相対速度の計算
	SubVector2DF(vel, *obj2->vel);

	Vector2DF pos1 = *obj1->pos;	//移動後の座標の計算
	Vector2DF pos2 = *obj2->pos;
	AddVector2DF(pos1, *obj1->vel);
	AddVector2DF(pos2, *obj2->vel);

	BOOL ret = FALSE;				//当たったかどうかの判定

	float sinkX, sinkY;				//めりこみ量
	float distX, distY;				//移動前の距離

	//obj1の方が左なら
	if (obj1->pos->x < obj2->pos->x) {
		sinkX = (obj1->col->right - obj2->col->left) - (pos2.x - pos1.x);
		distX = (obj2->pos->x - obj1->pos->x) - (obj1->col->right - obj2->col->left);
	}
	//obj1の方が右なら
	else {
		sinkX = (obj2->col->right - obj1->col->left) - (pos1.x - pos2.x);
		distX = (obj1->pos->x - obj2->pos->x) - (obj2->col->right - obj1->col->left);
	}

	//obj1の方が上なら
	if (obj1->pos->y < obj2->pos->y) {
		sinkY = (obj1->col->bottom - obj2->col->top) - (pos2.y - pos1.y);
		distY = (obj2->pos->y - obj1->pos->y) - (obj1->col->bottom - obj2->col->top);
	}
	//obj1の方が下なら
	else {
		sinkY = (obj2->col->bottom - obj1->col->top) - (pos1.y - pos2.y);
		distY = (obj1->pos->y - obj2->pos->y) - (obj2->col->bottom - obj1->col->top);
	}

	//衝突しているなら
	if (sinkX >= 0 && sinkY >= 0) {
		//obj1->vel->x=
	}
}

//オブジェクトと動く矩形同士の当たり判定
BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
	Vector2DF vel = *obj1->vel;		//相対速度の計算
	SubVector2DF(vel, *obj2->vel);

	Vector2DF pos1 = *obj1->pos;	//移動後の座標の計算
	Vector2DF pos2 = *obj2->pos;
	AddVector2DF(pos1, *obj1->vel);
	AddVector2DF(pos2, *obj2->vel);

	BOOL lrflag = pos1.x < pos2.x;
	BOOL tbflag = pos1.y < pos2.y;

	if (lrflag) {
		if (tbflag) {

		}
	}
}

*/