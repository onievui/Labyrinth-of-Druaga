#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�I�[�u�̏�����
void InitializeOrbs();

//�I�[�u�̐���
BOOL CreateOrb(Vector2DF *pos, int sp);

//�I�[�u�̍X�V
void UpdateOrbs();

//�I�[�u�̕`��
void DrawOrbs();

//�I�[�u�̓����蔻��̐ݒ�
void SetOrbsCollider(BoxCollider collider[]);

//�I�[�u�̏��ŏ���
void DestroyOrb(int i);




