#pragma once




//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"




//�O���[�o���ϐ��̏�����
void InitializeMediator();

//�I�𒆂̃X�e�[�W�̐ݒ�
void SetSelectStage(StageId stageId);

//�I�𒆂̃X�e�[�W�̎擾
StageId GetSelectStage();

//�v���C��ʂ̃N���A���Ԃ̋L��
void SetClearTime(int time);

//�v���C��ʂ̃N���A���Ԃ̎擾
int GetClearTime();

//�v���C���[�̍��W���擾����˗�
Vector2DF OrderGetPlayerPos();

//�v���C���[�̍��W��ݒ肷��˗�
void OrderSetPlayerPos(Vector2DF pos);

//�v���C���[�̒n�ʔ����ݒ肷��˗�
void OrderSetPlayerIsGround(BOOL isGround);

//�v���C���[�̓����蔻���ݒ肷��˗�
void OrderSetPlayerCollider(BoxCollider *collider);

//�v���C���[��������擾�����Ƃ��̏����˗�
void OrderPlayerGetTreasure();

//���������X�^�[�̐����˗�
int OrderCreateMinion(MinionPattern knd, Vector2DF pos, BOOL isLeft);

//����̍��W��ݒ肷��
void OrderSetTreasurePos(Vector2DF pos);

//����̓����蔻���ݒ肷��
void OrderSetTreasureCollider(BoxCollider *collider);

//���󂪃v���C���[�ƏՓ˂����Ƃ��̏����˗�
void OrderCollisionTreasure();

//�}�b�v���擾����˗�
MapData OrderGetMap();

//�w�肵�����W���ʉߕs�}�X���ǂ����̈˗�
BOOL OrderIsMapPosWall(float x, float y);

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��˗�
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//�J�����̃I�t�Z�b�g���擾����˗�
Vector2DF OrderGetCameraOffset();

