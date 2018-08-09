//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  �v���C���[�I�u�W�F�N�g�̃w�b�_�t�@�C��
//!
//! @date   2018/08/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Vector2DF.h"
//#include "Collision.h"



//�v���C���[�̏�����
void InitializePlayer();

//�v���C���[�̍X�V
void UpdatePlayer();

//�v���C���[�̕`��
void DrawPlayer();

//�v���C���[�̍��W���擾����
Vector2DF GetPlayerPos();


//�v���C���[�̓����蔻���ݒ肷��
//void SetPlayerCollider(CircleCollider *collider);

//�v���C���[���G�ƏՓ˂����Ƃ��̏���
//void CollisionPlayer();


