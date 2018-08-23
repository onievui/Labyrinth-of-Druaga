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

//�v���C���[�̒n�ʔ����ݒ肷��˗�
void OrderSetPlayerIsGround(BOOL isGround) {
	SetPlayerIsGround(isGround);
}

//�v���C���[�̏����\�����X�^�[��ݒ肷��˗�
void OrderSetPlayerSummonable(BOOL summonable[]) {
	SetPlayerSummonable(summonable);
}

//�v���C���[�̓����蔻���ݒ肷��˗�
void OrderSetPlayerCollider(BoxCollider *collider) {
	SetPlayerCollider(collider);
}

//�v���C���[��������擾�����Ƃ��̏����˗�
void OrderPlayerGetTreasure() {
	PlayerGetTreasure();
}

//���������X�^�[�̐����˗�
int OrderCreateMinion(MinionPattern knd, Vector2DF pos, RectF pl_col, BOOL isLeft) {
	return CreateMinion(knd, pos, pl_col, isLeft);
}

//���������X�^�[�̓����蔻��̐ݒ�˗�
void OrderSetMinionsCollider(BoxCollider collider[]) {
	SetMinionsCollider(collider);
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

//�w�肵�����W���ʉߕs�}�X���ǂ����̈˗�
BOOL OrderIsMapPosWall(float x, float y) {
	return IsMapPosWall(x, y);
}

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��˗�
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	return CollisionObjectMap(pos, vel, col);
}

//�J�����̃I�t�Z�b�g���擾����˗�
Vector2DF OrderGetCameraOffset() {
	return GetCameraOffset();
}


