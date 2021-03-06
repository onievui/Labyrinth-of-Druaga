#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Sound.h"



//定数の定義
#define FIRE_INI_OFFSET		(60)					//親の座標とのずれ
#define FIRE_DRAW_OFFSET	(160-FIRE_INI_OFFSET)	//描画時の中心座標のずれ

#define FIRE_SPEED			(5)					//炎の増大間隔


//ドラゴンの炎の状態
enum FireState {
	FIRE_STATE_NONE,		//未使用状態
	FIRE_STATE_IN,			//拡大状態
	FIRE_STATE_WAIT,		//待機状態
	FIRE_STATE_OUT,			//縮小状態
	FIRE_STATE_DESTROY		//消滅状態
};



//関数のプロトタイプ宣言
RectF GetFireRect(int sprite_num);
void UpdateFireAnimation(int i, int num);


Fire g_fire[FIRE_MAX];		//ドラゴンの炎オブジェクト
Fire g_prototype_fire;		//ドラゴンの炎のプロトタイプ


//ドラゴンの炎の初期化
void InitializeFire() {

	//データの初期化
	memset(g_fire, 0, sizeof(g_fire));
	
	//プロトタイプの作成
	g_prototype_fire =
	{
		1,
		0,
		{ 0,0 },
		GetFireRect(0),
		NULL,
		NULL,
		TRUE,
		{ g_sprite[SPR_STD_FIRE],1.0,0.0 },
		0
	};
}

//ドラゴンの炎の生成
BOOL CreateFire(Minion *parent) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		//未使用かどうか
		if (!g_fire[i].state) {
			g_fire[i] = g_prototype_fire;
			//親の向きによって向きと座標が変わる
			g_fire[i].pos = parent->pos;
			if (g_fire[i].is_left = parent->is_left) {
				g_fire[i].pos.x -= FIRE_INI_OFFSET;
			}
			else {
				g_fire[i].pos.x += FIRE_INI_OFFSET;
			}
			//親の取得
			g_fire[i].parent = parent;
			//親の速度の取得
			g_fire[i].parent_vel = &parent->vel;

			//効果音を鳴らす
			SetSE(SE_FIRE);

			return TRUE;
		}
	}
	return FALSE;
}

//ドラゴンの炎の更新
void UpdateFire() {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		if (g_fire[i].state) {
			//出現状態なら
			if (g_fire[i].state < FIRE_STATE_DESTROY) {
				//拡大状態なら
				if (g_fire[i].state == FIRE_STATE_IN) {
					//5フレームに1回大きくする
					if (g_fire[i].count % FIRE_SPEED == FIRE_SPEED-1) {
						//アニメーションの更新
						UpdateFireAnimation(i, 1);
						//最大まで大きくなったら待機状態に遷移
						if (g_fire[i].sprite_num == 7) {
							g_fire[i].state = FIRE_STATE_WAIT;
						}
					}
				}
				//待機状態なら
				else if (g_fire[i].state == FIRE_STATE_WAIT) {
					//一定時間経過で縮小状態に遷移
					if (g_fire[i].count == FIRE_SPEED * 8 * 2) {
						g_fire[i].state = FIRE_STATE_OUT;
					}
				}
				//縮小状態なら
				else {
					//5フレームに1回小さくする
					if (g_fire[i].count % FIRE_SPEED == FIRE_SPEED - 1) {
						//アニメーションの更新
						UpdateFireAnimation(i, -1);
						//最小まで小さくなったら消す
						if (g_fire[i].sprite_num == 0) {
							g_fire[i].parent = NULL;
							g_fire[i].state = FIRE_STATE_DESTROY;
						}
					}
				}
				//移動処理
				AddVector2DF(g_fire[i].pos, *g_fire[i].parent_vel);
			}
			//消滅状態なら
			else {
				//最大60フレームで消滅させる
				if (g_fire[i].count >= 60) {
					g_fire[i].state = FIRE_STATE_NONE;
				}
			}
			g_fire[i].count++;
		}
	}
}

//ドラゴンの炎の描画
void DrawFire() {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		if (g_fire[i].state) {
			//向きによって描画時の座標をずらす
			Vector2DF pos = g_fire[i].pos;
			if (g_fire[i].is_left) {
				pos.x -= FIRE_DRAW_OFFSET;
			}
			else {
				pos.x += FIRE_DRAW_OFFSET;
			}
			//消滅中は透明にする
			if (g_fire[i].state == FIRE_STATE_DESTROY) {
				float t = (60 - g_fire[i].count) / 60.0f;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * t * (2-t)));
			}

			//向きによって画像を反転させる
			if (g_fire[i].is_left) {
				DrawTurnGraphicToMap(pos, &g_fire[i].graph);
			}
			else {
				DrawGraphicToMap(pos, &g_fire[i].graph);
			}

			//透明度を元に戻す
			if (g_fire[i].state == FIRE_STATE_DESTROY) {
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			
		}
	}
}

//ドラゴンの炎のサイズ取得
RectF GetFireRect(int sprite_num) {
	RectF ret = { 0,0,0,0 };
	switch (sprite_num) {
	case 0:
		ret = { -32,-5,32,5 };
		break;
	case 1:
		ret = { -32,-13,64,13 };
		break;
	case 2:
		ret = { -32,-17,88,17 };
		break;
	case 3:
		ret = { -32,-25,134,25 };
		break;
	case 4:
		ret = { -32,-29,166,29 };
		break;
	case 5:
		ret = { -32,-29,198,29 };
		break;
	case 6:
		ret = { -32,-29,226,29 };
		break;
	case 7:
		ret = { -32,-29,226,29 };
		break;
	}

	return ret;
}

//ドラゴンの炎のアニメーションの更新
void UpdateFireAnimation(int i, int num) {
	//画像の変更
	g_fire[i].sprite_num += num;
	g_fire[i].graph.sprite.rect = GetSpriteRect(SPR_STD_FIRE, g_fire[i].sprite_num);
	//当たり判定の更新
	g_fire[i].col = GetFireRect(g_fire[i].sprite_num);
	//左右反転させる
	if (g_fire[i].is_left) {
		float tmp = g_fire[i].col.left;
		g_fire[i].col.left = -g_fire[i].col.right;
		g_fire[i].col.right = -tmp;
	}
}

//ドラゴンの炎の当たり判定の設定
void SetFireCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		collider[i].state = &g_fire[i].state;
		collider[i].pos = &g_fire[i].pos;
		collider[i].col = &g_fire[i].col;
		collider[i].vel = NULL;
		collider[i].ride = &g_fire[i].parent_vel;
		collider[i].collision_state = NULL;
		collider[i].ground_flag = NULL;
	}
}

//ドラゴンの炎の親オブジェクトへのポインタの変更
void ChangeFireParentPt(Minion *pre_parent, Minion *new_parent) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		//使用中で対象のIDを持つオブジェクトがあるかどうか
		if (g_fire[i].state && g_fire[i].parent == pre_parent) {
			//親オブジェクトの再設定をする
			g_fire[i].parent = new_parent;
			g_fire[i].parent_vel = &new_parent->vel;
		}
	}
}

//ドラゴンの炎の親が消えたことの通知
void DestroyFire(Minion *parent) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		//使用中で対象のIDを持つオブジェクトがあるかどうか
		if (g_fire[i].state && g_fire[i].parent == parent) {
			//IDを変更して、状態を遷移する
			g_fire[i].parent = NULL;
			g_fire[i].state = FIRE_STATE_DESTROY;
			g_fire[i].count = 0;
		}
	}
}

