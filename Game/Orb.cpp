#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"
#include "Sound.h"
#include <math.h>



//定数の定義
#define ORB_APPEAR_ROTATE_SPEED		(8)		//オーブの出現した時の回転間隔
#define ORB_MOVE_ROTATE_SPEED		(5)		//オーブの追尾中の回転間隔

#define ORB_APPEAR_SPEED			(2)		//オーブが出現したときの速度
#define ORB_MOVE_SPEED				(16)	//オーブがプレイヤーに向かうときの速度

#define ORB_APPEAR_TIME				(30)	//オーブの出現状態が終わるまでの時間


//オーブの状態
enum OrbState {
	ORB_STATE_NONE,		//未使用状態
	ORB_STATE_APPEAR,	//出現状態
	ORB_STATE_CHASE,	//追尾状態
};



Orb g_orb[ORB_MAX];		//オーブオブジェクト
Orb g_prototype_orb;	//オーブのプロトタイプ


//オーブの初期化
void InitializeOrbs() {

	//データの初期化
	memset(g_orb, 0, sizeof(g_orb));

	//プロトタイプの作成
	g_prototype_orb =
	{
		ORB_STATE_APPEAR,
		0,
		{ 0,0 },
		{-20,-20,20,20},
		{ 0,0 },
		0,
		1,
		{ g_sprite[SPR_STD_MONSTER],0.75,0.0 },
		33
	};
	g_prototype_orb.graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_prototype_orb.sprite_num);
}

//オーブの生成
BOOL CreateOrb(Vector2DF *pos, int sp) {
	int i, j;
	BOOL ret;

	//回復量分ループ
	for (i = 0; i < sp; i++) {
		for (j = 0; j < ORB_MAX; j++) {
			//未使用かどうか
			if (!g_orb[j].state) {
				g_orb[j] = g_prototype_orb;
				g_orb[j].pos = *pos;
				g_orb[j].angle = PI2 * GetRand(10000) / 10000.0f;
				ret = TRUE;
				break;
			}
		}
	}
	return ret;
}

//オーブの更新
void UpdateOrbs() {
	int i;
	for (i = 0; i < ORB_MAX; i++) {
		if (g_orb[i].state) {
			
			//座標に速度を足す
			AddVector2DF(g_orb[i].pos, g_orb[i].vel);

			//出現状態の時
			if (g_orb[i].state == ORB_STATE_APPEAR) {
				float t = g_orb[i].count * 1.0f / ORB_APPEAR_TIME;
				t = t*(2 - t);
				CalcVector2DF(g_orb[i].vel, ORB_APPEAR_SPEED * t, g_orb[i].angle);
				//回転アニメーション
				if (g_orb[i].count % ORB_APPEAR_ROTATE_SPEED == ORB_APPEAR_ROTATE_SPEED - 1) {
					g_orb[i].graph.angle += PI / 2;
				}
			}
			//追尾状態の時
			else {
				Vector2DF pos = OrderGetPlayerPos();
				g_orb[i].angle = atan2f(pos.y - g_orb[i].pos.y, pos.x - g_orb[i].pos.x);
				CalcVector2DF(g_orb[i].vel, ORB_MOVE_SPEED, g_orb[i].angle);
				//回転アニメーション
				if (g_orb[i].count % ORB_MOVE_ROTATE_SPEED == ORB_MOVE_ROTATE_SPEED - 1) {
					g_orb[i].graph.angle += PI / 2;
				}
			}
			
			//出現状態が終わったら追尾状態にする
			if (g_orb[i].count == ORB_APPEAR_TIME) {
				g_orb[i].state = ORB_STATE_CHASE;
			}

			g_orb[i].count++;
		}
	}
}

//オーブの描画
void DrawOrbs() {
	int i;
	for (i = 0; i < ORB_MAX; i++) {
		if (g_orb[i].state) {
			DrawGraphicToMap(g_orb[i].pos, &g_orb[i].graph);
		}
	}
}

//オーブの当たり判定の設定
void SetOrbsCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < ORB_MAX; i++) {
		collider[i].state = &g_orb[i].state;
		collider[i].pos = &g_orb[i].pos;
		collider[i].col = &g_orb[i].col;
		collider[i].vel = &g_orb[i].vel;
	}
}

//オーブの消滅処理
void DestroyOrb(int i) {
	//SPを回復させる
	OrderAddPlayerSp(g_orb[i].sp);
	g_orb[i].state = ORB_STATE_NONE;
	SetSE(SE_ORB);
}