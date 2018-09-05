//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.h
//!
//! @brief  �}�b�v�֘A�̃w�b�_�t�@�C��
//!
//! @date   2018/08/23
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�}�b�v�̏�����
void InitializeMap();

//�J�����̃I�t�Z�b�g���v�Z����
void UpdateCameraOffset();

//�}�b�v�̕`��
void DrawMap();

//�}�b�v���擾����
MapData GetMap();

//�w�肵�����W���}�b�v���W�ɕϊ�����
void GetMapPosWithPos(Vector2DF pos, int *x, int *y);

//�w�肵���}�b�v���W�����W�ɕϊ�����
Vector2DF GetPosWithMapPos(int x, int y);

//�w�肵�����W���ʉߕs�}�X���ǂ���
BOOL IsWallWithPos(float x, float y);

//�J�����̃I�t�Z�b�g���擾����
Vector2DF GetCameraOffset();

//�}�b�v�O�ɂ��邩�̔���
BOOL IsOutsideMap(Vector2DF *pos, RectF *col);

//��ʉ��ɂ��邩�̔���
BOOL IsUnderMap(Vector2DF *pos, RectF *col);


