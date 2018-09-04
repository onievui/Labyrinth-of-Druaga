#pragma once




//�w�b�_�t�@�C���̓ǂݍ���
#include "Mediator.h"
#include "Map.h"
#include "Player.h"
#include "MinionManager.h"
#include "Treasure.h"
#include "Collision.h"



//�O���[�o���ϐ��̐錾
static StageId g_select_stage;	//�I�𒆂̃X�e�[�W
static int g_clear_time;		//�X�e�[�W�N���A�܂ł̎���




//�O���[�o���ϐ��̏�����
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	g_clear_time = -1;
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

//�v���C���[�̍��W���擾����˗�
Vector2DF OrderGetPlayerPos() {
	return GetPlayerPos();
}

//�v���C���[�̍��W��ݒ肷��˗�
void OrderSetPlayerPos(Vector2DF pos) {
	SetPlayerPos(pos);
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

//���������X�^�[�̐����˗�
int OrderCreateMinion(MinionPattern knd, Vector2DF pos, RectF pl_col, BOOL isLeft) {
	return CreateMinion(knd, pos, pl_col, isLeft);
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

//���������X�^�[�������˗�
void OrderDeleteMinion(Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft) {
	DeleteMinion(pl_pos, pl_col, isLeft);
}

//���������X�^�[�̏��ň˗�
void OrderDestroyMinion(int i) {
	DestroyMinion(i);
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

//�J�����̃I�t�Z�b�g���擾����˗�
Vector2DF OrderGetCameraOffset() {
	return GetCameraOffset();
}

//�}�b�v�O�ɂ��邩�̔���˗�
BOOL OrderIsOutsideMap(Vector2DF *pos, RectF *col) {
	return IsOutsideMap(pos, col);
}

