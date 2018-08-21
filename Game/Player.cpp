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
#include "ScenePlay.h"
#include "Mediator.h"
#include "Key.h"
#include <math.h>



//定数の定義
#define SUMMON_FAILED_TIME	(32)	//召喚に失敗したときの待ち時間


//プロトタイプ宣言
void ActPlayer();
void PlayerActDead();
void PlayerActStand();
void PlayerActJump();
void PlayerActSummon();
void PlayerActClear();
void AnimatePlayer();


//グローバル変数の宣言
Player g_player;		//プレイヤーオブジェクト
Graph g_sword;			//剣オブジェクト
int g_summon_time;		//召喚動作に必要な時間


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

	g_sword = Graph{ g_sprite[SPR_STD_SWORD],1.0,0.0 };

	g_sword.sprite.rect = GetSpriteRect(SPR_STD_SWORD, 6);

	g_summon_time = 0;
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
	//召喚したなら召喚状態に遷移する
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		g_player.state = PLAYER_STATE_SUMMON;
		if (!(g_summon_time = OrderCreateMinion(MINION_SLIME, g_player.pos, g_player.is_left))) {
			g_summon_time = SUMMON_FAILED_TIME;
		}
		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//ジャンプしたなら上方向に加速してジャンプ状態に遷移する
	else if (CheckHitKeyDown(KEY_INPUT_Z) && g_player.is_ground) {
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
	//召喚したなら召喚状態に遷移する
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		g_player.state = PLAYER_STATE_SUMMON;
		if (!(g_summon_time = OrderCreateMinion(MINION_SLIME, g_player.pos, g_player.is_left))) {
			g_summon_time = SUMMON_FAILED_TIME;
		}		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//地上にいたなら立ち状態にする
	else if (g_player.is_ground) {
		g_player.state = PLAYER_STATE_STAND;
	}
}

//プレイヤーの召喚状態
void PlayerActSummon() {
	//召喚中
	if (g_summon_time > g_player.anime_count) {
		g_player.anime_count++;
	}
	//終了処理
	else {
		if (g_player.is_ground) {
			g_player.state = PLAYER_STATE_STAND;
		}
		else {
			g_player.state = PLAYER_STATE_JUMP;
		}
		g_player.anime_count = 0;
	}
}

//プレイヤーのクリア状態
void PlayerActClear() {
	g_player.vel.x = 0;
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
		sprite_num = g_player.anime_count * 16 / g_summon_time;
		//逆向きにアニメーションさせる
		if (sprite_num >= 8) {
			sprite_num = 15 - sprite_num;
		}
		//画像の都合で調整
		if (sprite_num >= 6) {
			sprite_num = sprite_num == 6 ? 7 : 6;
		}
		//向きによって変える
		sprite_num += g_player.is_left ? 24 : 32;
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
		//召喚状態でないときはプレイヤーのスプライトを変更しない
		if (g_player.state != PLAYER_STATE_SUMMON) {
			//スプライトの変更
			g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
		}
		//剣スプライトの変更
		g_sword.sprite.rect = GetSpriteRect(SPR_STD_SWORD, g_player.sprite_num);
	}
}

//プレイヤーの描画
void DrawPlayer() {
	if (g_player.state) {
		//向きによって表示順を変える
		if (g_player.is_left && g_player.state != PLAYER_STATE_CLEAR) {
			DrawGraphicToMap(g_player.pos, &g_sword);
			DrawGraphicToMap(g_player.pos, &g_player.graph);
		}
		else {
			DrawGraphicToMap(g_player.pos, &g_player.graph);
			DrawGraphicToMap(g_player.pos, &g_sword);
		}
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
	//プレイヤーをクリア状態にする
	g_player.state = PLAYER_STATE_CLEAR;
	//ステージクリアの通知
	RequestStageClear();
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

