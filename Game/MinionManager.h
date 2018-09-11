#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//���������X�^�[�̏�����
void InitializeMinions();

//���������X�^�[�̐���
int CreateMinion(SummonAreaData *summon_area_data);

//�����R�X�g�̎擾
int GetSummonCost(MinionPattern knd);

//���������X�^�[�̉摜�擾
Sprite GetMinionSprite(MinionPattern knd);

//���������X�^�[�̍X�V
void UpdateMinions();

//���������X�^�[�̕`��
void DrawMinions();

//���������X�^�[�̓����蔻��̐ݒ�
void SetMinionsCollider(BoxCollider collider[]);

//���������X�^�[�̐����E���Ŕ͈͏��̎擾
SummonAreaData GetSummonAreaData(MinionPattern knd, Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft);

//���������X�^�[������
void DeleteMinion(SummonAreaData *summon_area_data);

//���������X�^�[�̃_���[�W����
BOOL DamageMinion(int i, int power);

//���������X�^�[�̏���
void DestroyMinion(int i);








