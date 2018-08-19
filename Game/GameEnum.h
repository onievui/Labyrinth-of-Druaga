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
	STAGE_NUM,
};

//プレイヤーの状態
enum PlayerState {
	PLAYER_STATE_DEAD,		//死に状態
	PLAYER_STATE_STAND,		//立ち状態
	PLAYER_STATE_JUMP,		//ジャンプ状態
	PLAYER_STATE_SUMMON,	//召喚状態
	PLAYER_STATE_CLEAR,		//クリア状態
	PLAYER_STATE_NUM,		//プレイヤーの状態の種類数
};







