#pragma once




//�w�b�_�t�@�C���̓ǂݍ���
#include "Mediator.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"



//�O���[�o���ϐ��̐錾
static StageId g_select_stage;	//�I�𒆂̃X�e�[�W




//�O���[�o���ϐ��̏�����
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	
}

//�I�𒆂̃X�e�[�W�̐ݒ�
void SetSelectStage(StageId stageId) {
	g_select_stage = stageId;
}

//�I�𒆂̃X�e�[�W�̎擾
StageId GetSelectStage() {
	return g_select_stage;
}

//�v���C���[�̍��W���擾����˗�
Vector2DF OrderGetPlayerPos() {
	return GetPlayerPos();
}

//�v���C���[�̍��W��ݒ肷��˗�
void OrderSetPlayerPos(Vector2DF pos) {
	SetPlayerPos(pos);
}

//�v���C���[�̓����蔻���ݒ肷��˗�
void OrderSetPlayerCollider(BoxCollider *collider) {
	SetPlayerCollider(collider);
}

//�}�b�v���擾����˗�
MapAll OrderGetMap() {
	return GetMap();
}

//�w�肵�����W���ʉߕs�}�X���ǂ����̈˗�
BOOL OrderIsMapPosWall(float x, float y) {
	return IsMapPosWall(x, y);
}

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��˗�
BOOL OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	return CollisionObjectMap(pos, vel, col);
}

