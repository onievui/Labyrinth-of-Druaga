#pragma once



//ヘッダファイルの読み込み
#include "GameMain.h"
#include "Shader.h"
#include "GameObjectStruct.h"




//グローバル変数の宣言
int g_timer;					//シェーダー用タイマー

int g_shader_state;				//シェーダーの状態
ShaderPattern now_shader;		//現在使用中のシェーダー

int g_third_screen;				//シェーダー用画面
int g_fourth_screen;			//シェーダー用画面2

GameObject g_waipu_object;		//ワイプエフェクト用オブジェクト

VERTEX2DSHADER vertex[4];		//シェーダ用頂点



//プロトタイプ宣言
void UpdateShader();
void DrawShader();




//シェーダーの初期化
void InitializeShader() {

	g_timer = 0;
	g_shader_state = 0;
	g_third_screen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_fourth_screen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	//背景オブジェクトの初期化
	g_waipu_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_waipu_object.vel = Vector2DF{ 0,0 };
	g_waipu_object.state = 1;
	g_waipu_object.speed = 0;
	g_waipu_object.angle = 0;
	//g_waipu_object.graph = Graph{ g_sprite[******] , 1.0f, 0.0f };

	int i;
	for (i = 0; i < 4; i++) {
		vertex[i].pos = VGet((i % 2)*(float)(SCREEN_WIDTH), (i / 2)*(float)(SCREEN_HEIGHT), 0);
		vertex[i].rhw = 1.0f;
		vertex[i].dif = GetColorU8(255, 255, 255, 255);
		vertex[i].spc = GetColorU8(0, 0, 0, 0);
		vertex[i].u = vertex[i].su = (float)(i % 2);
		vertex[i].v = vertex[i].sv = (float)(i / 2);

	}

}

//シェーダーを使用中かを確認
BOOL UseShaderCheck() {
	if (g_shader_state) {
		switch (now_shader) {
		case SH_PATTERN_WAIPU_A:
			SetDrawScreen(g_third_screen);
			ClearDrawScreen();
			break;
		case SH_PATTERN_WAIPU_B:
			SetDrawScreen(g_third_screen);
			ClearDrawScreen();
			break;
		}
		return TRUE;
	}
	return FALSE;
}

//シェーダー処理
void UseShader() {
	UpdateShader();
	DrawShader();
}

//シェーダーの更新
void UpdateShader() {
	if (g_shader_state) {
		float t;
		switch (now_shader) {
		//消えるワイプエフェクト
		case SH_PATTERN_WAIPU_A:
			SetDrawScreen(g_fourth_screen);
			ClearDrawScreen();
			t = (180 - g_timer)/18.0f;
			DrawRectExtendGraphF(g_waipu_object.pos.x - t * 600, g_waipu_object.pos.y - t * 450, 
				g_waipu_object.pos.x + t * 600, g_waipu_object.pos.y + t * 450,
				g_waipu_object.graph.sprite.rect.left, g_waipu_object.graph.sprite.rect.top, 
				g_waipu_object.graph.sprite.rect.right, g_waipu_object.graph.sprite.rect.bottom,
				g_waipu_object.graph.sprite.texture, TRUE);
			SetDrawScreen(DX_SCREEN_BACK);
			SetUseTextureToShader(0, g_third_screen);
			SetUseTextureToShader(1, g_fourth_screen);
			//3秒で終了
			if (g_timer == 180) {
				g_shader_state = 0;
				
			}
			break;
		//現れるワイプエフェクト
		case SH_PATTERN_WAIPU_B:
			SetDrawScreen(g_fourth_screen);
			ClearDrawScreen();
			t = g_timer / 18.0f;
			DrawRectExtendGraphF(g_waipu_object.pos.x - t * 600, g_waipu_object.pos.y - t * 450, 
				g_waipu_object.pos.x + t * 600, g_waipu_object.pos.y + t * 450,
				g_waipu_object.graph.sprite.rect.left, g_waipu_object.graph.sprite.rect.top, 
				g_waipu_object.graph.sprite.rect.right, g_waipu_object.graph.sprite.rect.bottom,
				g_waipu_object.graph.sprite.texture, TRUE);
			SetDrawScreen(DX_SCREEN_BACK);
			SetUseTextureToShader(0, g_third_screen);
			SetUseTextureToShader(1, g_fourth_screen);
			//3秒で終了
			if (g_timer == 180) {
				g_shader_state = 0;
			}
			break;
		}

		g_timer++;
	}
}

//シェーダーを描画
void DrawShader() {
	if (g_shader_state) {
		SetUsePixelShader(g_shader[now_shader]);
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
	}
}

//シェーダーのセット
void SetShader(ShaderPattern shader) {
	switch (shader) {
	case SH_PATTERN_WAIPU_A:
		now_shader = shader;
		g_shader_state = 1;
		g_timer = 0;
		break;
	case SH_PATTERN_WAIPU_B:
		now_shader = shader;
		g_shader_state = 1;
		g_timer = 0;
		break;
	default:
		MessageBox(NULL, "シェーダーの使用で不正な値が渡されました", "", MB_OK);
		break;
	}
}

//シェーダーの終了処理
void FinalizeShader() {
	//シェーダー用マスクの削除
	DeleteMask(g_third_screen);
	DeleteMask(g_fourth_screen);
}





