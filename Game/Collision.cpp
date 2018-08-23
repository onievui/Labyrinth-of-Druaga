#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "Mediator.h"
#include "GameDefine.h"
#include  <math.h>



//�}�N���̒�`
//������`�̓����蔻��𑍓����肳����}�N��
#define MR_COLLISION_MACRO(col1, len1, i, col2, len2, j, check)			\
	for (i = len1 - 1; i >= 0; i--)										\
		if (*col1[i].state)												\
			for (j = len2 - 1; j >= 0; j--)								\
				if (*col2[j].state)										\
					if (check = CollisionMovingAABB(&col1[i], &col2[j]))	

//������`�̓����蔻����I�u�W�F�N�g�̐�^2/2�����[�v������}�N��
#define MR_COLLISION_MACRO2(col, len, i, j, check)						\
	for (i = 0; i < len - 1; i++)										\
		if (*col[i].state)												\
			for (j = i + 1; j < len; j++)								\
				if (*col[j].state)										\
					if (check = CollisionMovingAABB(&col[i], &col[j]))	



//�O���[�o���ϐ��̐錾
BoxCollider g_player_collider[PLAYER_MAX];			//�v���C���[�̓����蔻��
BoxCollider g_treasure_collider[TREASURE_MAX];		//����̓����蔻��	
BoxCollider g_minion_collider[MINION_MAX];			//���������X�^�[�̓����蔻��


//�v���g�^�C�v�錾
int CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2);



//�����蔻��̏�����
void InitializeCollision() {
	OrderSetPlayerCollider(g_player_collider);
	OrderSetTreasureCollider(g_treasure_collider);
	OrderSetMinionsCollider(g_minion_collider);
}

//�����蔻��
void UpdateCollision() {

	//���[�v�p�J�E���^
	int i = 0, j = 0;
	//�����蔻��p�t���O
	int check = 0;


	//�v���C���[�Ƃ���̓����蔻��
	MR_COLLISION_MACRO(g_player_collider, PLAYER_MAX, i, g_treasure_collider, TREASURE_MAX, j, check) {
		//���������
		OrderCollisionTreasure();
		//������擾�������̏������s��
		OrderPlayerGetTreasure();
	}
	
	//���������X�^�[���m�̓����蔻��
	MR_COLLISION_MACRO2(g_minion_collider, MINION_MAX, i, j, check) {

	}

	//�v���C���[�Ə��������X�^�[�̓����蔻��
	MR_COLLISION_MACRO(g_player_collider, PLAYER_MAX, i, g_minion_collider, MINION_MAX, j, check) {
		if (check & ISGROUND) {
			OrderSetPlayerIsGround(TRUE);
		}
	}

	

}

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��
int CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	float tempF;//�v�Z�p

	//�ړ��O�̍��W
	RectF rect0 = {
		pos->x + col->left,
		pos->y + col->top,
		pos->x + col->right - 1,
		pos->y + col->bottom - 1,
	};
	//�ړ���̍��W
	RectF rect1 = {
		vel->x + rect0.left,
		vel->y + rect0.top,
		vel->x + rect0.right,
		vel->y + rect0.bottom,
	};

	//�}�b�v�c����������
	BOOL mL = OrderIsMapPosWall(rect1.left,rect0.top)     || OrderIsMapPosWall(rect1.left, rect0.bottom);
	BOOL mR = OrderIsMapPosWall(rect1.right, rect0.top)   || OrderIsMapPosWall(rect1.right, rect0.bottom);
	BOOL mU = OrderIsMapPosWall(rect0.left, rect1.top)    || OrderIsMapPosWall(rect0.right, rect1.top);
	BOOL mD = OrderIsMapPosWall(rect0.left, rect1.bottom) || OrderIsMapPosWall(rect0.right, rect1.bottom);

	//�}�b�v�΂ߕ�������
	if (!mL && !mU) { mL = mU = OrderIsMapPosWall(rect1.left, rect1.top); }
	if (!mL && !mD) { mL = mD = OrderIsMapPosWall(rect1.left, rect1.bottom); }
	if (!mR && !mU) { mR = mU = OrderIsMapPosWall(rect1.right, rect1.top); }
	if (!mR && !mD) { mR = mD = OrderIsMapPosWall(rect1.right, rect1.bottom); }

	//���W���u���b�N�̉��ɍ��킹��
	if (mL && !mR) {
		tempF = ceilf(rect1.left / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->left;		//��
		if (pos->x > tempF)pos->x = tempF;
	}
	if (!mL && mR ) {
		tempF = floorf(rect1.right / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->right;	//�E
		if (pos->x < tempF)pos->x = tempF;
	}
	if (mU && !mD) {
		tempF = ceilf(rect1.top / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->top;		//��
		if (pos->y > tempF)pos->y = tempF;
	}
	if (!mU && mD) {
		tempF = floorf(rect1.bottom / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->bottom;	//��
		if (pos->y < tempF)pos->y = tempF;
	}

	//����ɂ�������~����
	if (mL) if (vel->x<0)vel->x = 0;
	if (mR) if (vel->x>0)vel->x = 0;
	if (mU) if (vel->y<0)vel->y = 0;
	if (mD) if (vel->y>0)vel->y = 0;

	//�P�����ł��Փ˂��Ă�����TRUE��Ԃ�
	return mL + mR*2 + mU*4 + mD*8;
}



//�I�u�W�F�N�g�Ɠ�����`���m�̓����蔻��
//BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
//	Vector2DF vel = *obj1->vel;		//���Α��x�̌v�Z
//	SubVector2DF(vel, *obj2->vel);
//
//	float xtMin, xtMax, ytMin, ytMax, tMin, tMax;
//	BOOL xFlag, yFlag;
//
//	if (vel.x != 0) {
//		xtMin = (obj2->pos->x - obj1->pos->x - (obj1->col->right - obj2->col->left)) / vel.x;	// X���ɂ��Ă�t�̏��
//		xtMax = (obj2->pos->x - obj1->pos->x + (obj2->col->right - obj1->col->left)) / vel.x;	// X���ɂ��Ă�t�̉���
//		xFlag = TRUE;
//		if (vel.x < 0) {	// ����̕��������������ꍇ�̕s�������]�ւ̑Ώ�
//			float swap = xtMin;
//			xtMin = xtMax;
//			xtMax = swap;
//		}
//	}
//	else {
//		xFlag = FALSE;
//	}
//	
//
//	if (vel.y != 0) {
//		ytMin = (obj2->pos->y - obj1->pos->y - (obj1->col->bottom - obj2->col->top)) / vel.y;	// Y���ɂ��Ă�t�̏��
//		ytMax = (obj2->pos->y - obj1->pos->y + (obj2->col->bottom - obj1->col->top)) / vel.y;	// Y���ɂ��Ă�t�̉���
//		yFlag = TRUE;
//		if (vel.y < 0) {	// ����̕��������������ꍇ�̕s�������]�ւ̑Ώ�
//			float swap = ytMin;
//			ytMin = ytMax;
//			ytMax = swap;
//		}
//	}
//	else {
//		yFlag = FALSE;
//	}
//	
//
//	if (!xFlag) {
//		if (!yFlag) {
//			//return CollisionAABB(obj1, obj2);	//���x0�Ȃ�ʏ��AABB���s��
//		}
//		xtMin = ytMin;
//		xtMax = ytMax;
//	}
//	else if (!yFlag) {
//		ytMin = xtMin;
//		ytMax = xtMax;
//	}
//
//	// �������m�A������m�Ŕ͈͂��i�荞��
//	tMin = xtMin > ytMin ? xtMin : ytMin;
//	tMax = xtMax < ytMax ? xtMax : ytMax;
//
//	// tMin < t < tMax �� 0 < t < 1 �ɋ��ʔ͈͂�����ΏՓ�
//	if (tMin < tMax && tMin <= 1 && 0 <= tMax) {
//		// ���̉��ɂ��鑬�x���������p��t�̉�����0�����̏ꍇ��0�ɐݒ�
//		tMin = tMin < 0 ? 0 : tMin;
//		xtMin = xtMin < 0 ? 0 : xtMin;
//		ytMin = ytMin < 0 ? 0 : ytMin;
//
//		// X�������̏Փ˂̏ꍇ�A���x��X�����݂̂�␳
//		if (tMin == xtMin) {
//			obj1->vel->x *= tMin;
//			obj2->vel->x *= tMin;
//		}
//		// Y�������̏Փ˂̏ꍇ�A���x��Y�����݂̂�␳
//		if (tMin == ytMin) {
//			obj1->vel->y *= tMin;
//			obj2->vel->y *= tMin;
//		}
//		
//		return TRUE;
//	}
//	return FALSE;
//}


//�I�u�W�F�N�g�Ɠ�����`���m�̓����蔻��
int CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
	Vector2DF vel = *obj1->vel;		//���Α��x�̌v�Z
	SubVector2DF(vel, *obj2->vel);

	float t, tx, ty;	//�Փ˂���܂ł̎���
	BOOL xflag, yflag;	//�Փ˂������̔���

	t = tx = ty = 999;
	xflag = yflag = FALSE;

	Vector2DF point = { obj1->pos->x + obj1->col->left,
						obj1->pos->y + obj1->col->top };
	RectF rect = { obj2->pos->x + obj2->col->left - (obj1->col->right- obj1->col->left),
					obj2->pos->y + obj2->col->top - (obj1->col->bottom - obj1->col->top),
					obj2->pos->x + obj2->col->right,
					obj2->pos->y + obj2->col->bottom };

	//X�����̑��x��0�łȂ��Ȃ玞�Ԃ����߂�
	if (vel.x != 0) {
		float lineX = (vel.x > 0) ? rect.left : rect.right;
		tx = (lineX - point.x) / vel.x;

		if ((tx >= 0) && (tx <= 1.0f)){
			t = tx;
			xflag = TRUE;
		}
		else if (point.x >= rect.left && point.x <= rect.right) {
			xflag = TRUE;
		}
	}
	//X�����̑��x��0�Ȃ瓖�����Ă��邩�����߂�
	else {	
		if (point.x >= rect.left && point.x <= rect.right) {
			/*if (point.x == rect.left || point.x == rect.right) {
				xflag = FALSE;
			}
			else {
				xflag = TRUE;
			}*/
			xflag = TRUE;
		}
	}

	//Y�����̑��x��0�łȂ��Ȃ玞�Ԃ����߂�
	if (vel.y != 0) {
		float lineY = (vel.y > 0) ? rect.top : rect.bottom;
		ty = (lineY - point.y) / vel.y;

		if ((ty >= 0) && (ty <= 1.0f)){
			t = t < ty ? t : ty;
			yflag = TRUE;
		}
		else if(point.y >= rect.top && point.y <= rect.bottom) {
			yflag = TRUE;
		}
	}
	//Y�����̑��x��0�Ȃ瓖�����Ă��邩�����߂�
	else {
		if (point.y >= rect.top && point.y <= rect.bottom) {
			yflag = TRUE;
		}
	}

	//�Փ˂��Ă���Ȃ�
	if (xflag && yflag) {
		if (t != 999) {
			//X�����ɐ�ɏՓ˂����Ȃ�
			if (t == tx) {
				obj1->vel->x *= tx;
				obj2->vel->x *= tx;
			}
			//Y�����ɐ�ɏՓ˂����Ȃ�
			if (t == ty) {
				obj1->vel->y *= ty;
				obj2->vel->y *= ty;
				//obj1�̉����ƏՓ˂����Ȃ�
				if (obj1->pos->y < obj2->pos->y) {
					return ISGROUND;
				}
				else {
					return ISCEILING;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

/*
//�I�u�W�F�N�g�Ɠ�����`���m�̓����蔻��
BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
	Vector2DF vel = *obj1->vel;		//���Α��x�̌v�Z
	SubVector2DF(vel, *obj2->vel);

	Vector2DF pos1 = *obj1->pos;	//�ړ���̍��W�̌v�Z
	Vector2DF pos2 = *obj2->pos;
	AddVector2DF(pos1, *obj1->vel);
	AddVector2DF(pos2, *obj2->vel);

	BOOL ret = FALSE;				//�����������ǂ����̔���

	float sinkX, sinkY;				//�߂肱�ݗ�
	float distX, distY;				//�ړ��O�̋���

	//obj1�̕������Ȃ�
	if (obj1->pos->x < obj2->pos->x) {
		sinkX = (obj1->col->right - obj2->col->left) - (pos2.x - pos1.x);
		distX = (obj2->pos->x - obj1->pos->x) - (obj1->col->right - obj2->col->left);
	}
	//obj1�̕����E�Ȃ�
	else {
		sinkX = (obj2->col->right - obj1->col->left) - (pos1.x - pos2.x);
		distX = (obj1->pos->x - obj2->pos->x) - (obj2->col->right - obj1->col->left);
	}

	//obj1�̕�����Ȃ�
	if (obj1->pos->y < obj2->pos->y) {
		sinkY = (obj1->col->bottom - obj2->col->top) - (pos2.y - pos1.y);
		distY = (obj2->pos->y - obj1->pos->y) - (obj1->col->bottom - obj2->col->top);
	}
	//obj1�̕������Ȃ�
	else {
		sinkY = (obj2->col->bottom - obj1->col->top) - (pos1.y - pos2.y);
		distY = (obj1->pos->y - obj2->pos->y) - (obj2->col->bottom - obj1->col->top);
	}

	//�Փ˂��Ă���Ȃ�
	if (sinkX >= 0 && sinkY >= 0) {
		//obj1->vel->x=
	}
}

//�I�u�W�F�N�g�Ɠ�����`���m�̓����蔻��
BOOL CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2) {
	Vector2DF vel = *obj1->vel;		//���Α��x�̌v�Z
	SubVector2DF(vel, *obj2->vel);

	Vector2DF pos1 = *obj1->pos;	//�ړ���̍��W�̌v�Z
	Vector2DF pos2 = *obj2->pos;
	AddVector2DF(pos1, *obj1->vel);
	AddVector2DF(pos2, *obj2->vel);

	BOOL lrflag = pos1.x < pos2.x;
	BOOL tbflag = pos1.y < pos2.y;

	if (lrflag) {
		if (tbflag) {

		}
	}
}

*/