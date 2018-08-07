//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Vector2DF.cpp
//!
//! @brief  �񎟃x�N�g���f�[�^�̏���
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Vector2DF.h"
#include <math.h>


//�ړ��ʌv�Z
void CalcVector2DF(Vector2DF &vel, const float &speed, const float &angle) {
	vel.x = cosf(angle)*speed;
	vel.y = sinf(angle)*speed;
}

//�񎟃x�N�g���̉��Z
void AddVector2DF(Vector2DF &vec1, const Vector2DF &vec2) {
	vec1.x += vec2.x;
	vec1.y += vec2.y;
}

//�񎟃x�N�g���̌��Z
void SubVector2DF(Vector2DF &vec1, const Vector2DF &vec2) {
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
}

//�񎟃x�N�g���ɃX�J���[���|����
void  MulVector2DF(Vector2DF &vec, const float &mul) {
	vec.x *= mul;
	vec.y *= mul;
}

//4�̓񎟃x�N�g���Ɋe�v�f�����
void SetVector2DF4(Vector2DF vec[], float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	vec[0].x = x1;
	vec[0].y = y1;
	vec[1].x = x2;
	vec[1].y = y2;
	vec[2].x = x3;
	vec[2].y = y3;
	vec[3].x = x4;
	vec[3].y = y4;
}

