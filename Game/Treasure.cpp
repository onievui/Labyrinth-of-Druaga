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
	g_treasure.graph = Graph{ g_sprite[SPR_OBJECT_TREASURE],1.0,0.0 };
	
}

//����̍X�V
void UpdateTreasure() {

	//�d�͂�������
	g_treasure.vel.y += GRAVITY;

	//�}�b�v�Ƃ̓����蔻��
	OrderCollisionObjectMap(&g_treasure.pos, &g_treasure.vel, &g_treasure.col);

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(g_treasure.pos, g_treasure.vel);
}

//����̕`��
void DrawTreasure() {
	if (g_treasure.state) {
		DrawGraphicToMap(g_treasure.pos, &g_treasure.graph);
		/*Vector2DF pos = g_treasure.pos;
		SubVector2DF(pos, OrderGetCameraOffset());
		RectF rect = { pos.x + g_treasure.col.left,
			pos.y + g_treasure.col.top,
			pos.x + g_treasure.col.right,
			pos.y + g_treasure.col.bottom };
		DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);*/
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
	collider->vel = &g_treasure.vel;
	collider->col = &g_treasure.col;
}

//���󂪃v���C���[�ƏՓ˂����Ƃ��̏���
void CollisionTreasure() {
	g_treasure.state = 0;
}