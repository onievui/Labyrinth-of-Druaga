//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  �v���C���[�I�u�W�F�N�g�̃w�b�_�t�@�C��
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�v���C���[�̏�����
void InitializePlayer();

//�v���C���[�̍X�V
void UpdatePlayer();

//�v���C���[�̕`��
void DrawPlayer();

//�v���C���[�֌W�̏��̕`��
void DrawPlayerUI();

//�v���C���[�̍��W���擾����
Vector2DF GetPlayerPos();

//�v���C���[�̍��W��ݒ肷��
void SetPlayerPos(Vector2DF pos);

//�v���C���[�̏����\�����X�^�[��ݒ肷��
void SetPlayerSummonable(BOOL summonable[]);

//�v���C���[��SP��ݒ肷��
void SetPlayerSp(int sp);

//�v���C���[�̓����蔻���ݒ肷��
void SetPlayerCollider(BoxCollider *collider);

//�v���C���[��SP���񕜂���
void AddPlayerSp(int plus);

//�v���C���[��������擾�����Ƃ��̏���
void PlayerGetTreasure();

//�v���C���[���_���[�W����ƏՓ˂����Ƃ��̏���
void CollisionPlayer();


