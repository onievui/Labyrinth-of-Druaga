#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�G�t�F�N�g�̏�����
void InitializeEffects();

//�G�t�F�N�g�̐���
BOOL CreateEffect(EffectPattern knd, Vector2DF *pos, BOOL isLeft);

//�G�t�F�N�g�̍X�V
void UpdateEffects();

//�G�t�F�N�g�̕`��
void DrawEffects();


