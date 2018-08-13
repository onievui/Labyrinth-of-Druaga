#pragma once




//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"




//�O���[�o���ϐ��̏�����
void InitializeMediator();

//�I�𒆂̃X�e�[�W�̐ݒ�
void SetSelectStage(StageId stageId);

//�I�𒆂̃X�e�[�W�̎擾
StageId GetSelectStage();

//�v���C���[�̍��W���擾����˗�
Vector2DF OrderGetPlayerPos();

//�v���C���[�̍��W��ݒ肷��˗�
void OrderSetPlayerPos(Vector2DF pos);

//�v���C���[�̓����蔻���ݒ肷��˗�
void OrderSetPlayerCollider(BoxCollider *collider);

//�}�b�v���擾����˗�
MapAll OrderGetMap();

//�w�肵�����W���ʉߕs�}�X���ǂ����̈˗�
BOOL OrderIsMapPosWall(float x, float y);

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��˗�
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//�J�����̃I�t�Z�b�g���擾����˗�
Vector2DF OrderGetCameraOffset();

