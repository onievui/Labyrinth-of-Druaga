//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  プレイヤーオブジェクトの処理
//!
//! @date   2018/08/09
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//ヘッダーファイルの読み込み
#include "GameObjectStruct.h"
#include "GameDefine.h"
#include "Player.h"
#include "Mediator.h"
#include "Key.h"
#include <math.h>



//プロトタイプ宣言
void MovePlayer();
void AnimatePlayer();


//グローバル変数の宣言
Player g_player;


//プレイヤーの初期化
void InitializePlayer() {
	g_player.state = 1;
	g_player.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT-100 };
	g_player.col = RectF{ -14,-31,14,31 };
	g_player.vel = Vector2DF{ 0,0 };
	g_player.speed = 5;
	g_player.is_left = TRUE;
	g_player.sprite_num = 6;
	g_player.graph = Graph{ g_sprite[SPR_STD_GIL],1.0,0.0 };
	g_player.anime_count = 0;
	
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, 6);
}


//プレイヤーの更新
void UpdatePlayer() {
	if (g_player.state) {
		//プレイヤーの移動
		MovePlayer();
		//プレイヤーのアニメーション
		AnimatePlayer();
	}
}


//プレイヤーの移動
void MovePlayer() {
	
	//速度の初期化
	//g_player.vel = Vector2DF{ 0,0 };
	//移動後の座標
	Vector2DF next_pos = Vector2DF{ g_player.pos.x,g_player.pos.y };
	

	//横方向の移動
	switch (CheckStateKeyLater(KEY_INPUT_LEFT, KEY_INPUT_RIGHT)) {
	case 0:
		g_player.vel.x = 0;
		break;
	case 1:
		//AddVector2DF(g_player.vel, Vector2DF{ -g_player.speed,0 });
		g_player.vel.x = -g_player.speed;
		g_player.is_left = TRUE;
		g_player.anime_count++;
		break;
	case 2:
		//AddVector2DF(g_player.vel, Vector2DF{ g_player.speed,0 });
		g_player.vel.x = g_player.speed;
		g_player.is_left = FALSE;
		g_player.anime_count++;
		break;
	default:
		MessageBox(NULL, "プレイヤー入力エラー", "", MB_OK);
		break;
	}

	if (CheckHitKeyDown(KEY_INPUT_Z)) {
		g_player.vel.y -= 25;
	}

	g_player.vel.y += 2.4f;

	if (g_player.pos.y + g_player.col.top > FIELD_HEIGHT) {
		g_player.pos.y -= FIELD_HEIGHT;
	}

	////縦方向の移動
	//switch (CheckStateKeyLater(KEY_INPUT_UP, KEY_INPUT_DOWN)) {
	//case 0:
	//	break;
	//case 1:
	//	AddVector2DF(g_player.vel, Vector2DF{ 0,-g_player.speed });
	//	ud_flag = true;
	//	break;
	//case 2:
	//	AddVector2DF(g_player.vel, Vector2DF{ 0,g_player.speed });
	//	ud_flag = true;
	//	break;
	//default:
	//	MessageBox(NULL, "プレイヤー入力エラー", "", MB_OK);
	//	break;
	//}


	//マップとの当たり判定
	OrderCollisionObjectMap(&g_player.pos, &g_player.vel, &g_player.col);


	//移動量を座標に足す
	AddVector2DF(g_player.pos, g_player.vel);

	//移動範囲外なら座標を端に戻す
	/*if (next_pos.x - g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate < 0) {
		g_player.pos.x = 0 + g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate;
	}
	else if (next_pos.x + g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate > FIELD_WIDTH) {
		g_player.pos.x = FIELD_WIDTH - g_player.graph.sprite.rect.right / 2 * g_player.graph.exrate;

	}
	else {
		g_player.pos.x = next_pos.x;
	}
	if (next_pos.y - g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate < 0) {
		g_player.pos.y = 0 + g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate;
	}
	else if (next_pos.y + g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate > FIELD_HEIGHT) {
		g_player.pos.y = FIELD_HEIGHT - g_player.graph.sprite.rect.bottom / 2 * g_player.graph.exrate;
	}
	else {
		g_player.pos.y = next_pos.y;
	}*/

}

//プレイヤーのアニメーション
void AnimatePlayer() {
	//歩いているなら
	if (g_player.state == 1) {
		//左向き
		if (g_player.is_left) {
			if (g_player.anime_count % 12 < 6) {
				g_player.sprite_num = 6;
			}
			else {
				g_player.sprite_num = 7;
			}
		}
		//右向き
		else {
			if (g_player.anime_count % 12 < 6) {
				g_player.sprite_num = 4;
			}
			else {
				g_player.sprite_num = 5;
			}
		}
	}
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
}

//プレイヤーの描画
void DrawPlayer() {
	if (g_player.state==1) {
		DrawGraphic(g_player.pos, &g_player.graph);
		RectF rect = { g_player.pos.x + g_player.col.left,
			g_player.pos.y + g_player.col.top,
			g_player.pos.x + g_player.col.right,
			g_player.pos.y + g_player.col.bottom };
		DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);
	}
}

//プレイヤーの座標を取得する
Vector2DF GetPlayerPos() {
	return g_player.pos;
}

//プレイヤーの座標を設定する
void SetPlayerPos(Vector2DF pos) {
	g_player.pos = pos;
}


//プレイヤーの当たり判定を設定する
void SetPlayerCollider(BoxCollider *collider) {
	collider->state = &g_player.state;
	collider->pos = &g_player.pos;
	collider->vel = &g_player.vel;
	collider->col = &g_player.col;
}

//プレイヤーが敵と衝突したときの処理
//void CollisionPlayer() {
//	//無敵状態なら処理しない
//	if (g_player.state == 2) {
//		return;
//	}
//	g_player.state = 0;
//	SetSE(SE_MISS);
//	OrderCreateEffect(EFF_PATTERN_2, g_player.pos);
//	//コンティニューの確認
//	RequestContinue();
//}

