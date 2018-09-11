#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"




//�h���S���̉��̏�����
void InitializeFire();

//�h���S���̉��̐���
BOOL CreateFire(Minion *parent);

//�h���S���̉��̍X�V
void UpdateFire();

//�h���S���̉��̕`��
void DrawFire();

//�h���S���̉��̓����蔻��̐ݒ�
void SetFireCollider(BoxCollider collider[]);

//�h���S���̉��̐e�I�u�W�F�N�g�ւ̃|�C���^�̕ύX
void ChangeFireParentPt(Minion *pre_parent, Minion *new_parent);

//�h���S���̉��̐e�����������Ƃ̒ʒm
void DestroyFire(Minion *parent);

