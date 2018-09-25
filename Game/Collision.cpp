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

//������`�̓����蔻��𑍓����肳����}�N���i�ړ����j
#define MR_COLLISION_MACRO3(col1, len1, i, col2, len2, j, check)		\
	for (i = len1 - 1; i >= 0; i--)										\
		if (*col1[i].state)												\
			for (j = len2 - 1; j >= 0; j--)								\
				if (*col2[j].state)										\
					if (check = CollisionMovingAABB2(&col1[i], &col2[j]))	




//�O���[�o���ϐ��̐錾
BoxCollider g_player_collider[PLAYER_MAX];			//�v���C���[�̓����蔻��
BoxCollider g_treasure_collider[TREASURE_MAX];		//����̓����蔻��	
BoxCollider g_minion_collider[MINION_MAX];			//���������X�^�[�̓����蔻��
BoxCollider g_orb_collider[ORB_MAX];				//�I�[�u�̓����蔻��
BoxCollider g_fire_collider[FIRE_MAX];				//�h���S���̉��̓����蔻��
BoxCollider g_enemy_collider[ENEMY_MAX];			//�G�����X�^�[�̓����蔻��
BoxCollider g_magic_collider[MAGIC_MAX];			//�����X�^�[�̖��@�̓����蔻��


//�v���g�^�C�v�錾
int CollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);
int CollisionObjectMap2(Vector2DF *pos, Vector2DF *vel, RectF *col);
int CollisionMovingAABB(BoxCollider *obj1, BoxCollider *obj2);
int CollisionMovingAABB2(BoxCollider *obj1, BoxCollider *obj2);
BOOL CollisionAABB(Vector2DF *pos1, RectF *col1, Vector2DF *pos2, RectF *col2);



//�����蔻��̏�����
void InitializeCollision() {
	OrderSetPlayerCollider(g_player_collider);
	OrderSetTreasureCollider(g_treasure_collider);
	OrderSetMinionsCollider(g_minion_collider);
	OrderSetOrbsCollider(g_orb_collider);
	OrderSetFireCollider(g_fire_collider);
	OrderSetEnemiesCollider(g_enemy_collider);
	OrderSetMagicsCollider(g_magic_collider);
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
	for (i = 0; i < MINION_MAX; i++) {
		*g_minion_collider[i].ride = NULL;
	}
	MR_COLLISION_MACRO2(g_minion_collider, MINION_MAX, i, j, check) {
		if (check & ISGROUND) {
			*g_minion_collider[i].collision_state |= ISGROUND;
			*g_minion_collider[j].collision_state |= ISCEILING;
			*g_minion_collider[i].ride = g_minion_collider[j].vel;
		}
		else if (check & ISCEILING) {
			*g_minion_collider[j].collision_state |= ISGROUND;
			*g_minion_collider[i].collision_state |= ISCEILING;
			*g_minion_collider[j].ride = g_minion_collider[i].vel;
		}
		if (check & ISLEFT) {
			*g_minion_collider[i].collision_state |= ISLEFT;
			*g_minion_collider[j].collision_state |= ISRIGHT;
		}
		else if (check & ISRIGHT) {
			*g_minion_collider[j].collision_state |= ISLEFT;
			*g_minion_collider[i].collision_state |= ISRIGHT;
		}
	}

	//�G�����X�^�[���m�̓����蔻��
	for (i = 0; i < ENEMY_MAX; i++) {
		*g_enemy_collider[i].ride = NULL;
	}
	MR_COLLISION_MACRO2(g_enemy_collider, ENEMY_MAX, i, j, check) {
		if (check & ISGROUND) {
			*g_enemy_collider[i].collision_state |= ISGROUND;
			*g_enemy_collider[j].collision_state |= ISCEILING;
			*g_enemy_collider[i].ride = g_enemy_collider[j].vel;
		}
		else if (check & ISCEILING) {
			*g_enemy_collider[j].collision_state |= ISGROUND;
			*g_enemy_collider[i].collision_state |= ISCEILING;
			*g_enemy_collider[j].ride = g_enemy_collider[i].vel;
		}
		if (check & ISLEFT) {
			*g_enemy_collider[i].collision_state |= ISLEFT;
			*g_enemy_collider[j].collision_state |= ISRIGHT;
		}
		else if (check & ISRIGHT) {
			*g_enemy_collider[j].collision_state |= ISLEFT;
			*g_enemy_collider[i].collision_state |= ISRIGHT;
		}
	}

	//���������X�^�[�ƓG�����X�^�[�̓����蔻��
	MR_COLLISION_MACRO(g_minion_collider, MINION_MAX, i, g_enemy_collider, ENEMY_MAX, j, check) {
		if (check & ISGROUND) {
			*g_minion_collider[i].collision_state |= ISGROUND;
			*g_enemy_collider[j].collision_state |= ISCEILING;
			*g_minion_collider[i].ride = g_enemy_collider[j].vel;
		}
		else if (check & ISCEILING) {
			*g_enemy_collider[j].collision_state |= ISGROUND;
			*g_minion_collider[i].collision_state |= ISCEILING;
			*g_enemy_collider[j].ride = g_minion_collider[i].vel;
		}
		if (check & ISLEFT) {
			*g_minion_collider[i].collision_state |= ISLEFT;
			*g_enemy_collider[j].collision_state |= ISRIGHT;
		}
		else if (check & ISRIGHT) {
			*g_enemy_collider[j].collision_state |= ISLEFT;
			*g_minion_collider[i].collision_state |= ISRIGHT;
		}
	}

	//���������X�^�[�ƃ}�b�v�̓����蔻��
	for (i = 0; i < MINION_MAX; i++) {
		if (*g_minion_collider[i].state) {
			*g_minion_collider[i].collision_state |= check = CollisionObjectMap(g_minion_collider[i].pos, g_minion_collider[i].vel, g_minion_collider[i].col);
			if (check & ISGROUND) {
				*g_minion_collider[i].ground_flag = TRUE;
			}
			else {
				//*g_minion_collider[i].ground_flag = FALSE;
			}
		}
	}

	//�v���C���[�Ə��������X�^�[�̓����蔻��
	*g_player_collider->ride = NULL;
	MR_COLLISION_MACRO(g_player_collider, PLAYER_MAX, i, g_minion_collider, MINION_MAX, j, check) {
		if (check & ISGROUND) {
			*g_player_collider->collision_state = TRUE;
			*g_player_collider->ride = g_minion_collider[j].vel;
		}
		else if (check & ISCEILING) {
			*g_minion_collider[j].collision_state = TRUE;
			*g_minion_collider[j].ride = g_minion_collider[i].vel;
		}
		if (check & ISLEFT) {
			*g_minion_collider[j].collision_state |= ISRIGHT;
		}
		else if (check & ISRIGHT) {
			*g_minion_collider[j].collision_state |= ISLEFT;
		}
	}

	//�v���C���[�ƓG�����X�^�[�̓����蔻��
	MR_COLLISION_MACRO(g_player_collider, PLAYER_MAX, i, g_enemy_collider, ENEMY_MAX, j, check) {
		if (check & ISGROUND) {
			*g_player_collider->collision_state = TRUE;
			*g_player_collider->ride = g_enemy_collider[j].vel;
		}
		else if (check & ISCEILING) {
			*g_enemy_collider[j].collision_state = TRUE;
			*g_enemy_collider[j].ride = g_enemy_collider[i].vel;
		}
		if (check & ISLEFT) {
			*g_enemy_collider[j].collision_state |= ISRIGHT;
		}
		else if (check & ISRIGHT) {
			*g_enemy_collider[j].collision_state |= ISLEFT;
		}
	}

	//�v���C���[�ƃ}�b�v�̓����蔻��
	if (CollisionObjectMap(g_player_collider->pos, g_player_collider->vel, g_player_collider->col) & ISGROUND) {
		*g_player_collider->ground_flag = TRUE;
	}
	else {
		*g_player_collider->ground_flag = FALSE;
	}

	//����ƃ}�b�v�̓����蔻��
	if (CollisionObjectMap(g_treasure_collider->pos, g_treasure_collider->vel, g_treasure_collider->col) & ISGROUND) {
		*g_treasure_collider->collision_state = TRUE;
	}
	else {
		*g_treasure_collider->collision_state = FALSE;
	}

	

	//�G�����X�^�[�ƃ}�b�v�̓����蔻��
	for (i = 0; i < ENEMY_MAX; i++) {
		if (*g_enemy_collider[i].state) {
			*g_enemy_collider[i].collision_state |= check = CollisionObjectMap(g_enemy_collider[i].pos, g_enemy_collider[i].vel, g_enemy_collider[i].col);
			if (check & ISGROUND) {
				*g_enemy_collider[i].ground_flag = TRUE;
			}
			else {
				//*g_enemy_collider[i].ground_flag = FALSE;
			}
		}
	}

	//�v���C���[�ƃI�[�u�̓����蔻��
	MR_COLLISION_MACRO3(g_player_collider, PLAYER_MAX, i, g_orb_collider, ORB_MAX, j, check) {
		//�I�[�u�����ł�����
		OrderDestroyOrb(j);
	}

	//�G�����X�^�[�ƃh���S���̉��̓����蔻��
	for (i = 0; i < FIRE_MAX; i++) {
		g_fire_collider[i].vel = *g_fire_collider[i].ride;
	}
	MR_COLLISION_MACRO3(g_enemy_collider, ENEMY_MAX, i, g_fire_collider, FIRE_MAX, j, check) {
		//�_���[�W��^����
		if (OrderDamageEnemy(i, 1))
		{
			break;
		}
	}

	//���������X�^�[�ƓG�̖��@�̓����蔻��
	MR_COLLISION_MACRO3(g_minion_collider, MINION_MAX, i, g_magic_collider, MAGIC_MAX, j, check) {
		//���������X�^�[��|���Ȃ���������ł���
		if (!OrderDamageMinion(i, OrderGetMagicPower(j))) {
			OrderDestroyMagic(j);
		}
		else {
			break;
		}
	}

	//�v���C���[�ƓG�̖��@�̓����蔻��
	MR_COLLISION_MACRO3(g_player_collider, PLAYER_MAX, i, g_magic_collider, MAGIC_MAX, j, check) {
		//�v���C���[�̃_���[�W�������Ăяo��
		OrderCollisionPlayer();
	}

	//�G�̖��@�ƃ}�b�v�̓����蔻��
	for (i = MAGIC_MAX - 1; i >= 0; i--) {
		if (*g_magic_collider[i].state) {
			if (CollisionObjectMap2(g_magic_collider[i].pos, g_magic_collider[i].vel, g_magic_collider[i].col)) {
				OrderCollisionMagic(i);
			}	
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
	BOOL mL = OrderIsWallWithPos(rect1.left,rect0.top)     || OrderIsWallWithPos(rect1.left, rect0.bottom);
	BOOL mR = OrderIsWallWithPos(rect1.right, rect0.top)   || OrderIsWallWithPos(rect1.right, rect0.bottom);
	BOOL mU = OrderIsWallWithPos(rect0.left, rect1.top)    || OrderIsWallWithPos(rect0.right, rect1.top);
	BOOL mD = OrderIsWallWithPos(rect0.left, rect1.bottom) || OrderIsWallWithPos(rect0.right, rect1.bottom);

	//�}�b�v�΂ߕ�������
	if (!mL && !mU) { mL = mU = OrderIsWallWithPos(rect1.left, rect1.top); }
	if (!mL && !mD) { mL = mD = OrderIsWallWithPos(rect1.left, rect1.bottom); }
	if (!mR && !mU) { mR = mU = OrderIsWallWithPos(rect1.right, rect1.top); }
	if (!mR && !mD) { mR = mD = OrderIsWallWithPos(rect1.right, rect1.bottom); }

	//���W���u���b�N�̉��ɍ��킹��
	if (mL && !mR) {
		tempF = ceilf(rect1.left / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->left;		//��
		if (pos->x > tempF)pos->x = tempF;
		//if (pos->x >= tempF)vel->x = tempF - pos->x;
	}
	if (!mL && mR ) {
		tempF = floorf(rect1.right / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->right;	//�E
		if (pos->x < tempF)pos->x = tempF;
		//if (pos->x < tempF)vel->x = tempF - pos->x;
	}
	if (mU && !mD) {
		tempF = ceilf(rect1.top / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->top;		//��
		if (pos->y > tempF)pos->y = tempF;
		//if (pos->y >= tempF)vel->y = tempF - pos->y;
	}
	if ((!mU || vel->y>0) && mD) {
		tempF = floorf(rect1.bottom / MAPCHIP_SIZE) * MAPCHIP_SIZE - col->bottom;	//��
		if (pos->y < tempF)pos->y = tempF;
		//if (pos->y <= tempF)vel->y = tempF - pos->y;
	}


	//����ɂ�������~����
	if (mL) if (vel->x<0)vel->x = 0;
	if (mR) if (vel->x>0)vel->x = 0;
	if (mU) if (vel->y<0)vel->y = 0;
	if (mD) if (vel->y>0)vel->y = 0;

	//�P�����ł��Փ˂��Ă�����TRUE��Ԃ�
	return mL + mR*2 + mU*4 + mD*8;
}

//�I�u�W�F�N�g�ƃ}�b�v�̓����蔻��i�ړ����j
int CollisionObjectMap2(Vector2DF *pos, Vector2DF *vel, RectF *col) {

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
	BOOL mL = OrderIsWallWithPos(rect1.left, rect0.top) || OrderIsWallWithPos(rect1.left, rect0.bottom);
	BOOL mR = OrderIsWallWithPos(rect1.right, rect0.top) || OrderIsWallWithPos(rect1.right, rect0.bottom);
	BOOL mU = OrderIsWallWithPos(rect0.left, rect1.top) || OrderIsWallWithPos(rect0.right, rect1.top);
	BOOL mD = OrderIsWallWithPos(rect0.left, rect1.bottom) || OrderIsWallWithPos(rect0.right, rect1.bottom);

	//�}�b�v�΂ߕ�������
	if (!mL && !mU) { mL = mU = OrderIsWallWithPos(rect1.left, rect1.top); }
	if (!mL && !mD) { mL = mD = OrderIsWallWithPos(rect1.left, rect1.bottom); }
	if (!mR && !mU) { mR = mU = OrderIsWallWithPos(rect1.right, rect1.top); }
	if (!mR && !mD) { mR = mD = OrderIsWallWithPos(rect1.right, rect1.bottom); }


	//�P�����ł��Փ˂��Ă�����TRUE��Ԃ�
	return mL + mR * 2 + mU * 4 + mD * 8;
}

//�I�u�W�F�N�g�Ə��������X�^�[�̓����蔻��
BOOL CollisionObjectMinions(Vector2DF *pos, RectF *col) {
	int i;
	for (i = 0; i < MINION_MAX; i++) {
		if (*g_minion_collider[i].state) {
			//�Փ˂��Ă��邩�ǂ���
			if (CollisionAABB(pos, col, g_minion_collider[i].pos, g_minion_collider[i].col)) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//�I�u�W�F�N�g�Ə��������X�^�[�̓����蔻��i�����������̂͏����j
BOOL CollisionDeleteObjectMinions(Vector2DF *pos, RectF *col) {
	BOOL ret = FALSE;
	int i;
	for (i = MINION_MAX - 1; i >= 0; i--) {
		if (*g_minion_collider[i].state) {
			//�Փ˂��Ă��邩�ǂ���
			if (CollisionAABB(pos, col, g_minion_collider[i].pos, g_minion_collider[i].col)) {
				//�Փ˂��Ă�������ł�����
				OrderDestroyMinion(i);
				ret = TRUE;
			}
		}
	}
	return ret;
}

//�I�u�W�F�N�g�ƓG�����X�^�[�̓����蔻��
BOOL CollisionObjectEnemies(Vector2DF *pos, RectF *col) {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		if (*g_enemy_collider[i].state) {
			//�Փ˂��Ă��邩�ǂ���
			if (CollisionAABB(pos, col, g_enemy_collider[i].pos, g_enemy_collider[i].col)) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//������`���m�̓����蔻��
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
				if (obj1->vel->x*obj2->vel->x > 0) {
					if (obj1->vel->x > 0) {
						(obj1->pos->x < obj2->pos->x ? obj1->vel->x : obj2->vel->x) *= tx;
					}
					else {
						(obj1->pos->x > obj2->pos->x ? obj1->vel->x : obj2->vel->x) *= tx;
					}
				}
				else {
					obj1->vel->x *= tx;
					obj2->vel->x *= tx;
				}
				//obj1�̉E���ƏՓ˂����Ȃ�
				if (obj1->pos->x < obj2->pos->x) {
					return ISRIGHT;
				}
				//obj1�̍����ƏՓ˂����Ȃ�
				else {
					return ISLEFT;
				}
			}
			//Y�����ɐ�ɏՓ˂����Ȃ�
			if (t == ty) {
				if (obj1->vel->y*obj2->vel->y > 0) {
					if (obj1->vel->y > 0) {
						(obj1->pos->y < obj2->pos->y ? obj1->vel->y : obj2->vel->y) *= ty;
					}
					else {
						(obj1->pos->y > obj2->pos->y ? obj1->vel->y : obj2->vel->y) *= ty;
					}
				}
				else {
					obj1->vel->y *= ty;
					obj2->vel->y *= ty;
				}
				//obj1�̉����ƏՓ˂����Ȃ�
				if (obj1->pos->y < obj2->pos->y) {
					return ISGROUND;
				}
				//obj1�̏㑤�ƏՓ˂����Ȃ�
				else {
					return ISCEILING;
				}
			}
		}
		else {
			if (vel.y == 0) {
				if (obj1->vel->y > 0) {
					(obj1->pos->y < obj2->pos->y ? obj1->vel->y : obj2->vel->y) = 0;
					//return ISGROUND;
				}
				else {
					(obj1->pos->y > obj2->pos->y ? obj1->vel->y : obj2->vel->y) = 0;
					//return ISCEILING;
				}
			}
			if (vel.x == 0) {
				if (obj1->vel->x > 0) {
					(obj1->pos->x < obj2->pos->x ? obj1->vel->x : obj2->vel->x) = 0;
					return ISRIGHT;
				}
				else {
					(obj1->pos->x > obj2->pos->x ? obj1->vel->x : obj2->vel->x) = 0;
					return ISLEFT;
				}
			}
		}
		return ISTRUE;
	}
	return FALSE;
}

//������`���m�̓����蔻��i�ړ����j
int CollisionMovingAABB2(BoxCollider *obj1, BoxCollider *obj2) {
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
				//obj1�̉E���ƏՓ˂����Ȃ�
				if (obj1->pos->x < obj2->pos->x) {
					return ISRIGHT;
				}
				//obj1�̍����ƏՓ˂����Ȃ�
				else {
					return ISLEFT;
				}
			}
			//Y�����ɐ�ɏՓ˂����Ȃ�
			if (t == ty) {
				//obj1�̉����ƏՓ˂����Ȃ�
				if (obj1->pos->y < obj2->pos->y) {
					return ISGROUND;
				}
				//obj1�̏㑤�ƏՓ˂����Ȃ�
				else {
					return ISCEILING;
				}
			}
		}
		else {
			if (vel.y == 0) {
				if (obj1->vel->y > 0) {
					return ISGROUND;
				}
				else {
					return ISCEILING;
				}
			}
		}
		return ISTRUE;
	}
	return FALSE;
}


//�����Ȃ���`���m�̓����蔻��
BOOL CollisionAABB(Vector2DF *pos1, RectF *col1, Vector2DF *pos2, RectF *col2) {
	if (
		fabsf(pos1->x - pos2->x) < (pos1->x < pos2->x ? col1->right - col2->left : col2->right - col1->left) &&
		fabsf(pos1->y - pos2->y) < (pos1->y < pos2->y ? col1->bottom - col2->top : col2->bottom - col1->top)
		)
	{
		return TRUE;
	}

	return FALSE;
}
