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

//�����E���Ŕ͈͕\���t���O�̐ݒ�
void SetUseSummonArea(BOOL flag);

//�����E���Ŕ͈͕\���t���O�̎擾
BOOL GetUseSummonArea();

//�v���C���[�̍��W���擾����˗�
Vector2DF OrderGetPlayerPos();

//�v���C���[�̍��W��ݒ肷��˗�
void OrderSetPlayerPos(Vector2DF pos);

//�v���C���[�̏����\�����X�^�[��ݒ肷��˗�
void OrderSetPlayerSummonable(BOOL summonable[]);

//�v���C���[��SP��ݒ肷��˗�
void OrderSetPlayerSp(int sp);

//�v���C���[�̓����蔻���ݒ肷��˗�
void OrderSetPlayerCollider(BoxCollider *collider);

//�v���C���[��SP���񕜂���˗�
void OrderAddPlayerSp(int plus);

//�v���C���[��������擾�����Ƃ��̏����˗�
void OrderPlayerGetTreasure();

//���������X�^�[�̐����˗�
int OrderCreateMinion(SummonAreaData *summon_area_data);

//�����R�X�g�̎擾�˗�
int OrderGetSummonCost(MinionPattern knd);

//���������X�^�[�̉摜�擾�˗�
Sprite OrderGetMinionSprite(MinionPattern knd);

//���������X�^�[�̓����蔻��̐ݒ�˗�
void OrderSetMinionsCollider(BoxCollider collider[]);

//���������X�^�[�̐����E���Ŕ͈͏��̎擾�˗�
SummonAreaData OrderGetSummonAreaData(MinionPattern knd, Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft);

//���������X�^�[�������˗�
void OrderDeleteMinion(SummonAreaData *summon_area_data);

//���������X�^�[�̏��ň˗�
void OrderDestroyMinion(int i);

//�h���S���̉��̓����蔻��̐ݒ�˗�
void OrderSetFireCollider(BoxCollider collider[]);

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

//�I�u�W�F�N�g�Ə��������X�^�[�̓����蔻��˗��i�����������̂͏����j
BOOL OrderCollisionDeleteObjectMinions(Vector2DF *pos, RectF *col);

//�J�����̃I�t�Z�b�g���擾����˗�
Vector2DF OrderGetCameraOffset();

//�}�b�v�O�ɂ��邩�̔���˗�
BOOL OrderIsOutsideMap(Vector2DF *pos, RectF *col);

//��ʉ��ɂ��邩�̔���˗�
BOOL OrderIsUnderMap(Vector2DF *pos, RectF *col);


