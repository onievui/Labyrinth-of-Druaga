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

//�v���C���[�̏����\�����X�^�[��ݒ肷��˗�
void OrderSetPlayerSummonable(BOOL summonable[]);

//�v���C���[�̒n�ʔ����ݒ肷��˗�
void OrderSetPlayerIsGround(BOOL isGround);

//�v���C���[�̓����蔻���ݒ肷��˗�
void OrderSetPlayerCollider(BoxCollider *collider);

//�v���C���[��SP���񕜂���˗�
void OrderAddPlayerSp(int plus);

//�v���C���[��������擾�����Ƃ��̏����˗�
void OrderPlayerGetTreasure();

//���������X�^�[�̐����˗�
int OrderCreateMinion(MinionPattern knd, Vector2DF pos, RectF pl_col, BOOL isLeft);

//�����R�X�g�̎擾�˗�
int OrderGetSummonCost(MinionPattern knd);

//���������X�^�[�̉摜�擾�˗�
Sprite OrderGetMinionSprite(MinionPattern knd);

//���������X�^�[�̓����蔻��̐ݒ�˗�
void OrderSetMinionsCollider(BoxCollider collider[]);

//���������X�^�[�������˗�
void OrderDeleteMinion(Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft);

//���������X�^�[�̏��ň˗�
void OrderDestroyMinion(int i);

//����̍��W��ݒ肷��
void OrderSetTreasurePos(Vector2DF pos);

//����̓����蔻���ݒ肷��
void OrderSetTreasureCollider(BoxCollider *collider);

//���󂪃v���C���[�ƏՓ˂����Ƃ��̏����˗�
void OrderCollisionTreasure();

//�}�b�v���擾����˗�
MapData OrderGetMap();

//�w�肵�����W���}�b�v���W�ɕϊ�����˗�
void OrderGetMapPosWithPos(Vector2DF pos, int *x, int *y);

//�w�肵���}�b�v���W�����W�ɕϊ�����˗�
Vector2DF OrderGetPosWithMapPos(int x, int y);

//�w�肵�����W���ʉߕs�}�X���ǂ����̈˗�
BOOL OrderIsWallWithPos(float x, float y);

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��˗�
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//�I�u�W�F�N�g�Ə��������X�^�[�̓����蔻��˗�
BOOL OrderCollisionObjectMinions(Vector2DF *pos, RectF *col);

//�J�����̃I�t�Z�b�g���擾����˗�
Vector2DF OrderGetCameraOffset();

