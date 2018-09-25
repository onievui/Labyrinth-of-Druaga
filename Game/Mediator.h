#pragma once




//ヘッダファイルの読み込み
#include "GameObjectStruct.h"




//グローバル変数の初期化
void InitializeMediator();

//選択中のステージの設定
void SetSelectStage(StageId stageId);

//選択中のステージの取得
StageId GetSelectStage();

//プレイ画面のクリア時間の記憶
void SetClearTime(int time);

//プレイ画面のクリア時間の取得
int GetClearTime();

//クリアデータの読み込み依頼
void OrderLoadClearData();

//クリアデータの更新依頼
void OrderWriteClearData();

//クリアデータの取得
AllClearData* GetAllClearData();

//クリアしたステージ数の取得
int GetClearStageNum();

//召喚・消滅範囲表示フラグの設定
void SetUseSummonArea(BOOL flag);

//召喚・消滅範囲表示フラグの取得
BOOL GetUseSummonArea();

//プレイヤーの座標を取得する依頼
Vector2DF OrderGetPlayerPos();

//プレイヤーの座標を設定する依頼
void OrderSetPlayerPos(Vector2DF pos);

//プレイヤーの向きを設定する依頼
void OrderSetPlayerDirection(BOOL isLeft);

//プレイヤーの召喚可能モンスターを設定する依頼
void OrderSetPlayerSummonable(BOOL summonable[]);

//プレイヤーのSPを設定する依頼
void OrderSetPlayerSp(int sp);

//プレイヤーの当たり判定を設定する依頼
void OrderSetPlayerCollider(BoxCollider *collider);

//プレイヤーのSPを回復する依頼
void OrderAddPlayerSp(int plus);

//プレイヤーがお宝を取得したときの処理依頼
void OrderPlayerGetTreasure();

//プレイヤーがダメージ判定と衝突したときの処理依頼
void OrderCollisionPlayer();

//召喚モンスターの生成依頼
int OrderCreateMinion(SummonAreaData *summon_area_data);

//召喚コストの取得依頼
int OrderGetSummonCost(MinionPattern knd);

//召喚モンスターの画像取得依頼
Sprite OrderGetMinionSprite(MinionPattern knd);

//召喚モンスターの当たり判定の設定依頼
void OrderSetMinionsCollider(BoxCollider collider[]);

//召喚モンスターの生成・消滅範囲情報の取得依頼
SummonAreaData OrderGetSummonAreaData(MinionPattern knd, Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft);

//召喚モンスターを消す依頼
void OrderDeleteMinion(SummonAreaData *summon_area_data);

//召喚モンスターのダメージ処理依頼
BOOL OrderDamageMinion(int i, int power);

//召喚モンスターの消滅依頼
void OrderDestroyMinion(int i);

//オーブスポナーの生成依頼
BOOL OrderCreateOrbSpawner(Vector2DF *pos, int sp);

//オーブの当たり判定の設定依頼
void OrderSetOrbsCollider(BoxCollider collider[]);

//オーブの消滅処理依頼
void OrderDestroyOrb(int i);

//ドラゴンの炎の当たり判定の設定依頼
void OrderSetFireCollider(BoxCollider collider[]);

//敵モンスターの生成依頼
BOOL OrderCreateEnemies(EnemyList enemy_list[]);

//敵モンスターの当たり判定の設定依頼
void OrderSetEnemiesCollider(BoxCollider collider[]);

//敵モンスターのダメージ処理依頼
BOOL OrderDamageEnemy(int i, int power);

//敵の魔法の当たり判定の設定依頼
void OrderSetMagicsCollider(BoxCollider collider[]);

//敵の魔法の壁衝突処理依頼
BOOL OrderCollisionMagic(int i);

//敵の魔法の消滅依頼
void OrderDestroyMagic(int i);

//敵の魔法のダメージ量の取得依頼
int OrderGetMagicPower(int i);

//お宝の座標を設定する
void OrderSetTreasurePos(Vector2DF pos);

//お宝の当たり判定を設定する
void OrderSetTreasureCollider(BoxCollider *collider);

//お宝がプレイヤーと衝突したときの処理依頼
void OrderCollisionTreasure();

//エフェクトの生成依頼
BOOL OrderCreateEffect(EffectPattern knd, Vector2DF *pos, BOOL isLeft);

//マップを取得する依頼
MapData OrderGetMap();

//指定した座標をマップ座標に変換する依頼
void OrderGetMapPosWithPos(Vector2DF pos, int *x, int *y);

//指定したマップ座標を座標に変換する依頼
Vector2DF OrderGetPosWithMapPos(int x, int y);

//指定した座標が通過不可マスかどうかの依頼
BOOL OrderIsWallWithPos(float x, float y);

//オブジェクトとマップの当たり判定依頼
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//オブジェクトと召喚モンスターの当たり判定依頼
BOOL OrderCollisionObjectMinions(Vector2DF *pos, RectF *col);

//オブジェクトと召喚モンスターの当たり判定依頼（当たったものは消す）
BOOL OrderCollisionDeleteObjectMinions(Vector2DF *pos, RectF *col);

//オブジェクトと敵モンスターの当たり判定依頼
BOOL OrderCollisionObjectEnemies(Vector2DF *pos, RectF *col);

//カメラのオフセットを取得する依頼
Vector2DF OrderGetCameraOffset();

//マップ外にいるかの判定依頼
BOOL OrderIsOutsideMap(Vector2DF *pos, RectF *col);

//画面下にいるかの判定依頼
BOOL OrderIsUnderMap(Vector2DF *pos, RectF *col);

//画面横にはみ出ないようにする依頼
void OrderClampMap(Vector2DF *pos, RectF *col);


