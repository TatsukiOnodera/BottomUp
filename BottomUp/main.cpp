#include "DxLib.h"
#include "Character.h"
#include "Item.h"
#include "Stage.h"
#include "Poison.h"

const char TITLE[] = "Bottom Up";

const int WIN_WIDTH = 1500; //�E�B���h�E����
const int WIN_HEIGHT = 844; //�E�B���h�E�c��


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(0.8);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0, 0, 255);		// ��ʂ̔w�i�F��ݒ肷��
	//ChangeWindowMode(1);		//�t���X�N���[��
	SetMouseDispFlag(TRUE);				//�}�E�X�\��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int soundHandle[9];
	soundHandle[0] = LoadSoundMem("�X�^�[�gBGM.mp3");
	soundHandle[1] = LoadSoundMem("�X�e�[�WBGM.mp3");
	soundHandle[2] = LoadSoundMem("�Z���N�gSE.mp3");
	soundHandle[3] = LoadSoundMem("����.mp3");
	soundHandle[4] = LoadSoundMem("�v�C�ő���.mp3");
	soundHandle[5] = LoadSoundMem("�x�񂪖�.mp3");
	soundHandle[6] = LoadSoundMem("�u���Ⴀ���[�[�I�v.mp3");
	soundHandle[7] = LoadSoundMem("�Q�[���N���ABGM.mp3");
	soundHandle[8] = LoadSoundMem("�Q�[���I�[�o�[BGM.mp3");

	int graphHandle[9];
	graphHandle[0] = LoadGraph("back1.png");
	graphHandle[1] = LoadGraph("back2.png");
	graphHandle[2] = LoadGraph("back3.png");
	graphHandle[3] = LoadGraph("characterStand.png");
	graphHandle[4] = LoadGraph("characterWalk.png");
	graphHandle[5] = LoadGraph("characterUp.png");
	graphHandle[6] = LoadGraph("block.png");
	graphHandle[7] = LoadGraph("ladder.png");
	graphHandle[8] = LoadGraph("wall.png");

	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���
	int mouse = 0;
	int oldMouse = 0;

	int cursorX = 0;
	int cursorY = 0;

	int isStart = 1;
	int isOperation = 0;
	int isGame = 0;
	int isGameClear = 0;
	int isGameOver = 0;
	int count = 0;
	int alpha = 255;

	int map[96][20] = { {4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4}
										,{4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4} };

	Character* character = new Character;
	Item* item = new Item;
	Stage* stage = new Stage;
	Poison* poison = new Poison;

	ChangeVolumeSoundMem(100, soundHandle[0]);
	ChangeVolumeSoundMem(100, soundHandle[1]);
	ChangeVolumeSoundMem(100, soundHandle[2]);
	ChangeVolumeSoundMem(100, soundHandle[3]);
	ChangeVolumeSoundMem(100, soundHandle[4]);
	ChangeVolumeSoundMem(100, soundHandle[5]);
	ChangeVolumeSoundMem(100, soundHandle[6]);
	ChangeVolumeSoundMem(100, soundHandle[7]);
	ChangeVolumeSoundMem(100, soundHandle[8]);

	// �Q�[�����[�v
	while (1)
	{
		//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		oldMouse = mouse;
		mouse = 0;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
		{
			mouse = 1;
		}

		//�ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//�}�E�X���W
		GetMousePoint(&cursorX, &cursorY);

		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//
		//���͏���
		if (isStart == 1)
		{
			if (count >= 2)
			{
				if (mouse == 1 && oldMouse == 0)
				{
					isStart = 0;
					isOperation = 1;
					if (CheckSoundMem(soundHandle[2]) == 0)
					{
						PlaySoundMem(soundHandle[2], DX_PLAYTYPE_NORMAL, 1);
					}
				}
				count = 0;
			}
			count++;
		}
		if (isOperation == 1)
		{
			if (count >= 2)
			{
				if (mouse == 1 && oldMouse == 0)
				{
					isOperation = 0;
					isGame = 1;
					if (CheckSoundMem(soundHandle[2]) == 0)
					{
						PlaySoundMem(soundHandle[2], DX_PLAYTYPE_NORMAL, 1);
					}
				}
				count = 0;
			}
			count++;
		}
		if (isGame == 1)
		{
			item->carry(mouse, oldMouse);
			item->put(cursorX, cursorY, mouse, oldMouse, map, stage, soundHandle[3]);
		}
		if (isGameClear == 1)
		{
			character->reset();
			item->reset();
			stage->reset();
			if (count >= 2)
			{
				if (mouse == 1 && oldMouse == 0)
				{
					isGameClear = 0;
					isStart = 1;
					count = 0;
					alpha = 255;
					if (CheckSoundMem(soundHandle[2]) == 0)
					{
						PlaySoundMem(soundHandle[2], DX_PLAYTYPE_NORMAL, 1);
					}
				}
			}
			count++;
		}
		if (isGameOver == 1)
		{
			character->reset();
			item->reset();
			stage->reset();
			if (count >= 2)
			{
				if (mouse == 1 && oldMouse == 0)
				{
					isGameOver = 0;
					isStart = 1;
					count = 0;
					alpha = 255;
					if (CheckSoundMem(soundHandle[2]) == 0)
					{
						PlaySoundMem(soundHandle[2], DX_PLAYTYPE_NORMAL, 1);
					}
				}
			}
			count++;
		}

		//�X�V����
		if (isStart == 1 || isOperation == 1)
		{
			if (CheckSoundMem(soundHandle[0]) == 0)
			{
				PlaySoundMem(soundHandle[0], DX_PLAYTYPE_BACK, 1);
			}
			if (CheckSoundMem(soundHandle[0]) == 1)
			{
				StopSoundMem(soundHandle[7]);
			}
			if (CheckSoundMem(soundHandle[0]) == 1)
			{
				StopSoundMem(soundHandle[8]);
			}
		}
		if (isGame == 1)
		{
			if (CheckSoundMem(soundHandle[1]) == 0)
			{
				PlaySoundMem(soundHandle[1], DX_PLAYTYPE_BACK, 1);
			}
			if (CheckSoundMem(soundHandle[1]) == 1)
			{
				StopSoundMem(soundHandle[0]);
			}
			character->collisionPoison(isGameOver, poison);
			item->select(cursorX, cursorY, WIN_WIDTH, WIN_HEIGHT);
			character->move(stage, map);
			character->changeStage(stage);
			stage->scroll();
			character->clear(isGameClear, stage, soundHandle[4], soundHandle[6]);
			poison->move(stage);
		}
		if (isGameClear == 1)
		{
			if (CheckSoundMem(soundHandle[7]) == 0)
			{
				PlaySoundMem(soundHandle[7], DX_PLAYTYPE_BACK, 1);
			}
			if (CheckSoundMem(soundHandle[7]) == 1)
			{
				StopSoundMem(soundHandle[1]);
			}
		}
		if (isGameOver == 1)
		{
			if (CheckSoundMem(soundHandle[8]) == 0)
			{
				PlaySoundMem(soundHandle[8], DX_PLAYTYPE_BACK, 1);
			}
			if (CheckSoundMem(soundHandle[8]) == 1)
			{
				StopSoundMem(soundHandle[1]);
			}
		}

		//�`�揈��
		if (isStart == 1)
		{
			DrawBox(0, 0, 1500, 844, GetColor(255, 255, 255), 1);
		}
		if (isOperation == 1)
		{
			DrawBox(0, 0, 1500, 844, GetColor(255, 255, 0), 1);
		}
		if (isGame == 1)
		{
			stage->draw(map, graphHandle[0], graphHandle[1], graphHandle[2], graphHandle[6], graphHandle[7], graphHandle[8]);
			character->draw(stage, graphHandle[3], graphHandle[4], soundHandle[4], soundHandle[6]);
			poison->draw(stage);
			item->draw(WIN_WIDTH, WIN_HEIGHT, cursorX, cursorY);
		}
		if (isGameClear == 1)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawBox(0, 0, 1500, 844, GetColor(255, 255, 255), 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
			DrawBox(0, 0, 1500, 844, GetColor(255, 255, 255), 1);
			alpha -= 15;
			if (alpha < 0)
			{
				alpha = 0;
			}
		}
		if (isGameOver == 1)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			DrawBox(0, 0, 1500, 844, GetColor(0, 0, 0), 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
			DrawBox(0, 0, 1500, 844, GetColor(255, 255, 0), 1);
			alpha -= 15;
			if (alpha < 0)
			{
				alpha = 0;
			}
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}