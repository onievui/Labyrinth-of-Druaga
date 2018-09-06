//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Treasure.cpp
//!
//! @brief  ����I�u�W�F�N�g�̏���
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "Mediator.h"


//�O���[�o���ϐ��̐錾
Treasure g_treasure;


//����̏�����
void InitializeTreasure() {
	g_treasure.state = 1;
	g_treasure.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT - 100 };
	g_treasure.col = RectF{ -32,-13,20,24 };
	g_treasure.vel = Vector2DF{ 0,0 };
	g_treasure.ride = NULL;
	g_treasure.is_ground = FALSE;
	g_treasure.graph = Graph{ g_sprite[SPR_OBJECT_TREASURE],1.0,0.0 };
	
}

//����̍X�V
void UpdateTreasure() {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(g_treasure.pos, g_treasure.vel);

	//�d�͂�������
	g_treasure.vel.y += GRAVITY;

	//����Ă���I�u�W�F�N�g�̑��x��������
	if (g_treasure.ride) {
		AddVector2DF(g_treasure.vel, *g_treasure.ride);
	}

	
}

//����̕`��
void DrawTreasure() {
	if (g_treasure.state) {
		DrawGraphicToMap(g_treasure.pos, &g_treasure.graph);
	}
}

//����̍��W��ݒ肷��
void SetTreasurePos(Vector2DF pos) {
	g_treasure.pos = pos;
}

//����̓����蔻���ݒ肷��
void SetTreasureCollider(BoxCollider *collider) {
	collider->state = &g_treasure.state;
	collider->pos = &g_treasure.pos;
	collider->col = &g_treasure.col;
	collider->vel = &g_treasure.vel;
	collider->ride = &g_treasure.ride;
	collider->collision_state = &g_treasure.is_ground;
}

//���󂪃v���C���[�ƏՓ˂����Ƃ��̏���
void CollisionTreasure() {
	g_treasure.state = 0;
}