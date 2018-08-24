#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//���������X�^�[�̏�����
void InitializeMinions();

//���������X�^�[�̐���
int CreateMinion(MinionPattern knd, Vector2DF pos, RectF pl_col, BOOL isLeft);

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

//���������X�^�[�̃_���[�W����
void DamageMinion(int i, int power);

//���������X�^�[�̏���
void DestroyMinion(int i);








