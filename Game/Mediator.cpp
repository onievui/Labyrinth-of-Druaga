#pragma once




//�w�b�_�t�@�C���̓ǂݍ���
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



//�O���[�o���ϐ��̐錾
static StageId g_select_stage;			//�I�𒆂̃X�e�[�W
static int g_clear_time;				//�X�e�[�W�N���A�܂ł̎���
static BOOL g_use_summon_area;			//�����E���Ŕ͈͕\���t���O
static AllClearData g_all_clear_data;		//�X�e�[�W�̃N���A���


extern void LoadClearData(AllClearData *all_clear_data);
extern void WriteClearData(AllClearData *all_clear_data);



//�O���[�o���ϐ��̏�����
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	g_clear_time = -1;
	g_use_summon_area = FALSE;
	memset(&g_all_clear_data, 0, sizeof(g_all_clear_data));
}

//�I�𒆂̃X�e�[�W�̐ݒ�
void SetSelectStage(StageId stageId) {
	g_select_stage = stageId;
}

//�I�𒆂̃X�e�[�W�̎擾
StageId GetSelectStage() {
	return g_select_stage;
}

//�v���C��ʂ̃N���A���Ԃ̐ݒ�
void SetClearTime(int time) {
	g_clear_time = time;
}

//�v���C��ʂ̃N���A���Ԃ̎擾
int GetClearTime() {
	return g_clear_time;
}

//�N���A�f�[�^�̓ǂݍ��݈˗�
void OrderLoadClearData() {
	LoadClearData(&g_all_clear_data);
}

//�N���A�f�[�^�̍X�V�˗�
void OrderWriteClearData() {
	WriteClearData(&g_all_clear_data);
}

//�N���A�f�[�^�̎擾
AllClearData* GetAllClearData() {
	return &g_all_clear_data;
}

//�N���A�����X�e�[�W���̎擾
int GetClearStageNum() {
	int i;
	int count = 0;
	for (i = 0; i < STAGE_NUM; i++) {
		if (g_all_clear_data.clear_data[i].is_clear)
			count++;
	}
	return count;
}

//�����E���Ŕ͈͕\���t���O�̐ݒ�
void SetUseSummonArea(BOOL flag) {
	g_use_summon_area = flag;
}

//�����E���Ŕ͈͕\���t���O�̎擾
BOOL GetUseSummonArea() {
	return g_use_summon_area;
}

//�v���C���[�̍��W���擾����˗�
Vector2DF OrderGetPlayerPos() {
	return GetPlayerPos();
}

//�v���C���[�̍��W��ݒ肷��˗�
void OrderSetPlayerPos(Vector2DF pos) {
	SetPlayerPos(pos);
}

//�v���C���[�̌�����ݒ肷��˗�
void OrderSetPlayerDirection(BOOL isLeft) {
	SetPlayerDirection(isLeft);
}

//�v���C���[�̏����\�����X�^�[��ݒ肷��˗�
void OrderSetPlayerSummonable(BOOL summonable[]) {
	SetPlayerSummonable(summonable);
}

//�v���C���[��SP��ݒ肷��˗�
void OrderSetPlayerSp(int sp) {
	SetPlayerSp(sp);
}

//�v���C���[�̓����蔻���ݒ肷��˗�
void OrderSetPlayerCollider(BoxCollider *collider) {
	SetPlayerCollider(collider);
}

//�v���C���[��SP���񕜂���˗�
void OrderAddPlayerSp(int plus) {
	AddPlayerSp(plus);
}

//�v���C���[��������擾�����Ƃ��̏����˗�
void OrderPlayerGetTreasure() {
	PlayerGetTreasure();
}

//�v���C���[���_���[�W����ƏՓ˂����Ƃ��̏����˗�
void OrderCollisionPlayer() {
	CollisionPlayer();
}

//���������X�^�[�̐����˗�
int OrderCreateMinion(SummonAreaData *summon_area_data) {
	return CreateMinion(summon_area_data);
}

//���������X�^�[�̔z�u�˗�
BOOL OrderSetMinion(MonsterList *minion) {
	return SetMinion(minion);
}

//�����R�X�g�̎擾�˗�
int OrderGetSummonCost(MinionPattern knd) {
	return GetSummonCost(knd);
}

//���������X�^�[�̉摜�擾�˗�
Sprite OrderGetMinionSprite(MinionPattern knd) {
	return GetMinionSprite(knd);
}

//���������X�^�[�̓����蔻��̐ݒ�˗�
void OrderSetMinionsCollider(BoxCollider collider[]) {
	SetMinionsCollider(collider);
}

//���������X�^�[�̐����E���Ŕ͈͏��̎擾�˗�
SummonAreaData OrderGetSummonAreaData(MinionPattern knd, Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft) {
	return GetSummonAreaData(knd, pl_pos, pl_col, isLeft);
}

//���������X�^�[�������˗�
void OrderDeleteMinion(SummonAreaData *summon_area_data) {
	DeleteMinion(summon_area_data);
}

//���������X�^�[�̃_���[�W�����˗�
BOOL OrderDamageMinion(int i, int power) {
	return DamageMinion(i, power);
}

//���������X�^�[�̏��ň˗�
void OrderDestroyMinion(int i) {
	DestroyMinion(i);
}

//�I�[�u�X�|�i�[�̐����˗�
BOOL OrderCreateOrbSpawner(Vector2DF *pos, int sp) {
	return CreateOrbSpawner(pos, sp);
}

//�I�[�u�̓����蔻��̐ݒ�˗�
void OrderSetOrbsCollider(BoxCollider collider[]) {
	SetOrbsCollider(collider);
}

//�I�[�u�̏��ŏ����˗�
void OrderDestroyOrb(int i) {
	DestroyOrb(i);
}

//�h���S���̉��̓����蔻��̐ݒ�˗�
void OrderSetFireCollider(BoxCollider collider[]) {
	SetFireCollider(collider);
}

//�G�����X�^�[�̐����˗�
BOOL OrderCreateEnemy(MonsterList *enemy_list) {
	return CreateEnemy(enemy_list);
}

//�G�����X�^�[�̓����蔻��̐ݒ�˗�
void OrderSetEnemiesCollider(BoxCollider collider[]) {
	SetEnemiesCollider(collider);
}

//�G�����X�^�[�̃_���[�W�����˗�
BOOL OrderDamageEnemy(int i, int power) {
	return DamageEnemy(i, power);
}

//�G�̖��@�̓����蔻��̐ݒ�˗�
void OrderSetMagicsCollider(BoxCollider collider[]) {
	SetMagicsCollider(collider);
}

//�G�̖��@�̕ǏՓˏ����˗�
BOOL OrderCollisionMagic(int i) {
	return CollisionMagic(i);
}

//�G�̖��@�̏��ň˗�
void OrderDestroyMagic(int i) {
	DestroyMagic(i);
}

//�G�̖��@�̃_���[�W�ʂ̎擾�˗�
int OrderGetMagicPower(int i) {
	return GetMagicPower(i);
}

//����̍��W��ݒ肷��
void OrderSetTreasurePos(Vector2DF pos) {
	SetTreasurePos(pos);
}

//����̓����蔻���ݒ肷��
void OrderSetTreasureCollider(BoxCollider *collider) {
	SetTreasureCollider(collider);
}

//���󂪃v���C���[�ƏՓ˂����Ƃ��̏����˗�
void OrderCollisionTreasure() {
	CollisionTreasure();
}

//�G�t�F�N�g�̐����˗�
BOOL OrderCreateEffect(EffectPattern knd, Vector2DF *pos, BOOL isLeft) {
	return CreateEffect(knd, pos, isLeft);
}

//�}�b�v���擾����˗�
MapData OrderGetMap() {
	return GetMap();
}

//�w�肵�����W���}�b�v���W�ɕϊ�����˗�
void OrderGetMapPosWithPos(Vector2DF pos, int *x, int *y) {
	GetMapPosWithPos(pos, x, y);
}

//�w�肵���}�b�v���W�����W�ɕϊ�����˗�
Vector2DF OrderGetPosWithMapPos(int x, int y) {
	return GetPosWithMapPos(x, y);
}

//�w�肵�����W���ʉߕs�}�X���ǂ����̈˗�
BOOL OrderIsWallWithPos(float x, float y) {
	return IsWallWithPos(x, y);
}

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��˗�
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	return CollisionObjectMap(pos, vel, col);
}

//�I�u�W�F�N�g�Ə��������X�^�[�̓����蔻��˗�
BOOL OrderCollisionObjectMinions(Vector2DF *pos, RectF *col) {
	return CollisionObjectMinions(pos, col);
}

//�I�u�W�F�N�g�Ə��������X�^�[�̓����蔻��˗��i�����������̂͏����j
BOOL OrderCollisionDeleteObjectMinions(Vector2DF *pos, RectF *col) {
	return CollisionDeleteObjectMinions(pos, col);
}

//�I�u�W�F�N�g�ƓG�����X�^�[�̓����蔻��˗�
BOOL OrderCollisionObjectEnemies(Vector2DF *pos, RectF *col) {
	return CollisionObjectEnemies(pos, col);
}

//�J�����̃I�t�Z�b�g���擾����˗�
Vector2DF OrderGetCameraOffset() {
	return GetCameraOffset();
}

//�}�b�v�O�ɂ��邩�̔���˗�
BOOL OrderIsOutsideMap(Vector2DF *pos, RectF *col) {
	return IsOutsideMap(pos, col);
}

//��ʉ��ɂ��邩�̔���˗�
BOOL OrderIsUnderMap(Vector2DF *pos, RectF *col) {
	return IsUnderMap(pos, col);
}

//��ʉ��ɂ͂ݏo�Ȃ��悤�ɂ���˗�
void OrderClampMap(Vector2DF *pos, RectF *col) {
	ClampMap(pos, col);
}


