#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"






//�G�����X�^�[�̃v���g�^�C�v�̏�����
void InitializePrototypeEnemy(Enemy proto_enemy[]);

//�h���C�h�̍X�V
void UpdateEnemyDruid(Enemy *enemy);

//�E�B�U�[�h�̍X�V
void UpdateEnemyWizard(Enemy *enemy);

//�h���C�h�̕`��
void DrawEnemyDruid(Enemy *enemy);

//�E�B�U�[�h�̕`��
void DrawEnemyWizard(Enemy *enemy);

//�h���C�h�̃_���[�W����
BOOL DamageEnemyDruid(Enemy *enemy, int power);

//�E�B�U�[�h�̃_���[�W����
BOOL DamageEnemyWizard(Enemy *enemy, int power);

//�h���C�h�̏���
void DestroyEnemyDruid(Enemy *enemy);

//�E�B�U�[�h�̏���
void DestroyEnemyWizard(Enemy *enemy);



