//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLibMath.cpp
//!
//! @brief  DxLib�̐��w�֘A�ւ̒ǉ��@�\�̃\�[�X�t�@�C��
//!
//! @date   2017/3/27
//!
//! @author ********
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <float.h>
#include <math.h>
#include <DxLib.h>




// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �p�x�̒P�ʕϊ�([�x]��[���W�A��])
//!
//! @param[in] degree �p�x[�x]
//!
//! @return �p�x[���W�A��]
//----------------------------------------------------------------------
float ToRadians(float degree)
{
	return degree * DX_PI_F / 180.0f;
}



//----------------------------------------------------------------------
//! @brief �p�x�̒P�ʕϊ�([���W�A��]��[�x])
//!
//! @param[in] radian �p�x[���W�A��]
//!
//! @return �p�x[�x]
//----------------------------------------------------------------------
float ToDegrees(float radian)
{
	return radian * 180.0f / DX_PI_F;
}



//----------------------------------------------------------------------
//! @brief �w�肵���l�������`����͈͓̔��Ɏ��߂�(int�^��)
//!
//! @param[in] x   �͈͓��Ɏ��߂����l�̌��ݒl
//! @param[in] min ����
//! @param[in] max ���
//!
//! @return �����`����͈͓̔��Ɏ��߂��l
//----------------------------------------------------------------------
int ClampI(int x, int min, int max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}



//----------------------------------------------------------------------
//! @brief �w�肵���l���A�����`����͈͓̔��Ɏ��߂�(float�^��)
//!
//! @param[in] x   �͈͓��Ɏ��߂����l�̌��ݒl 
//! @param[in] min ����
//! @param[in] max ���
//!
//! @return �����`����͈͓̔��Ɏ��߂��l
//----------------------------------------------------------------------
float ClampF(float x, float min, float max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}



//----------------------------------------------------------------------
//! @brief ���������_���^�̌덷���l���ɓ��ꂽ��r
//!
//! @param[in] a ��r�Ώۂ̒l
//! @param[in] b ��r�Ώۂ̒l
//!
//! @retval TRUE  �덷���w��͈�(FLT_EPSILON)�ȓ��̏ꍇ
//! @retval FALSE ����ȊO�̏ꍇ
//----------------------------------------------------------------------
BOOL FloatEquals(float a, float b)
{
	if (fabsf(a - b) < FLT_EPSILON)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



//----------------------------------------------------------------------
//! @brief 2D�̃x�N�g���̐���
//!
//! @param[in] x �x�N�g����X����
//! @param[in] y �x�N�g����Y����
//!
//! @retval �������ꂽ2D�̃x�N�g��
//----------------------------------------------------------------------
Vector2D CreateVector2D(float x, float y)
{
	Vector2D v = { x, y };

	return v;
}



//----------------------------------------------------------------------
//! @brief 2D�̃T�C�Y�̐���
//!
//! @param[in] width  �T�C�Y�̕�
//! @param[in] height �T�C�Y�̍���
//!
//! @retval �������ꂽ2D�̐��@
//----------------------------------------------------------------------
Size2D CreateSize2D(float width, float height)
{
	Size2D size = { width, height };

	return size;
}



//----------------------------------------------------------------------
//! @brief 2D�̋�`�̐���
//!
//! @param[in] x      ��`�̍��㒸�_��X���W
//! @param[in] y      ��`�̍��㒸�_��Y���W
//! @param[in] width  ��`�̕�
//! @param[in] height ��`�̍���
//!
//! @retval �������ꂽ2D�̋�`
//----------------------------------------------------------------------
Rect2D CreateRect2D(float x, float y, float width, float height)
{
	Rect2D rect = { x, y, width, height };

	return rect;
}



//----------------------------------------------------------------------
//! @brief 2D�͈̔͂̐���
//!
//! @param[in] left   �͈͂̍��[
//! @param[in] top    �͈͂̏�[
//! @param[in] right  �͈͂̉E�[
//! @param[in] bottom �͈͂̉��[
//!
//! @retval �������ꂽ2D�͈̔�
//----------------------------------------------------------------------
Bounds2D CreateBounds2D(float left, float top, float right, float bottom)
{
	Bounds2D bounds = { left, top, right, bottom };

	return bounds;
}



//----------------------------------------------------------------------
//! @brief 2D�̓_�̐���
//!
//! @param[in] x �_��X���W
//! @param[in] y �_��Y���W
//!
//! @retval �������ꂽ2D�̓_
//----------------------------------------------------------------------
Point2D CreatePoint2D(float x, float y)
{
	Point2D point = { x, y };

	return point;
}



//----------------------------------------------------------------------
//! @brief 2D�̒����̐���
//!
//! @param[in] p �����̒ʂ�_
//! @param[in] v �����x�N�g�� 
//!
//! @retval �������ꂽ2D�̒���
//----------------------------------------------------------------------
Line2D CreateLine2D(Point2D p, Vector2D v)
{
	Line2D line = { p, v };

	return line;
}



//----------------------------------------------------------------------
//! @brief 2D�̒����̐���
//!
//! @param[in] px �����̒ʂ�_��X���W
//! @param[in] py �����̒ʂ�_��Y���W
//! @param[in] vx �����x�N�g����X����
//! @param[in] vy �����x�N�g����Y����
//!
//! @retval �������ꂽ2D�̒���
//----------------------------------------------------------------------
Line2D CreateLine2D(float px, float py, float vx, float vy)
{
	return CreateLine2D(CreatePoint2D(px, py), CreateVector2D(vx, vy));
}



//----------------------------------------------------------------------
//! @brief 2D�̐����̐���
//!
//! @param[in] start �����̎n�_
//! @param[in] end   �����̏I�_
//!
//! @retval �������ꂽ2D�̐���
//----------------------------------------------------------------------
Segment2D CreateSegment2D(Point2D start, Point2D end)
{
	Segment2D segment = { start, end };

	return segment;
}



//----------------------------------------------------------------------
//! @brief 2D�̐����̐���
//!
//! @param[in] sx �����̎n�_��X���W
//! @param[in] sy �����̎n�_��Y���W
//! @param[in] ex �����̏I�_��X���W
//! @param[in] ey �����̏I�_��Y���W
//!
//! @retval �������ꂽ2D�̐���
//----------------------------------------------------------------------
Segment2D CreateSegment2D(float sx, float sy, float ex, float ey)
{
	return CreateSegment2D(CreatePoint2D(sx, sy), CreatePoint2D(ex, ey));
}



//----------------------------------------------------------------------
//! @brief 2D�̉~�̐���
//!
//! @param[in] center �~�̒��S���W
//! @param[in] radius �~�̔��a
//!
//! @retval �������ꂽ2D�̉~
//----------------------------------------------------------------------
Circle2D CreateCircle2D(Point2D center, float radius)
{
	Circle2D circle = { center, radius };

	return circle;
}



//----------------------------------------------------------------------
//! @brief 2D�̉~�̐���
//!
//! @param[in] cx     �~�̒��S��X���W
//! @param[in] cy     �~�̒��S��Y���W
//! @param[in] radius �~�̔��a
//!
//! @retval �������ꂽ2D�̉~
//----------------------------------------------------------------------
Circle2D CreateCircle2D(float cx, float cy, float radius)
{
	return CreateCircle2D(CreatePoint2D(cx, cy), radius);
}



//----------------------------------------------------------------------
//! @brief 2D�̎O�p�`�̐���
//!
//! @param[in] p1 �O�p�`��1�߂̒��_�̍��W
//! @param[in] p2 �O�p�`��2�߂̒��_�̍��W
//! @param[in] p3 �O�p�`��3�߂̒��_�̍��W
//!
//! @retval �������ꂽ2D�̎O�p�`
//----------------------------------------------------------------------
Triangle2D CreateTriangle2D(Point2D p1, Point2D p2, Point2D p3)
{
	Triangle2D triangle = { {p1, p2, p3} };

	return triangle;
}



//----------------------------------------------------------------------
//! @brief 2D�̎O�p�`�̐���
//!
//! @param[in] x1 �O�p�`��1�߂̒��_��X���W
//! @param[in] y1 �O�p�`��1�߂̒��_��Y���W
//! @param[in] x2 �O�p�`��2�߂̒��_��X���W
//! @param[in] y2 �O�p�`��2�߂̒��_��Y���W
//! @param[in] x3 �O�p�`��3�߂̒��_��X���W 
//! @param[in] y3 �O�p�`��3�߂̒��_��Y���W 
//!
//! @retval �������ꂽ2D�̎O�p�`
//----------------------------------------------------------------------
Triangle2D CreateTriangle2D(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return CreateTriangle2D(CreatePoint2D(x1, y1), CreatePoint2D(x2, y2), CreatePoint2D(x3, y3));
}



//----------------------------------------------------------------------
//! @brief 2D�̔��`�̐���
//!
//! @param[in] center ���`�̒��S���W
//! @param[in] size   ���`�̃T�C�Y
//!
//! @retval �������ꂽ2D�̔��`
//----------------------------------------------------------------------
Box2D CreateBox2D(Point2D center, Size2D size)
{
	Box2D box = { center, size };

	return box;
}



//----------------------------------------------------------------------
//! @brief 2D�̔��^�̐���
//!
//! @param[in] cx     ���`�̒��S��X���W
//! @param[in] cy     ���`�̒��S��Y���W
//! @param[in] width  ���`�̕�
//! @param[in] height ���`�̍���
//!
//! @retval �������ꂽ2D�̔��`
//----------------------------------------------------------------------
Box2D CreateBox2D(float cx, float cy, float width, float height)
{
	return CreateBox2D(CreatePoint2D(cx, cy), CreateSize2D(width, height));
}



//----------------------------------------------------------------------
//! @brief 2D�̃J�v�Z���̐���
//!
//! @param[in] segment �J�v�Z���̗��[�̉~�̒��S�����Ԑ���
//! @param[in] radius  �J�v�Z���̗��[�̉~�̔��a
//!
//! @retval �������ꂽ2D�̃J�v�Z��
//----------------------------------------------------------------------
Capsule2D CreateCapsule2D(Segment2D segment, float radius)
{
	Capsule2D capsule = { segment, radius };

	return capsule;
}



//----------------------------------------------------------------------
//! @brief 2D�̃J�v�Z���̐���
//!
//! @param[in] p1     �J�v�Z���̈���̉~�̒��S���W
//! @param[in] p2     �J�v�Z���̂�������̉~�̒��S���W
//! @param[in] radius �J�v�Z���̗��[�̉~�̔��a
//!
//! @retval �������ꂽ2D�̃J�v�Z��
//----------------------------------------------------------------------
Capsule2D CreateCapsule2D(Point2D p1, Point2D p2, float radius)
{
	return CreateCapsule2D(CreateSegment2D(p1, p2), radius);
}



//----------------------------------------------------------------------
//! @brief 2D�̃J�v�Z���̐���
//!
//! @param[in] x1     �J�v�Z���̈���̉~�̒��S��X���W
//! @param[in] y1     �J�v�Z���̈���̉~�̒��S��Y���W
//! @param[in] x2     �J�v�Z���̂�������̉~�̒��S��X���W
//! @param[in] y2     �J�v�Z���̂�������̉~�̒��S��Y���W
//! @param[in] radius �J�v�Z���̗��[�̉~�̔��a
//!
//! @retval �������ꂽ2D�̃J�v�Z��
//----------------------------------------------------------------------
Capsule2D CreateCapsule2D(float x1, float y1, float x2, float y2, float radius)
{
	return CreateCapsule2D(CreateSegment2D(CreatePoint2D(x1, y1), CreatePoint2D(x2, y2)), radius);
}
