#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�萔�̒�`
#define FIRE_INI_OFFSET		(60)					//�e�̍��W�Ƃ̂���
#define FIRE_DRAW_OFFSET	(160-FIRE_INI_OFFSET)	//�`�掞�̒��S���W�̂���

#define FIRE_SPEED			(6)					//���̑���Ԋu



//�֐��̃v���g�^�C�v�錾
RectF GetFireRect(int sprite_num);



Fire g_fire[FIRE_MAX];		//�h���S���̉��I�u�W�F�N�g
Fire g_prototype_fire;		//�h���S���̉��̃v���g�^�C�v


//�h���S���̉��̏�����
void InitializeFire() {

	//�f�[�^�̏�����
	memset(g_fire, 0, sizeof(g_fire));
	
	//�v���g�^�C�v�̍쐬
	g_prototype_fire =
	{
		1,
		0,
		{ 0,0 },
		GetFireRect(0),
		NULL,
		NULL,
		TRUE,
		{ g_sprite[SPR_STD_FIRE],1.0,0.0 },
		0
	};
}

//�h���S���̉��̐���
BOOL CreateFire(Minion *parent) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		//���g�p���ǂ���
		if (!g_fire[i].state) {
			g_fire[i] = g_prototype_fire;
			//�e�̌����ɂ���Č����ƍ��W���ς��
			g_fire[i].pos = parent->pos;
			if (g_fire[i].is_left = parent->is_left) {
				g_fire[i].pos.x -= FIRE_INI_OFFSET;
			}
			else {
				g_fire[i].pos.x += FIRE_INI_OFFSET;
			}
			//�e�̎擾
			g_fire[i].parent = parent;
			//�e�̑��x�̎擾
			g_fire[i].parent_vel = &parent->vel;

			return TRUE;
		}
	}
	return FALSE;
}

//�h���S���̉��̍X�V
void UpdateFire() {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		if (g_fire[i].state) {
			//�o����ԂȂ�
			if (g_fire[i].state < 3) {
				//�傫���Ȃ�r���Ȃ珈�����s��
				if (g_fire[i].state == 1) {
					//10�t���[����1��傫������
					if (g_fire[i].count % FIRE_SPEED == FIRE_SPEED-1) {
						//�摜�̕ύX
						g_fire[i].sprite_num++;
						g_fire[i].graph.sprite.rect = GetSpriteRect(SPR_STD_FIRE, g_fire[i].sprite_num);
						//�����蔻��̍X�V
						g_fire[i].col = GetFireRect(g_fire[i].sprite_num);
						//���E���]������
						if (g_fire[i].is_left) {
							float tmp = g_fire[i].col.left;
							g_fire[i].col.left = -g_fire[i].col.right;
							g_fire[i].col.right = -tmp;
						}
						//�ő�܂ő傫���Ȃ������Ԃ�J�ڂ�����
						if (g_fire[i].sprite_num == 7) {
							g_fire[i].state = 2;
						}
					}
				}
				//�ړ�����
				AddVector2DF(g_fire[i].pos, g_fire[i].parent->vel);
			}
			//���ŏ�ԂȂ�
			else {
				//60�t���[���ŏ��ł�����
				if (g_fire[i].count == 60) {
					g_fire[i].state = 0;
				}
			}
			g_fire[i].count++;
		}
	}
}

//�h���S���̉��̕`��
void DrawFire() {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		if (g_fire[i].state) {
			//�����ɂ���ĕ`�掞�̍��W�����炷
			Vector2DF pos = g_fire[i].pos;
			if (g_fire[i].is_left) {
				pos.x -= FIRE_DRAW_OFFSET;
			}
			else {
				pos.x += FIRE_DRAW_OFFSET;
			}
			//���Œ��͓����ɂ���
			if (g_fire[i].state == 3) {
				float t = (60 - g_fire[i].count) / 60.0f;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * t * (2-t)));
			}

			//�����ɂ���ĉ摜�𔽓]������
			if (g_fire[i].is_left) {
				DrawTurnGraphicToMap(pos, &g_fire[i].graph);
			}
			else {
				DrawGraphicToMap(pos, &g_fire[i].graph);
			}

			//�����x�����ɖ߂�
			if (g_fire[i].state == 3) {
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			/*pos = g_fire[i].pos;
			SubVector2DF(pos, OrderGetCameraOffset());
			RectF rect = { pos.x + g_fire[i].col.left,
				pos.y + g_fire[i].col.top,
				pos.x + g_fire[i].col.right,
				pos.y + g_fire[i].col.bottom };
			DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_BLUE, 0);*/
			
		}
	}
}

//�h���S���̉��̃T�C�Y�擾
RectF GetFireRect(int sprite_num) {
	RectF ret = { 0,0,0,0 };
	switch (sprite_num) {
	case 0:
		ret = { -32,-5,32,5 };
		break;
	case 1:
		ret = { -32,-13,64,13 };
		break;
	case 2:
		ret = { -32,-17,88,17 };
		break;
	case 3:
		ret = { -32,-25,134,25 };
		break;
	case 4:
		ret = { -32,-29,166,29 };
		break;
	case 5:
		ret = { -32,-29,198,29 };
		break;
	case 6:
		ret = { -32,-29,226,29 };
		break;
	case 7:
		ret = { -32,-29,226,29 };
		break;
	}

	return ret;
}

//�h���S���̉��̓����蔻��̐ݒ�
void SetFireCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		collider[i].state = &g_fire[i].state;
		collider[i].pos = &g_fire[i].pos;
		collider[i].col = &g_fire[i].col;
		collider[i].vel = NULL;
		collider[i].ride = &g_fire[i].parent_vel;
		collider[i].collision_state = NULL;
		collider[i].ground_flag = NULL;
	}
}

//�h���S���̉��̐e�I�u�W�F�N�g�ւ̃|�C���^�̕ύX
void ChangeFireParentPt(Minion *pre_parent, Minion *new_parent) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		//�g�p���őΏۂ�ID�����I�u�W�F�N�g�����邩�ǂ���
		if (g_fire[i].state && g_fire[i].parent == pre_parent) {
			//�e�I�u�W�F�N�g�̍Đݒ������
			g_fire[i].parent = new_parent;
		}
	}
}

//�h���S���̉��̐e�����������Ƃ̒ʒm
void DestroyFire(Minion *parent) {
	int i;
	for (i = 0; i < FIRE_MAX; i++) {
		//�g�p���őΏۂ�ID�����I�u�W�F�N�g�����邩�ǂ���
		if (g_fire[i].state && g_fire[i].parent == parent) {
			//ID��ύX���āA��Ԃ�J�ڂ���
			g_fire[i].parent = NULL;
			g_fire[i].state = 3;
			g_fire[i].count = 0;
		}
	}
}

