#pragma once



//ヘッダファイルの読み込み
#include "Mediator.h"
#include "GameDefine.h"
#include  <math.h>



//マクロの定義
//動く矩形の当たり判定を総当たりさせるマクロ
#define MR_COLLISION_MACRO(col1, len1, i, col2, len2, j, check)			\
	for (i = len1 - 1; i >= 0; i--)										\
		if (*col1[i].state)												\
			for (j = len2 - 1; j >= 0; j--)								\
				if (*col2[j].state)										\
					if (check = CollisionMovingAABB(&col1[i], &col2[j]))	

//動く矩形の当たり判定をオブジェクトの数^2/2分ループさせるマクロ
#define MR_COLLISION_MACRO2(col, len, i, j, check)						\
	for (i = 0; i < len - 1; i++)										\
		if (*col[i].state)												\
			for (j = i + 1; j < len; j++)								\
				if (*col[j].state)										\
					if (check = CollisionMovingAABB(&col[i], &col[j]))	



//グローバル変数の宣言
BoxCollider g_player_collider[PLAYER_MAX];			//プレイヤーの当たり判定
BoxCollider g_treasure_collider[TREASURE_MAX];		//お宝の当たり判定	
BoxCollider g_minion_collider[MINION_MAX];			//召喚モンスターの当たり判定


//プロトタイプ宣言
int CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);
int CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2);
BOOL CollisionAABB(Vector2DF *pos1, RectF *col1, Vector2DF *pos2, RectF *col2);



//当たり判定の初期化
void InitializeCollision() {
	OrderSetPlayerCollider(g_player_collider);
	OrderSetTreasureCollider(g_treasure_collider);
	OrderSetMinionsCollider(g_minion_collider);
}

//当たり判定
void UpdateCollision() {

	//ループ用カウンタ
	int i = 0, j = 0;
	//当たり判定用フラグ
	int check = 0;



	//プレイヤーとお宝の当たり判定
	MR_COLLISION_MACRO(g_player_collider, PLAYER_MAX, i, g_treasure_collider, TREASURE_MAX, j, check) {
		//お宝を消す
		OrderCollisionTreasure();
		//お宝を取得した時の処理を行う
		OrderPlayerGetTreasure();
	}
	
	//召喚モンスター同士の当たり判定
	for (i = 0; i < MINION_MAX; i++) {
		*g_minion_collider[i].ride = NULL;
	}
	MR_COLLISION_MACRO2(g_minion_collider, MINION_MAX, i, j, check) {
		if (check & ISGROUND) {
			*g_minion_collider[i].collision_state |= ISGROUND;
			*g_minion_collider[j].collision_state |= ISCEILING;
			*g_minion_collider[i].ride = g_minion_collider[j].vel;
		}
		else if (check & ISCEILING) {
			*g_minion_collider[j].collision_state |= ISGROUND;
			*g_minion_collider[i].collision_state |= ISCEILING;
			*g_minion_collider[j].ride = g_minion_collider[i].vel;
		}
		if (check & ISLEFT) {
			*g_minion_collider[i].collision_state |= ISLEFT;
			*g_minion_collider[j].collision_state |= ISRIGHT;
		}
		else if (check & ISRIGHT) {
			*g_minion_collider[j].collision_state |= ISLEFT;
			*g_minion_collider[i].collision_state |= ISRIGHT;
		}
	}

	//プレイヤーと召喚モンスターの当たり判定
	*g_player_collider->ride = NULL;
	MR_COLLISION_MACRO(g_player_collider, PLAYER_MAX, i, g_minion_collider, MINION_MAX, j, check) {
		if (check & ISGROUND) {
			*g_player_collider->collision_state = TRUE;
			*g_player_collider->ride = g_minion_collider[j].vel;
		}
		else if (check & ISCEILING) {
			*g_minion_collider[j].collision_state = TRUE;
			*g_minion_collider[j].ride = g_minion_collider[i].vel;
		}
		if (check & ISLEFT) {
			*g_minion_collider[j].collision_state |= ISRIGHT;
		}
		else if (check & ISRIGHT) {
			*g_minion_collider[j].collision_state |= ISLEFT;
		}
	}

	//プレイヤーとマップの当たり判定
	if (CollisionObjectMap(g_player_collider->pos, g_player_collider->vel, g_player_collider->col) & ISGROUND) {
		*g_player_collider->ground_flag = TRUE;
	}
	else {
		*g_player_collider->ground_flag = FALSE;
	}

	//お宝とマップの当たり判定
	if (CollisionObjectMap(g_treasure_collider->pos, g_treasure_collider->vel, g_treasure_collider->col) & ISGROUND) {
		*g_treasure_collider->collision_state = TRUE;
	}
	else {
		*g_treasure_collider->collision_state = FALSE;
	}

	//召喚モンスターとマップの当たり判定
	for (i = 0; i < MINION_MAX; i++) {
		if (*g_minion_collider[i].state) {
			*g_minion_collider[i].collision_state |= check = CollisionObjectMap(g_minion_collider[i].pos, g_minion_collider[i].vel, g_minion_collider[i].col);
			if (check & ISGROUND) {
				*g_minion_collider[i].ground_flag = TRUE;
			}
			else {
				//*g_minion_collider[i].ground_flag = FALSE;
			}
		}
	}

	

	

}

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
	BOOL mL = OrderIsWallWithPos(rect1.left,rect0.top)     || OrderIsWallWithPos(rect1.left, rect0.bottom);
	BOOL mR = OrderIsWallWithPos(rect1.right, rect0.top)   || OrderIsWallWithPos(rect1.right, rect0.bottom);
	BOOL mU = OrderIsWallWithPos(rect0.left, rect1.top)    || OrderIsWallWithPos(rect0.right, rect1.top);
	BOOL mD = OrderIsWallWithPos(rect0.left, rect1.bottom) || OrderIsWallWithPos(rect0.right, rect1.bottom);

	//マップ斜め方向判定
	if (!mL && !mU) { mL = mU = OrderIsWallWithPos(rect1.left, rect1.top); }
	if (!mL && !mD) { mL = mD = OrderIsWallWithPos(rect1.left, rect1.bottom); }
	if (!mR && !mU) { mR = mU = OrderIsWallWithPos(rect1.right, rect1.top); }
	if (!mR && !mD) { mR = mD = OrderIsWallWithPos(rect1.right, rect1.bottom); }

	//座標をブロックの縁に合わせる
	if (mL && !mR) {
		tempF = ceilf(rect1.left / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->left;		//左
		if (pos->x > tempF)pos->x = tempF;
		//if (pos->x >= tempF)vel->x = tempF - pos->x;
	}
	if (!mL && mR ) {
		tempF = floorf(rect1.right / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->right;	//右
		if (pos->x < tempF)pos->x = tempF;
		//if (pos->x < tempF)vel->x = tempF - pos->x;
	}
	if (mU && !mD) {
		tempF = ceilf(rect1.top / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->top;		//上
		if (pos->y > tempF)pos->y = tempF;
		//if (pos->y >= tempF)vel->y = tempF - pos->y;
	}
	if ((!mU || vel->y>0) && mD) {
		tempF = floorf(rect1.bottom / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->bottom;	//下
		if (pos->y < tempF)pos->y = tempF;
		//if (pos->y <= tempF)vel->y = tempF - pos->y;
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

//オブジェクトと召喚モンスターの当たり判定
BOOL CollisionObjectMinions(Vector2DF *pos, RectF *col) {
	int i;
	for (i = MINION_MAX - 1; i >= 0; i--) {
		if (*g_minion_collider[i].state) {
			//衝突しているかどうか
			if (CollisionAABB(pos, col, g_minion_collider[i].pos, g_minion_collider[i].col)) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//オブジェクトと召喚モンスターの当たり判定（当たったものは消す）
BOOL CollisionDeleteObjectMinions(Vector2DF *pos, RectF *col) {
	BOOL ret = FALSE;
	int i;
	for (i = MINION_MAX - 1; i >= 0; i--) {
		if (*g_minion_collider[i].state) {
			//衝突しているかどうか
			if (CollisionAABB(pos, col, g_minion_collider[i].pos, g_minion_collider[i].col)) {
				//衝突していたら消滅させる
				OrderDestroyMinion(i);
				ret = TRUE;
			}
		}
	}
	return ret;
}

//動く矩形同士の当たり判定
int CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
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
			/*if (point.x == rect.left || point.x == rect.right) {
				xflag = FALSE;
			}
			else {
				xflag = TRUE;
			}*/
			xflag = TRUE;
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
	if (xflag && yflag) {
		if (t != 999) {
			//X方向に先に衝突したなら
			if (t == tx) {
				if (obj1->vel->x*obj2->vel->x > 0) {
					if (obj1->vel->x > 0) {
						(obj1->pos->x < obj2->pos->x ? obj1->vel->x : obj2->vel->x) *= tx;
					}
					else {
						(obj1->pos->x > obj2->pos->x ? obj1->vel->x : obj2->vel->x) *= tx;
					}
				}
				else {
					obj1->vel->x *= tx;
					obj2->vel->x *= tx;
				}
				//obj1の右側と衝突したなら
				if (obj1->pos->x < obj2->pos->x) {
					return ISRIGHT;
				}
				//obj1の左側と衝突したなら
				else {
					return ISLEFT;
				}
			}
			//Y方向に先に衝突したなら
			if (t == ty) {
				if (obj1->vel->y*obj2->vel->y > 0) {
					if (obj1->vel->y > 0) {
						(obj1->pos->y < obj2->pos->y ? obj1->vel->y : obj2->vel->y) *= ty;
					}
					else {
						(obj1->pos->y > obj2->pos->y ? obj1->vel->y : obj2->vel->y) *= ty;
					}
				}
				else {
					obj1->vel->y *= ty;
					obj2->vel->y *= ty;
				}
				//obj1の下側と衝突したなら
				if (obj1->pos->y < obj2->pos->y) {
					return ISGROUND;
				}
				//obj1の上側と衝突したなら
				else {
					return ISCEILING;
				}
			}
		}
		else {
			if (vel.y == 0) {
				if (obj1->vel->y > 0) {
					(obj1->pos->y < obj2->pos->y ? obj1->vel->y : obj2->vel->y) = 0;
					return ISGROUND;
				}
				else {
					(obj1->pos->y > obj2->pos->y ? obj1->vel->y : obj2->vel->y) = 0;
					return ISCEILING;
				}
			}
		}
		return ISTRUE;
	}
	return FALSE;
}

//動かない矩形同士の当たり判定
BOOL CollisionAABB(Vector2DF *pos1, RectF *col1, Vector2DF *pos2, RectF *col2) {
	if (
		fabsf(pos1->x - pos2->x) < (pos1->x < pos2->x ? col1->right - col2->left : col2->right - col1->left) &&
		fabsf(pos1->y - pos2->y) < (pos1->y < pos2->y ? col1->bottom - col2->top : col2->bottom - col1->top)
		)
	{
		return TRUE;
	}

	return FALSE;
}
