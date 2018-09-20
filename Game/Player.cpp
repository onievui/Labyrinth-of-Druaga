//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  プレイヤーオブジェクトの処理
//!
//! @date   2018/09/15
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//ヘッダーファイルの読み込み
#include "GameObjectStruct.h"
#include "ScenePlay.h"
#include "Mediator.h"
#include "Key.h"
#include "Sound.h"
#include <math.h>



//定数の定義
#define SP_POS_X			(670)	//SPの表示X座標
#define SP_POS_Y			(10)	//SPの表示Y座標
#define SLIST_POS_X			(50)	//召喚可能なモンスターのリストの表示X座標
#define SLIST_POS_Y			(40)	//召喚可能なモンスターのリストの表示Y座標
#define SLIST_DIST_X		(70)	//召喚可能なモンスターのリストのX方向の間隔
#define SUMMON_FAILED_TIME	(32)	//召喚に失敗したときの待ち時間

#define KEY_INPUT_JUMP		(KEY_INPUT_Z)		//ジャンプキー
#define KEY_INPUT_SUMMON	(KEY_INPUT_X)		//召喚/消滅キー
#define KEY_INPUT_SELECT	(KEY_INPUT_LSHIFT)	//召喚モンスター選択キー
#define KEY_INPUT_S_AREA	(KEY_INPUT_A)		//召喚・消滅範囲表示キー


//プロトタイプ宣言
void ActPlayer();
void PlayerActMiss();
void PlayerActStand();
void PlayerActJump();
void PlayerActSummon();
void PlayerActClear();
void AnimatePlayer();
void SummonMinion();
void PlayerMiss(BOOL is_damage);



//グローバル変数の宣言
Player g_player;									//プレイヤーオブジェクト
Graph g_sword;										//剣オブジェクト
int g_summon_time;									//召喚動作に必要な時間
SummonableList g_summonable[MINION_PATTERN_NUM+1];	//召喚可能なモンスターのリスト
int g_slist_active_num;								//リストで使用中の要素数
int g_select_summon_type;							//選択中の召喚タイプ
SummonAreaData g_summon_area;						//召喚・消滅範囲情報
BOOL g_use_summon_area;								//召喚・消滅範囲表示フラグ
BOOL g_is_walking;									//今回歩いたかどうか
BOOL g_was_walking;									//前回歩いたかどうか
BOOL g_is_damage;									


extern HFNT g_font_g40;



//プレイヤーの初期化
void InitializePlayer() {
	g_player.state = PLAYER_STATE_STAND;
	g_player.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT-100 };
	g_player.col = RectF{ -14,-31,14,31 };
	g_player.vel = Vector2DF{ 0,0 };
	g_player.ride = NULL;
	g_player.is_left = TRUE;
	g_player.is_ground = FALSE;
	g_player.sp = 20;
	g_player.sprite_num = 6;
	g_player.graph = Graph{ g_sprite[SPR_STD_GIL],1.0,0.0 };
	g_player.anime_count = 0;
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, 6);

	g_sword = Graph{ g_sprite[SPR_STD_SWORD],1.0,0.0 };
	g_sword.sprite.rect = GetSpriteRect(SPR_STD_SWORD, 6);

	g_summon_time = 0;
	memset(g_summonable, 0, sizeof(g_summonable));
	g_summonable[0].is_use = TRUE;
	g_summonable[0].knd = MINION_PATTERN_NUM;
	g_summonable[0].graph = Graph{ g_sprite[SPR_DELETE_ICON],1.0,0.0 };
	g_slist_active_num = 1;
	g_select_summon_type = 0;
	memset(&g_summon_area, 0, sizeof(g_summon_area));
	g_use_summon_area = GetUseSummonArea();

	g_is_walking = FALSE;
	g_was_walking = FALSE;

	g_is_damage = FALSE;
}


//プレイヤーの更新
void UpdatePlayer() {
	//プレイヤーが生きている場合
	if (g_player.state) {
		//プレイヤーの行動
		ActPlayer();
		//マップの横に出ないようにする
		OrderClampMap(&g_player.pos, &g_player.col);
		//マップでの死亡判定
		if (OrderIsUnderMap(&g_player.pos,&g_player.col)) {
			PlayerMiss(FALSE);
		}
		//召喚・消滅範囲の表示切替
		if (CheckHitKeyDown(KEY_INPUT_S_AREA)) {
			g_use_summon_area = !g_use_summon_area;
			SetUseSummonArea(g_use_summon_area);
		}
	}
	//プレイヤーが死んでいる場合
	else {
		PlayerActMiss();
	}
	//プレイヤーのアニメーション
	AnimatePlayer();

	//歩き始めたら効果音を鳴らす
	if (g_is_walking && !g_was_walking) {
		SetSE(SE_WALK);
	}
	//歩いてないなら効果音を止める
	else if (!g_is_walking && g_was_walking) {
		StopSE(SE_WALK);
	}
	//フラグの更新
	g_was_walking = g_is_walking;
	g_is_walking = FALSE;


}


//プレイヤーの行動
void ActPlayer() {

	//移動量を座標に足す
	AddVector2DF(g_player.pos, g_player.vel);

	//着地していたなら速度を0にする
	if (g_player.is_ground && g_player.vel.y > 0) {
		g_player.vel.y = 0;
	}

	//召喚・消滅範囲情報の取得
	g_summon_area = OrderGetSummonAreaData(g_summonable[g_select_summon_type].knd, &g_player.pos, &g_player.col, g_player.is_left);

	//プレイヤーの状態で分岐する
	switch (g_player.state) {
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

	//乗っているオブジェクトの速度を加える
	if (g_player.ride) {
		AddVector2DF(g_player.vel, *g_player.ride);
	}

	//マップとの着地判定の適用
	g_player.is_ground = g_player.ground_flag;

	//召喚タイプの選択
	if (CheckHitKeyDown(KEY_INPUT_SELECT)) {
		g_select_summon_type = (g_select_summon_type + 1) % g_slist_active_num;
	}

}

//プレイヤーのミス状態
void PlayerActMiss() {
	//上に飛んで落下する
	if (g_player.anime_count == 0) {
		//落下死なら飛ばない
		if (g_is_damage) {
			g_player.vel.y = PLAYER_JUMP_SPEED*1.5f;
		}
	}
	else {
		g_player.vel.y += GRAVITY;
	}

	//移動量を座標に足す
	AddVector2DF(g_player.pos, g_player.vel);

	g_player.vel.x = 0;
	g_player.anime_count++;
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
		g_is_walking = TRUE;
		break;
	case 2:
		g_player.vel.x = PLAYER_WALK_SPEED;
		g_player.is_left = FALSE;
		g_player.anime_count++;
		g_is_walking = TRUE;
		break;
	default:
		MessageBox(NULL, "プレイヤー入力エラー", "", MB_OK);
		break;
	}

	//召喚したなら召喚状態に遷移する
	if (CheckHitKeyDown(KEY_INPUT_SUMMON)) {
		g_player.state = PLAYER_STATE_SUMMON;
		SummonMinion();
		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//ジャンプしたなら上方向に加速してジャンプ状態に遷移する
	else if (CheckHitKeyDown(KEY_INPUT_JUMP) && g_player.is_ground) {
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
	if (CheckHitKeyDown(KEY_INPUT_SUMMON)) {
		g_player.state = PLAYER_STATE_SUMMON;
		SummonMinion();
		g_player.vel.x = 0;
		g_player.anime_count = 0;
	}
	//地上にいたなら立ち状態にする
	else if (g_player.is_ground) {
		g_player.state = PLAYER_STATE_STAND;
	}
}

//プレイヤーの召喚状態
void PlayerActSummon() {
	g_player.vel.x = 0;
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
	case PLAYER_STATE_MISS:
		sprite_num = g_player.sprite_num;
		g_player.graph.angle += PI2 / 20.0f;
		break;
	//立っているなら
	case PLAYER_STATE_STAND:
		//左向き
		if (g_player.is_left) {
			if ((g_player.anime_count+5) % 12 < 6) {
				sprite_num = 6;
			}
			else {
				sprite_num = 7;
			}
		}
		//右向き
		else {
			if ((g_player.anime_count + 5) % 12 < 6) {
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
		//召喚状態のときはプレイヤーのスプライトを変更しない
		if (g_player.state != PLAYER_STATE_SUMMON) {
			//スプライトの変更
			g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
		}
		//剣スプライトの変更
		g_sword.sprite.rect = GetSpriteRect(SPR_STD_SWORD, g_player.sprite_num);
	}
}

//モンスターの召喚処理
void SummonMinion() {
	//消滅モードでないなら召喚
	if (g_summonable[g_select_summon_type].knd != MINION_PATTERN_NUM) {
		//召喚コストの取得
		int cost = OrderGetSummonCost(g_summonable[g_select_summon_type].knd);
		//SPが足りるかの確認
		if (g_player.sp >= cost) {
			//召喚に失敗してもモーションを行う
			if (!(g_summon_time = OrderCreateMinion(&g_summon_area))) {
				g_summon_time = SUMMON_FAILED_TIME;
			}
			//成功したらSPを減らす
			else {
				g_player.sp -= cost;
			}
		}
		//召喚に失敗してもモーションを行う
		else {
			g_summon_time = SUMMON_FAILED_TIME;
			SetSE(SE_SWORD);
		}
	}
	//モンスターの消滅処理
	else {
		OrderDeleteMinion(&g_summon_area);
		g_summon_time = SUMMON_FAILED_TIME;
		SetSE(SE_SWORD);
	}
}

//プレイヤーの描画
void DrawPlayer() {
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

//プレイヤー関係の情報の描画
void DrawPlayerUI() {
	//SPの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(SP_POS_X - 10, SP_POS_Y, SP_POS_X + 100, SP_POS_Y + 35, COLOR_AQUA, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatStringFToHandle(SP_POS_X, SP_POS_Y, COLOR_BLUE, g_font_g40, "SP:%d", g_player.sp);

	//召喚可能なモンスターのリストの描画
	int i;
	for (i = 0; i < g_slist_active_num; i++) {
		int index = (g_select_summon_type + i) % g_slist_active_num;
		//先頭は大きく表示する
		g_summonable[index].graph.exrate = (i == 0) ? 1.0f : 0.75f;
		//表示位置
		Vector2DF pos = { (float)(SLIST_POS_X + i * SLIST_DIST_X),(float)(SLIST_POS_Y) };
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		//枠の描画
		DrawBoxAA(pos.x - 32 * g_summonable[index].graph.exrate,
			pos.y - 32 * g_summonable[index].graph.exrate,
			pos.x + 32 * g_summonable[index].graph.exrate,
			pos.y + 32 * g_summonable[index].graph.exrate,
			COLOR_WHITE,
			TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//消滅モードはモンスターの画像を表示しない
		if (index != 0) {
			//召喚コストの取得
			int cost = OrderGetSummonCost(g_summonable[index].knd);
			int r, g, b;
			//コスト不足なら
			if (cost > g_player.sp) {
				GetDrawBright(&r, &g, &b);
				SetDrawBright(r * 2 / 5, g * 2 / 5,b * 2 / 5);
			}
			DrawGraphic(pos, &g_summonable[index].graph);
			float exrate = g_summonable[index].graph.exrate;
			DrawFormatStringFToHandle(pos.x + 15 * exrate, pos.y + 8 * exrate, COLOR_YELLOW, g_font_g30, "%d", cost);
			if (cost > g_player.sp) {
				SetDrawBright(r, g, b);
			}
		}
		//消滅アイコンの描画
		else {
			g_summonable[index].graph.exrate *= 0.8f;
			DrawGraphic(pos, &g_summonable[index].graph);
		}
	}

	//召喚・消滅範囲情報の描画
	if (g_use_summon_area) {
		if (g_player.state == PLAYER_STATE_STAND || g_player.state == PLAYER_STATE_JUMP) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
			int color = g_summon_area.state == 0 ? COLOR_BLUE : COLOR_RED;
			Vector2DF pos = g_summon_area.pos;
			SubVector2DF(pos, OrderGetCameraOffset());
			DrawBoxAA(pos.x + g_summon_area.area.left,
				pos.y + g_summon_area.area.top,
				pos.x + g_summon_area.area.right,
				pos.y + g_summon_area.area.bottom,
				color,
				TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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

//プレイヤーの向きを設定する
void SetPlayerDirection(BOOL isLeft) {
	g_player.is_left = isLeft;
	//スプライトの変更
	g_player.sprite_num = (isLeft ? 6 : 4);
	g_player.graph.sprite.rect = GetSpriteRect(SPR_STD_GIL, g_player.sprite_num);
	
}

//プレイヤーの召喚可能モンスターを設定する
void SetPlayerSummonable(BOOL summonable[]) {
	int i;
	for (i = 0; i < MINION_PATTERN_NUM; i++) {
		if (g_summonable[g_slist_active_num].is_use = summonable[i]) {
			g_summonable[g_slist_active_num].knd = MinionPattern(i);
			g_summonable[g_slist_active_num].graph = { g_sprite[SPR_STD_MONSTER],1.0,0.0 };
			g_summonable[g_slist_active_num].graph.sprite = OrderGetMinionSprite(MinionPattern(i));
			g_slist_active_num++;
		}
	}
}

//プレイヤーのSPを設定する
void SetPlayerSp(int sp) {
	g_player.sp = sp;
}

//プレイヤーの当たり判定を設定する
void SetPlayerCollider(BoxCollider *collider) {
	collider->state = (int*)&g_player.state;
	collider->pos = &g_player.pos;
	collider->col = &g_player.col;
	collider->vel = &g_player.vel;
	collider->ride = &g_player.ride;
	collider->collision_state = &g_player.is_ground;
	collider->ground_flag = &g_player.ground_flag;
}

//プレイヤーのSPを回復する
void AddPlayerSp(int plus) {
	g_player.sp += plus;
}

//プレイヤーがお宝を取得したときの処理
void PlayerGetTreasure() {
	//プレイヤーをクリア状態にする
	g_player.state = PLAYER_STATE_CLEAR;
	g_player.anime_count = 0;
	//ステージクリアの通知
	RequestStageClear();
}

//プレイヤーが死んだ時の処理
void PlayerMiss(BOOL is_damage) {
	//演出を行うかの判定
	g_is_damage = is_damage;
	//プレイヤーをミス状態にする
	g_player.state = PLAYER_STATE_MISS;
	g_player.anime_count = 0;
	//ステージ失敗の通知
	RequestStageFailed();
}

//プレイヤーがダメージ判定と衝突したときの処理
void CollisionPlayer() {
	//死んだときの処理を呼び出す
	PlayerMiss(TRUE);
}
