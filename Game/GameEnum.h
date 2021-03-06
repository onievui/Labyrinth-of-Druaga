#pragma once


//外部に公開する列挙体の定義



// シーンID
enum SceneId {
	SCENE_NONE = -1,	//シーン未選択
	SCENE_LOGO,			//ロゴシーン
	SCENE_TITLE,		//タイトルシーン
	SCENE_STAGESELECT,	//ステージセレクトシーン
	SCENE_PLAY,			//プレイシーン
	SCENE_RESULT,		//リザルトシーン
	SCENE_NUM,			//未選択を含まないシーン数
};

//ステージの種類
enum StageId {
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_6,
	STAGE_7,
	STAGE_8,
	STAGE_9,
	STAGE_10,
	STAGE_11,
	STAGE_12,
	STAGE_13,
	STAGE_14,
	STAGE_15,
	STAGE_16,
	STAGE_17,
	STAGE_18,
	STAGE_19,
	STAGE_20,
	STAGE_NUM,
};

//プレイヤーの状態
enum PlayerState {
	PLAYER_STATE_MISS,		//ミス状態
	PLAYER_STATE_STAND,		//立ち状態
	PLAYER_STATE_JUMP,		//ジャンプ状態
	PLAYER_STATE_SUMMON,	//召喚状態
	PLAYER_STATE_CLEAR,		//クリア状態
	PLAYER_STATE_NUM,		//プレイヤーの状態の種類数
};

//召喚モンスターの種類
enum MinionPattern {
	MINION_SLIME,			//スライム
	MINION_GHOST,			//ゴースト
	MINION_QUOX,			//クオックス（ドラゴン）
	MINION_PATTERN_NUM,		//召喚モンスターの種類数
};

//敵モンスターの種類
enum EnemyPattern {
	ENEMY_DRUID,			//ドルイド（マジシャン）
	ENEMY_WIZARD,			//ウィザード（マジシャン）
	ENEMY_PATTERN_NUM		//敵モンスターの種類数
};

//モンスターの魔法の種類
enum MagicPattern {
	MAGIC_WHITE,			//通常魔法
	MAGIC_GREEN,			//貫通魔法
	MAGIC_PATTERN_NUM		//モンスターの魔法の種類数
};

//エフェクトの種類
enum EffectPattern {
	EFFECT_GET_ORB,			//オーブ取得エフェクト
	EFFECT_PATTERN_NUM		//エフェクトの種類数
};


