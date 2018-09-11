#pragma once


//�O���Ɍ��J����萔�̒�`

// <�V�X�e��> ----------------------------------------------------------
#define GAME_TITLE "�h���A�[�K�̖��{"        // �Q�[���^�C�g��


// <���> --------------------------------------------------------------
#define SCREEN_WIDTH    (800)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (600)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

//�}�b�v�֌W
#define MAP_WIDTH_MAX	(20)	//�}�b�v�̍ő剡��
#define MAP_HEIGHT_MAX	(20)	//�}�b�v�̍ő�c��

#define MAPCHIP_SIZE		(64)	//�}�b�v�`�b�v�̑傫��
#define MAPCHIP_SIZE_HALF	(32)	//�}�b�v�`�b�v�̑傫���̔���


//�t�B�[���h�֌W
#define FIELD_WIDTH    (MAP_WIDTH_MAX * MAPCHIP_SIZE)                  // �t�B�[���h�̕�[pixel]
#define FIELD_HEIGHT   (MAP_HEIGHT_MAX * MAPCHIP_SIZE)                 // �t�B�[���h�̍���[pixel]

#define FIELD_CENTER_X (FIELD_WIDTH  / 2)    // �t�B�[���h�̒���(X���W)
#define FIELD_CENTER_Y (FIELD_HEIGHT / 2)    // �t�B�[���h�̒���(Y���W)


//���w�E�����֌W
#define PI	(DX_PI_F)	//�~����
#define PI2	(PI * 2)	//�~����*2

#define GRAVITY		(2.0f)	//�d��

#define ISLEFT		(1)		//�����ɐڂ��Ă��邩�̃}�N��
#define ISRIGHT		(2)		//�E���ɐڂ��Ă��邩�̃}�N��
#define ISCEILING	(4)		//�V��i�㑤�j�ɐڂ��Ă��邩�̃}�N��
#define ISGROUND	(8)		//�n�ʁi�����j�ɐڂ��Ă��邩�̃}�N��
#define ISTRUE		(16)	//TRUE��ISLEFT�̋������p


//UI�֌W
#define CURSOR_SPEED	(15)	//�J�[�\���𓮂������Ԃ̊Ԋu


//�v���C���[�֌W
#define PLAYER_MAX	(1)		//�v���C���[�̐�

#define PLAYER_WALK_SPEED	(5)		//�v���C���[�̈ړ����x
#define PLAYER_JUMP_SPEED	(-22)	//�v���C���[�̃W�����v���x


//���������X�^�[�֌W
#define MINION_MAX	(20)	//�����ł��郂���X�^�[�̍ő吔

//�h���S���̉��֌W
#define FIRE_MAX	(5)		//�h���S���̉��̍ő�o����


//����֌W
#define TREASURE_MAX	(1)		//����̐�







