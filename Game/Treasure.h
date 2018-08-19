//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Treasure.h
//!
//! @brief  ����I�u�W�F�N�g�̃w�b�_�t�@�C��
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//����̏�����
void InitializeTreasure();

//����̍X�V
void UpdateTreasure();

//����̕`��
void DrawTreasure();

//����̍��W��ݒ肷��
void SetTreasurePos(Vector2DF pos);

//����̓����蔻���ݒ肷��
void SetTreasureCollider(BoxCollider *collider);

//���󂪃v���C���[�ƏՓ˂����Ƃ��̏���
void CollisionTreasure();
