////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////! @file   GameLibMath.h
////!
////! @brief  DxLib�̐��w�֘A�ւ̒ǉ��@�\�̃w�b�_�t�@�C��
////!
////! @date   2018/7/1
////!
////! @author ********
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//// ���d�C���N���[�h�̖h�~ ==================================================
//#pragma once
//
//
//
//
//// �w�b�_�t�@�C���̓ǂݍ��� ================================================
//#include <minwindef.h>
//
//
//
//
//// �^�̒�` ================================================================
//
//// <2D�̃x�N�g��> ------------------------------------------------------
//struct tag_Vector2D
//{
//	float x;    // X����
//	float y;    // Y����
//};
//typedef struct tag_Vector2D Vector2D;
//
//
//// <2D�̃T�C�Y> --------------------------------------------------------
//struct tag_Size2D
//{
//	float width;     // ��
//	float height;    // ����
//};
//typedef struct tag_Size2D Size2D;
//
//
//// <2D�̋�`> ----------------------------------------------------------
//struct tag_Rect2D
//{
//	float x;         // ���㒸�_��X���W
//	float y;         // ���㒸�_��Y���W
//	float width;     // ��
//	float height;    // ����
//};
//typedef struct tag_Rect2D Rect2D;
//
//
//// <2D�͈̔�> ----------------------------------------------------------
//struct tag_Bounds2D
//{
//	float left;      // ���[
//	float top;       // ��[
//	float right;     // �E�[
//	float bottom;    // ���[
//};
//typedef struct tag_Bounds2D Bounds2D;
//
//
//// <��{�`��> ----------------------------------------------------------
//// 2D�̓_
//typedef Vector2D Point2D;
//
//
//// 2D�̒���
//struct tag_Line2D
//{
//	Point2D  p;    // �����̒ʂ�_
//	Vector2D v;    // �����x�N�g��
//};
//typedef struct tag_Line2D Line2D;
//
//
//// 2D�̐���
//struct tag_Segment2D
//{
//	Point2D  start;    // �n�_
//	Point2D  end;      // �I�_
//};
//typedef struct tag_Segment2D Segment2D;
//
//
//// 2D�̉~
//struct tag_Circle2D
//{
//	Point2D center;    // ���S���W
//	float   radius;    // ���a
//};
//typedef struct tag_Circle2D Circle2D;
//
//
//// 2D�̎O�p�`
//struct tag_Triangle2D
//{
//	Point2D vertices[3];    // ���_
//};
//typedef struct tag_Triangle2D Triangle2D;
//
//
//// 2D�̔��`
//struct tag_Box2D
//{
//	Point2D center;    // ���S���W
//	Size2D  size;      // �T�C�Y
//};
//typedef struct tag_Box2D Box2D;
//
//
//// 2D�̃J�v�Z��
//struct tag_Capsule2D
//{
//	Segment2D segment;    // ����
//	float     radius;     // ���a
//};
//typedef struct tag_Capsule2D Capsule2D;
//
//
//
//
//// �֐��̐錾 ==============================================================
//
//// <�p�x�̒P�ʕϊ�> ----------------------------------------------------
//
//// [�x]����[���W�A��]�ւ̒P�ʕϊ�
//float ToRadians(float degree);
//
//// [���W�A��]����[�x]�ւ̒P�ʕϊ�
//float ToDegrees(float radian);
//
//
//
//// <���l> --------------------------------------------------------------
//
//// �w�肵���l�������`����͈͓̔��Ɏ��߂�
//int   ClampI(int   x, int   min, int   max);
//float ClampF(float x, float min, float max);
//
//// ���������_���^�̌덷���l���ɓ��ꂽ��r
//BOOL FloatEquals(float a, float b);
//
//
//
//// <����> --------------------------------------------------------------
//// 2D�̃x�N�g���̐���
//Vector2D CreateVector2D(float x, float y);
//
//// 2D�̃T�C�Y�̐���
//Size2D CreateSize2D(float width, float height);
//
//// 2D�̋�`�̐���
//Rect2D CreateRect2D(float x, float y, float width, float height);
//
//// 2D�͈̔͂̐���
//Bounds2D CreateBounds2D(float left, float top, float right, float bottom);
//
//// 2D�̓_�̐���
//Point2D CreatePoint2D(float x, float y);
//
//// 2D�̒����̐���
//Line2D CreateLine2D(Point2D p, Vector2D v);
//Line2D CreateLine2D(float px, float py, float vx, float vy);
//
//// 2D�̐����̐���
//Segment2D CreateSegment2D(Point2D start, Point2D end);
//Segment2D CreateSegment2D(float sx, float sy, float ex, float ey);
//
//// 2D�̉~�̐���
//Circle2D CreateCircle2D(Point2D center, float radius);
//Circle2D CreateCircle2D(float cx, float cy, float radius);
//
//// 2D�̎O�p�`�̐���
//Triangle2D CreateTriangle2D(Point2D p1, Point2D p2, Point2D p3);
//Triangle2D CreateTriangle2D(float x1, float y1, float x2, float y2, float x3, float y3);
//
//// 2D�̔��`�̐���
//Box2D CreateBox2D(Point2D center, Size2D size);
//Box2D CreateBox2D(float cx, float cy, float width, float height);
//
//// 2D�̃J�v�Z���̐���
//Capsule2D CreateCapsule2D(Segment2D segment, float radius);
//Capsule2D CreateCapsule2D(Point2D p1, Point2D p2, float radius);
//Capsule2D CreateCapsule2D(float x1, float y1, float x2, float y2, float radius);
