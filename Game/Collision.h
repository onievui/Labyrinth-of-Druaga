#pragma once




//�����蔻��̏�����
void InitializeCollision();

//�����蔻��̍X�V
void UpdateCollision();

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��
int CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//�I�u�W�F�N�g�Ə��������X�^�[�̓����蔻��
BOOL CollisionObjectMinions(Vector2DF *pos, RectF *col);






