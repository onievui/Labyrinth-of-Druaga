#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//���������X�^�[�̏�����
void InitializeMinions();

//���������X�^�[�̐���
int CreateMinion(MinionPattern knd, Vector2DF pos, BOOL isLeft);

//���������X�^�[�̍X�V
void UpdateMinions();

//���������X�^�[�̕`��
void DrawMinions();

//���������X�^�[�̓����蔻��̐ݒ�
void SetEnemysCollider(BoxCollider collider[]);

//���������X�^�[�̃_���[�W����
void DamageMinion(int i, int power);

//���������X�^�[�̏���
void DestroyMinion(int i);








