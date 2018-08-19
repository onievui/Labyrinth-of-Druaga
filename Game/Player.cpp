//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  プレイヤーオブジェクトの処理
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//ヘッダーファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"
#include "Key.h"
#include <math.h>



//プロトタイプ宣言
void ActPlayer();
void PlayerActDead();
void PlayerActStand();
void PlayerActJump();
void PlayerActSummon();
void PlayerActClear();
void AnimatePlayer();


//グローバル変数の宣言
Player g_player;


//プレイヤーの初期化
void InitializePlayer() {
	g_player.state = PLAYER_STATE_STAND;
	g_player.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT-100 };
	g_player.col = RectF{ -14,-31,14,31 };
	g_player.vel = Vector2DF{ 0,0 };
	g_player.is_left = TRUE;
	g_player.is_ground = FALSE;
	g_player.sprite_num = 6;
	g_player.graph = Graph{ g_sprite[SPR_STD_GIL],1.0,0.0 };
	g_player.anime_count = 0;
	
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, 6);
}


//プレイヤーの更新
void UpdatePlayer() {
	if (g_player.state) {
		//プレイヤーの行動
		ActPlayer();
		//プレイヤーのアニメーション
		AnimatePlayer();
	}
}


//プレイヤーの行動
void ActPlayer() {

	//移動量を座標に足す
	AddVector2DF(g_player.pos, g_player.vel);

	//プレイヤーの状態で分岐する
	switch (g_player.state) {
		//死んでいるなら
	case PLAYER_STATE_DEAD:
		PlayerActDead();
		break;
		//立っているなら
	case PLAYER_STATE_STAND:
		PlayerActStand();
		break;
		//ジャンプしている（空中にいる）なら
	case PLAYER_STATE_JUMP:
		PlayerActJump();
		break;
		//召喚しているなら
	case PLAYER_STATE_SUMMON:
		PlayerActSummon();
		break;
		//クリアしているなら
	case PLAYER_STATE_CLEAR:
		PlayerActClear();
		break;
		//エラーチェック
	default:
		MessageBox(NULL, "プレイヤーのアニメーションで不正な値が渡されました", "", MB_OK);
		break;
	}

	//重力を加える
	g_player.vel.y += GRAVITY;

	//マップとの当たり判定
	if (OrderCollisionObjectMap(&g_player.pos, &g_player.vel, &g_player.col) & ISGROUND) {
		g_player.is_ground = TRUE;
	}
	else {
		g_player.is_ground = FALSE;
	}



}

//プレイヤーの死に状態
void PlayerActDead() {

}

//プレイヤーの立ち状態
void PlayerActStand() {
	//横方向の移動
	switch (CheckStateKeyLater(KEY_INPUT_LEFT, KEY_INPUT_RIGHT)) {
	//移動していないならアニメーションをしない
	case 0:
		g_player.vel.x = 0;
		g_player.anime_count = 0;
		break;
	case 1:
		g_player.vel.x = -PLAYER_WALK_SPEED;
		g_player.is_left = TRUE;
		g_player.anime_count++;
		break;
	case 2:
		g_player.vel.x = PLAYER_WALK_SPEED;
		g_player.is_left = FALSE;
		g_player.anime_count++;
		break;
	default:
		MessageBox(NULL, "プレイヤー入力エラー", "", MB_OK);
		break;
	}
	//ジャンプしたなら上方向に加速してジャンプ状態に遷移する
	if (CheckHitKeyDown(KEY_INPUT_Z) && g_player.is_ground) {
		g_player.state = PLAYER_STATE_JUMP;
		g_player.vel.y = PLAYER_JUMP_SPEED;
	}
	//空中にいたならジャンプ状態にする
	else if (!g_player.is_ground) {
		g_player.state = PLAYER_STATE_JUMP;
	}
}

//プレイヤーのジャンプ状態
void PlayerActJump() {
	//横方向の移動
	switch (CheckStateKeyLater(KEY_INPUT_LEFT, KEY_INPUT_RIGHT)) {
		//移動していないならアニメーションをしない
	case 0:
		g_player.vel.x = 0;
		break;
	case 1:
		g_player.vel.x = -PLAYER_WALK_SPEED;
		g_player.is_left = TRUE;
		break;
	case 2:
		g_player.vel.x = PLAYER_WALK_SPEED;
		g_player.is_left = FALSE;
		break;
	default:
		MessageBox(NULL, "プレイヤー入力エラー", "", MB_OK);
		break;
	}
	//地上にいたなら立ち状態にする
	if (g_player.is_ground) {
		g_player.state = PLAYER_STATE_STAND;
	}
}

//プレイヤーの召喚状態
void PlayerActSummon() {

}

//プレイヤーのクリア状態
void PlayerActClear() {
	g_player.anime_count++;
}

//プレイヤーのアニメーション
void AnimatePlayer() {

	//新しいスプライト番号
	int sprite_num;	

	//プレイヤーの状態で分岐する
	switch (g_player.state) {
	//死んでいるなら
	case PLAYER_STATE_DEAD:
		break;
	//立っているなら
	case PLAYER_STATE_STAND:
		//左向き
		if (g_player.is_left) {
			if (g_player.anime_count % 12 < 6) {
				sprite_num = 6;
			}
			else {
				sprite_num = 7;
			}
		}
		//右向き
		else {
			if (g_player.anime_count % 12 < 6) {
				sprite_num = 4;
			}
			else {
				sprite_num = 5;
			}
		}
		break;
	//ジャンプしている（空中にいる）なら
	case PLAYER_STATE_JUMP:
		//左向き
		if (g_player.is_left) {
			sprite_num = 7;
		}
		//右向き
		else {
			sprite_num = 5;
		}
		break;
	//召喚しているなら
	case PLAYER_STATE_SUMMON:
		break;
	//クリア状態なら
	case PLAYER_STATE_CLEAR:
		if (g_player.is_ground) {
			sprite_num = ((g_player.anime_count % 30) < 15);
		}
		else {
			sprite_num = g_player.sprite_num;
		}
		break;
	//エラーチェック
	default:
		MessageBox(NULL, "プレイヤーのアニメーションで不正な値が渡されました", "", MB_OK);
		break;
	}

	//スプライトが変更されかどうか
	if (g_player.sprite_num != sprite_num) {
		//スプライト番号の変更
		g_player.sprite_num = sprite_num;
		//スプライトの変更
		g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
	}
}

//プレイヤーの描画
void DrawPlayer() {
	if (g_player.state) {
		DrawGraphicToMap(g_player.pos, &g_player.graph);
		//RectF rect = { g_player.pos.x + g_player.col.left,
		//	g_player.pos.y + g_player.col.top,
		//	g_player.pos.x + g_player.col.right,
		//	g_player.pos.y + g_player.col.bottom };
		//DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);
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

//プレイヤーの地面判定を設定する
void SetPlayerIsGround(BOOL isGround) {
	g_player.is_ground = isGround;
}

//プレイヤーの当たり判定を設定する
void SetPlayerCollider(BoxCollider *collider) {
	collider->state = (int*)&g_player.state;
	collider->pos = &g_player.pos;
	collider->vel = &g_player.vel;
	collider->col = &g_player.col;
}

//プレイヤーがお宝を取得したときの処理
void PlayerGetTreasure() {
	g_player.state = PLAYER_STATE_CLEAR;
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

