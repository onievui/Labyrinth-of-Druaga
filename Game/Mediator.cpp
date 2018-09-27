#pragma once




//ヘッダファイルの読み込み
#include "Mediator.h"
#include "Map.h"
#include "Player.h"
#include "MinionManager.h"
#include "Orb.h"
#include "Fire.h"
#include "EnemyManager.h"
#include "MagicManager.h"
#include "Treasure.h"
#include "EffectManager.h"
#include "Collision.h"



//グローバル変数の宣言
static StageId g_select_stage;			//選択中のステージ
static int g_clear_time;				//ステージクリアまでの時間
static BOOL g_use_summon_area;			//召喚・消滅範囲表示フラグ
static AllClearData g_all_clear_data;		//ステージのクリア情報


extern void LoadClearData(AllClearData *all_clear_data);
extern void WriteClearData(AllClearData *all_clear_data);



//グローバル変数の初期化
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	g_clear_time = -1;
	g_use_summon_area = FALSE;
	memset(&g_all_clear_data, 0, sizeof(g_all_clear_data));
}

//選択中のステージの設定
void SetSelectStage(StageId stageId) {
	g_select_stage = stageId;
}

//選択中のステージの取得
StageId GetSelectStage() {
	return g_select_stage;
}

//プレイ画面のクリア時間の設定
void SetClearTime(int time) {
	g_clear_time = time;
}

//プレイ画面のクリア時間の取得
int GetClearTime() {
	return g_clear_time;
}

//クリアデータの読み込み依頼
void OrderLoadClearData() {
	LoadClearData(&g_all_clear_data);
}

//クリアデータの更新依頼
void OrderWriteClearData() {
	WriteClearData(&g_all_clear_data);
}

//クリアデータの取得
AllClearData* GetAllClearData() {
	return &g_all_clear_data;
}

//クリアしたステージ数の取得
int GetClearStageNum() {
	int i;
	int count = 0;
	for (i = 0; i < STAGE_NUM; i++) {
		if (g_all_clear_data.clear_data[i].is_clear)
			count++;
	}
	return count;
}

//召喚・消滅範囲表示フラグの設定
void SetUseSummonArea(BOOL flag) {
	g_use_summon_area = flag;
}

//召喚・消滅範囲表示フラグの取得
BOOL GetUseSummonArea() {
	return g_use_summon_area;
}

//プレイヤーの座標を取得する依頼
Vector2DF OrderGetPlayerPos() {
	return GetPlayerPos();
}

//プレイヤーの座標を設定する依頼
void OrderSetPlayerPos(Vector2DF pos) {
	SetPlayerPos(pos);
}

//プレイヤーの向きを設定する依頼
void OrderSetPlayerDirection(BOOL isLeft) {
	SetPlayerDirection(isLeft);
}

//プレイヤーの召喚可能モンスターを設定する依頼
void OrderSetPlayerSummonable(BOOL summonable[]) {
	SetPlayerSummonable(summonable);
}

//プレイヤーのSPを設定する依頼
void OrderSetPlayerSp(int sp) {
	SetPlayerSp(sp);
}

//プレイヤーの当たり判定を設定する依頼
void OrderSetPlayerCollider(BoxCollider *collider) {
	SetPlayerCollider(collider);
}

//プレイヤーのSPを回復する依頼
void OrderAddPlayerSp(int plus) {
	AddPlayerSp(plus);
}

//プレイヤーがお宝を取得したときの処理依頼
void OrderPlayerGetTreasure() {
	PlayerGetTreasure();
}

//プレイヤーがダメージ判定と衝突したときの処理依頼
void OrderCollisionPlayer() {
	CollisionPlayer();
}

//召喚モンスターの生成依頼
int OrderCreateMinion(SummonAreaData *summon_area_data) {
	return CreateMinion(summon_area_data);
}

//召喚モンスターの配置依頼
BOOL OrderSetMinion(MonsterList *minion) {
	return SetMinion(minion);
}

//召喚コストの取得依頼
int OrderGetSummonCost(MinionPattern knd) {
	return GetSummonCost(knd);
}

//召喚モンスターの画像取得依頼
Sprite OrderGetMinionSprite(MinionPattern knd) {
	return GetMinionSprite(knd);
}

//召喚モンスターの当たり判定の設定依頼
void OrderSetMinionsCollider(BoxCollider collider[]) {
	SetMinionsCollider(collider);
}

//召喚モンスターの生成・消滅範囲情報の取得依頼
SummonAreaData OrderGetSummonAreaData(MinionPattern knd, Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft) {
	return GetSummonAreaData(knd, pl_pos, pl_col, isLeft);
}

//召喚モンスターを消す依頼
void OrderDeleteMinion(SummonAreaData *summon_area_data) {
	DeleteMinion(summon_area_data);
}

//召喚モンスターのダメージ処理依頼
BOOL OrderDamageMinion(int i, int power) {
	return DamageMinion(i, power);
}

//召喚モンスターの消滅依頼
void OrderDestroyMinion(int i) {
	DestroyMinion(i);
}

//オーブスポナーの生成依頼
BOOL OrderCreateOrbSpawner(Vector2DF *pos, int sp) {
	return CreateOrbSpawner(pos, sp);
}

//オーブの当たり判定の設定依頼
void OrderSetOrbsCollider(BoxCollider collider[]) {
	SetOrbsCollider(collider);
}

//オーブの消滅処理依頼
void OrderDestroyOrb(int i) {
	DestroyOrb(i);
}

//ドラゴンの炎の当たり判定の設定依頼
void OrderSetFireCollider(BoxCollider collider[]) {
	SetFireCollider(collider);
}

//敵モンスターの生成依頼
BOOL OrderCreateEnemy(MonsterList *enemy_list) {
	return CreateEnemy(enemy_list);
}

//敵モンスターの当たり判定の設定依頼
void OrderSetEnemiesCollider(BoxCollider collider[]) {
	SetEnemiesCollider(collider);
}

//敵モンスターのダメージ処理依頼
BOOL OrderDamageEnemy(int i, int power) {
	return DamageEnemy(i, power);
}

//敵の魔法の当たり判定の設定依頼
void OrderSetMagicsCollider(BoxCollider collider[]) {
	SetMagicsCollider(collider);
}

//敵の魔法の壁衝突処理依頼
BOOL OrderCollisionMagic(int i) {
	return CollisionMagic(i);
}

//敵の魔法の消滅依頼
void OrderDestroyMagic(int i) {
	DestroyMagic(i);
}

//敵の魔法のダメージ量の取得依頼
int OrderGetMagicPower(int i) {
	return GetMagicPower(i);
}

//お宝の座標を設定する
void OrderSetTreasurePos(Vector2DF pos) {
	SetTreasurePos(pos);
}

//お宝の当たり判定を設定する
void OrderSetTreasureCollider(BoxCollider *collider) {
	SetTreasureCollider(collider);
}

//お宝がプレイヤーと衝突したときの処理依頼
void OrderCollisionTreasure() {
	CollisionTreasure();
}

//エフェクトの生成依頼
BOOL OrderCreateEffect(EffectPattern knd, Vector2DF *pos, BOOL isLeft) {
	return CreateEffect(knd, pos, isLeft);
}

//マップを取得する依頼
MapData OrderGetMap() {
	return GetMap();
}

//指定した座標をマップ座標に変換する依頼
void OrderGetMapPosWithPos(Vector2DF pos, int *x, int *y) {
	GetMapPosWithPos(pos, x, y);
}

//指定したマップ座標を座標に変換する依頼
Vector2DF OrderGetPosWithMapPos(int x, int y) {
	return GetPosWithMapPos(x, y);
}

//指定した座標が通過不可マスかどうかの依頼
BOOL OrderIsWallWithPos(float x, float y) {
	return IsWallWithPos(x, y);
}

//オブジェクトとマップの当たり判定依頼
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	return CollisionObjectMap(pos, vel, col);
}

//オブジェクトと召喚モンスターの当たり判定依頼
BOOL OrderCollisionObjectMinions(Vector2DF *pos, RectF *col) {
	return CollisionObjectMinions(pos, col);
}

//オブジェクトと召喚モンスターの当たり判定依頼（当たったものは消す）
BOOL OrderCollisionDeleteObjectMinions(Vector2DF *pos, RectF *col) {
	return CollisionDeleteObjectMinions(pos, col);
}

//オブジェクトと敵モンスターの当たり判定依頼
BOOL OrderCollisionObjectEnemies(Vector2DF *pos, RectF *col) {
	return CollisionObjectEnemies(pos, col);
}

//カメラのオフセットを取得する依頼
Vector2DF OrderGetCameraOffset() {
	return GetCameraOffset();
}

//マップ外にいるかの判定依頼
BOOL OrderIsOutsideMap(Vector2DF *pos, RectF *col) {
	return IsOutsideMap(pos, col);
}

//画面下にいるかの判定依頼
BOOL OrderIsUnderMap(Vector2DF *pos, RectF *col) {
	return IsUnderMap(pos, col);
}

//画面横にはみ出ないようにする依頼
void OrderClampMap(Vector2DF *pos, RectF *col) {
	ClampMap(pos, col);
}


