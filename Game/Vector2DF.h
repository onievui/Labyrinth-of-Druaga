//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Vector2DF.h
//!
//! @brief  �񎟃x�N�g���f�[�^�̃w�b�_�t�@�C��
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�񎟃x�N�g���\����
struct Vector2DF {
	float x;
	float y;

};

//�ړ��ʌv�Z
void CalcVector2DF(Vector2DF &vel, const float &speed, const float &angle);

//�񎟃x�N�g���̉��Z
void AddVector2DF(Vector2DF &vec1, const Vector2DF &vec2);

//�񎟃x�N�g���̌��Z
void SubVector2DF(Vector2DF &vec1, const Vector2DF &vec2);

//�񎟃x�N�g���ɃX�J���[���|����
void  MulVector2DF(Vector2DF &vec, const float &mul);

//4�̓񎟃x�N�g���Ɋe�v�f�����
void SetVector2DF4(Vector2DF vec[], float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

