#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�G�����X�^�[�̏�����
void InitializeEnemies();

//�G�����X�^�[�̐���
BOOL CreateEnemy(MonsterList *enemy_list);

//�G�����X�^�[�̍X�V
void UpdateEnemies();

//�G�����X�^�[�̕`��
void DrawEnemies();

//�G�����X�^�[�̓����蔻��̐ݒ�
void SetEnemiesCollider(BoxCollider collider[]);

//�G�����X�^�[�̃_���[�W����
BOOL DamageEnemy(int i, int power);

//�G�����X�^�[�̏���
void DestroyEnemy(int i);

