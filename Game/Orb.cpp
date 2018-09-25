#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"
#include "Sound.h"
#include <math.h>



//定数の定義
#define ORB_SPAWNER_MAX				(8)		//オーブスポナーの最大出現数
#define ORB_SPAWNER_SPEED			(6)		//オーブの生成間隔

#define ORB_APPEAR_ROTATE_SPEED		(8)		//オーブの出現した時の回転間隔
#define ORB_MOVE_ROTATE_SPEED		(5)		//オーブの追尾中の回転間隔

#define ORB_APPEAR_SPEED			(2)		//オーブが出現したときの速度
#define ORB_MOVE_SPEED				(18)	//オーブがプレイヤーに向かうときの速度

#define ORB_APPEAR_TIME				(30)	//オーブの出現状態が終わるまでの時間


//オーブの状態
enum OrbState {
	ORB_STATE_NONE,		//未使用状態
	ORB_STATE_APPEAR,	//出現状態
	ORB_STATE_CHASE,	//追尾状態
};



OrbSpawner g_orb_spawner[ORB_SPAWNER_MAX];	//オーブスポナーオブジェクト
OrbSpawner g_prototype_orb_spawner;			//オーブスポナーのプロトタイプ

Orb g_orb[ORB_MAX];			//オーブオブジェクト
Orb g_prototype_orb;		//オーブのプロトタイプ


//オーブの初期化
void InitializeOrbs() {

	//データの初期化
	memset(g_orb_spawner, 0, sizeof(g_orb_spawner));
	memset(g_orb, 0, sizeof(g_orb));

	//プロトタイプの作成
	g_prototype_orb_spawner =
	{
		1,
		0,
		{ 0,0 },
		0
	};

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

//オーブスポナーの生成
BOOL CreateOrbSpawner(Vector2DF *pos, int sp) {
	int i;
	for (i = 0; i < ORB_SPAWNER_MAX; i++) {
		//未使用かどうか
		if (!g_orb_spawner[i].state) {
			g_orb_spawner[i] = g_prototype_orb_spawner;
			g_orb_spawner[i].pos = *pos;
			g_orb_spawner[i].sp = sp;
			return TRUE;
		}
	}
	return FALSE;
}

//オーブの生成
BOOL CreateOrb(Vector2DF *pos, int sp) {
	int i;
	for (i = 0; i < ORB_SPAWNER_MAX; i++) {
		//未使用かどうか
		if (!g_orb[i].state) {
			g_orb[i] = g_prototype_orb;
			g_orb[i].pos = *pos;
			g_orb[i].sp = sp;
			g_orb[i].angle = GetRand(10000) / 10000.0f*PI2;
			return TRUE;
		}
	}
	return FALSE;
}

//オーブスポナーの更新
void UpdateOrbSpawner() {
	int i;
	for (i = 0; i < ORB_SPAWNER_MAX; i++) {
		if (g_orb_spawner[i].state) {
			//オーブの生成周期なら
			if (g_orb_spawner[i].count%ORB_SPAWNER_SPEED == 0) {
				//オーブを生成する
				CreateOrb(&g_orb_spawner[i].pos, 1);
				//残りSPを減らす
				g_orb_spawner[i].sp--;
				//残りSPがなくなったら消滅する
				if (g_orb_spawner[i].sp <= 0) {
					g_orb_spawner[i].state = 0;
				}
			}
			g_orb_spawner[i].count++;
		}
	}
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