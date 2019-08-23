////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////! @file   GameLibGraphics.cpp
////!
////! @brief  DxLib�̃O���t�B�b�N�֘A�ւ̒ǉ��@�\�̃\�[�X�t�@�C��
////!
////! @date   2017/3/27
////!
////! @author ********
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//// �w�b�_�t�@�C���̓ǂݍ��� ================================================
//#include <DxLib.h>
//#include <math.h>
//#include <stdio.h>
//
//
//
//
//// �萔�̒�` ==============================================================
//#define NUM_CAPSULE_DIVISION (16)    // �J�v�Z���`��ɂ����锼�~�̕�����
//
//
//
//
//// �֐��̒�` ==============================================================
//
////----------------------------------------------------------------------
////! @brief �j����`��
////!
////! @param[in] x1        �`�悷����̋N�_���W(X���W)
////! @param[in] y1        �`�悷����̋N�_���W(Y���W)
////! @param[in] x2        �`�悷����̏I�_���W(X���W)
////! @param[in] y2        �`�悷����̏I�_���W(Y���W)
////! @param[in] color     �`�����̐F
////! @param[in] length    �j���̒�������ъԊu�̕�
////! @param[in] thickness ���̑���
////!
////! @retval  0 ����
////! @retval -1 �G���[����
////----------------------------------------------------------------------
//int DrawDashedLine(int x1, int y1, int x2, int y2, unsigned int color, int length, int thickness)
//{
//	int vx = x2 - x1;
//	int vy = y2 - y1;
//
//	double angle = atan2(vy, vx);
//	float dx = (float)(length * cos(angle));
//	float dy = (float)(length * sin(angle));
//
//	int count = (int)(sqrt(vx * vx + vy * vy) / length);
//
//	float x = (float)x1;
//	float y = (float)y1;
//
//	for (int i = 0; i < count; i += 2)
//	{
//		if (DrawLine((int)x, (int)y, (int)(x + dx), (int)(y + dy), color, thickness) == -1)
//		{
//			return -1;
//		}
//		x += dx * 2;
//		y += dy * 2;
//	}
//
//	if (count % 2 == 0)
//	{
//		if (DrawLine((int)x, (int)y, x2, y2, color, thickness) == -1)
//		{
//			return -1;
//		}
//	}
//
//	return 0;
//}
//
//
//
////----------------------------------------------------------------------
////! @brief �j����`��(�A���`�G�C���A�X���ʕt��)
////!
////! @param[in] x1        �`�悷����̋N�_���W(X���W)
////! @param[in] y1        �`�悷����̋N�_���W(Y���W)
////! @param[in] x2        �`�悷����̏I�_���W(X���W)
////! @param[in] y2        �`�悷����̏I�_���W(Y���W)
////! @param[in] color     �`�����̐F
////! @param[in] length    �j���̒�������ъԊu�̕�
////! @param[in] thickness ���̑���
////!
////! @retval  0 ����
////! @retval -1 �G���[����
////----------------------------------------------------------------------
//int DrawDashedLineAA(float x1, float y1, float x2, float y2, unsigned int color, float length, float thickness)
//{
//	float vx = x2 - x1;
//	float vy = y2 - y1;
//
//	double angle = atan2(vy, vx);
//	float dx = (float)(length * cos(angle));
//	float dy = (float)(length * sin(angle));
//
//	int count = (int)(sqrt(vx * vx + vy * vy) / length);
//
//	float x = x1;
//	float y = y1;
//
//	for (int i = 0; i < count; i += 2)
//	{
//		if (DrawLineAA(x, y, (x + dx), (y + dy), color, thickness) == -1)
//		{
//			return -1;
//		}
//		x += dx * 2;
//		y += dy * 2;
//	}
//
//	if (count % 2 == 0)
//	{
//		if (DrawLineAA(x, y, x2, y2, color, thickness) == -1)
//		{
//			return -1;
//		}
//	}
//
//	return 0;
//}
//
//
//
////----------------------------------------------------------------------
////! @brief �J�v�Z����`��
////!
////! @param[in] x1        ����̉~�̒��S���W(X���W)
////! @param[in] y1        ����̉~�̒��S���W(Y���W)
////! @param[in] x2        ��������̉~�̒��S���W(X���W)
////! @param[in] y2        ��������̉~�̒��S���W(Y���W)
////! @param[in] color     �`�����̐F
////! @param[in] thickness ���̑���
////!
////! @retval  0 ����
////! @retval -1 �G���[����
////----------------------------------------------------------------------
//int DrawCapsule(int x1, int y1, int x2, int y2, int r, unsigned int color, int thickness)
//{
//	int vx = x2 - x1;
//	int vy = y2 - y1;
//
//	double angle = atan2(vy, vx) + (DX_PI / 2);
//
//	float dx[NUM_CAPSULE_DIVISION + 1];
//	float dy[NUM_CAPSULE_DIVISION + 1];
//	int i;
//
//	for (i = 0; i < NUM_CAPSULE_DIVISION + 1; i++)
//	{
//		dx[i] = (float)(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
//		dy[i] = (float)(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
//	}
//
//
//	if (DrawLine((int)(x1 + dx[0]), (int)(y1 + dy[0]), (int)(x2 + dx[0]), (int)(y2 + dy[0]), color, thickness))
//	{
//		return -1;
//	}
//
//	if (DrawLine((int)(x1 + dx[NUM_CAPSULE_DIVISION]), (int)(y1 + dy[NUM_CAPSULE_DIVISION]), (int)(x2 + dx[NUM_CAPSULE_DIVISION]), (int)(y2 + dy[NUM_CAPSULE_DIVISION]), color, thickness))
//	{
//		return -1;
//	}
//
//
//	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
//	{
//		if (DrawLine((int)(x1 + dx[i]), (int)(y1 + dy[i]), (int)(x1 + dx[i + 1]), (int)(y1 + dy[i + 1]), color, thickness))
//		{
//			return -1;
//		}
//	}
//
//	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
//	{
//		if (DrawLine((int)(x2 - dx[i]), (int)(y2 - dy[i]), (int)(x2 - dx[i + 1]), (int)(y2 - dy[i + 1]), color, thickness))
//		{
//			return -1;
//		}
//	}
//
//	return 0;
//}
//
//
//
////----------------------------------------------------------------------
////! @brief �J�v�Z����`��(�A���`�G�C���A�X���ʕt��)
////!
////! @param[in] x1        ����̉~�̒��S���W(X���W)
////! @param[in] y1        ����̉~�̒��S���W(Y���W)
////! @param[in] x2        ��������̉~�̒��S���W(X���W)
////! @param[in] y2        ��������̉~�̒��S���W(Y���W)
////! @param[in] color     �`�����̐F
////! @param[in] thickness ���̑���
////!
////! @retval  0 ����
////! @retval -1 �G���[����
////----------------------------------------------------------------------
//int DrawCapsuleAA(float x1, float y1, float x2, float y2, float r, unsigned int color, float thickness)
//{
//	float vx = x2 - x1;
//	float vy = y2 - y1;
//
//	double angle = atan2(vy, vx) + (DX_PI / 2);
//
//	float dx[NUM_CAPSULE_DIVISION+1];
//	float dy[NUM_CAPSULE_DIVISION+1];
//	int i;
//
//	for (i = 0; i < NUM_CAPSULE_DIVISION+1; i++)
//	{
//		dx[i] = (float)(r * cos(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
//		dy[i] = (float)(r * sin(angle + DX_PI_F / NUM_CAPSULE_DIVISION * i));
//	}
//
//
//	if (DrawLineAA(x1 + dx[0], y1 + dy[0], x2 + dx[0], y2 + dy[0], color, thickness))
//	{
//		return -1;
//	}
//
//	if (DrawLineAA(x1 + dx[NUM_CAPSULE_DIVISION], y1 + dy[NUM_CAPSULE_DIVISION], x2 + dx[NUM_CAPSULE_DIVISION], y2 + dy[NUM_CAPSULE_DIVISION], color, thickness))
//	{
//		return -1;
//	}
//
//
//	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
//	{
//		if (DrawLineAA(x1 + dx[i], y1 + dy[i], x1 + dx[i + 1], y1 + dy[i + 1], color, thickness))
//		{
//			return -1;
//		}
//	}
//
//	for (i = 0; i < NUM_CAPSULE_DIVISION; i++)
//	{
//		if (DrawLineAA(x2 - dx[i], y2 - dy[i], x2 - dx[i + 1], y2 - dy[i + 1], color, thickness))
//		{
//			return -1;
//		}
//	}
//
//	return 0;
//}
//
//
//
////----------------------------------------------------------------------
////! @brief �摜�t�@�C���̃������ւ̓ǂ݂���(�G���[�����t��)
////!
////! @param[in] filename �ǂݍ��ݑΏۂ̉摜�t�@�C���̖��O
////!
////! @retval -1�ȊO �O���t�B�b�N�̃n���h��
////! @retval -1     �G���[����
////----------------------------------------------------------------------
//int LoadGraphWithErrorHandling(const char* filename)
//{
//	HGRP imageHandle = LoadGraph(filename);
//
//	if (imageHandle == -1)
//	{
//		char errorMessage[MAX_PATH];
//		snprintf(errorMessage, sizeof(errorMessage), "�ȉ��̃t�@�C����������܂���B\n\"%s\"", filename);
//		MessageBox(NULL, errorMessage, NULL, MB_OK | MB_ICONEXCLAMATION);
//		ExitGame();
//	}
//
//	return imageHandle;
//}
