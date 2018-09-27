#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"


//プロトタイプ宣言
extern void LoadGuideData(const StageId stageId, Guide guide[]);


Guide g_guide[GUIDE_MAX];		//ガイドオブジェクト



//ガイドの初期化
void InitializeGuide() {

	//データの初期化
	memset(g_guide, 0, sizeof(g_guide));

	//ガイドデータの読み込み
	LoadGuideData(GetSelectStage(), g_guide);
	
	//座標の設定
	int i;
	for (i = 0; i < GUIDE_MAX; i++) {
		if (g_guide[i].state) {
			MulVector2DF(g_guide[i].pos, MAPCHIP_SIZE);
			AddVector2DF(g_guide[i].pos, Vector2DF{ MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF });
		}
	}
}



//ガイドの描画
void DrawGuide() {
	int i;
	Vector2DF pos;
	for (i = 0; i < GUIDE_MAX; i++) {
		if (g_guide[i].state) {
			pos = g_guide[i].pos;
			SubVector2DF(pos, OrderGetCameraOffset());
			DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_guide[i].font, "%s", g_guide[i].text) / 2,
				pos.y, g_guide[i].color, g_guide[i].font, "%s", g_guide[i].text);
		}
	}
}

