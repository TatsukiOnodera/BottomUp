#include "DxLib.h"
#include "Character.h"
#include "Item.h"
#include "Stage.h"
#include "Poison.h"

const char TITLE[] = "Bottom Up (��)";

const int WIN_WIDTH = 1500; //�E�B���h�E����
const int WIN_HEIGHT = 844;//�E�B���h�E�c��


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(0.8);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(150, 150, 150);		// ��ʂ̔w�i�F��ݒ肷��
	//ChangeWindowMode(1);		//�t���X�N���[��
	SetMouseDispFlag(TRUE);				//�}�E�X�\��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int graphHandle[3] = { 0 };

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

	int map[24][20] = { {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
										,{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

	Character* character = new Character;
	Item* item = new Item;
	Stage* stage = new Stage;
	Poison* poison = new Poison;

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
				}
				count = 0;
			}
			count++;
		}
		if (isGame == 1)
		{
			item->carry(mouse, oldMouse);
			item->put(cursorX, cursorY, mouse, oldMouse, map, stage);
		}
		if (isGameClear == 1)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isGameClear = 0;
				isStart = 1;
			}
		}
		if (isGameOver == 1)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isGameOver = 0;
				isStart = 1;
			}
		}

		//�X�V����
		if (isGame == 1)
		{
			item->select(cursorX, cursorY, WIN_WIDTH, WIN_HEIGHT);
			character->move(stage, map);
			character->changeStage(stage);
			stage->scroll();

			if (character->getNext() == 1)
			{
				isGameClear = 1;
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
			stage->draw(map);
			item->draw(WIN_WIDTH, WIN_HEIGHT, cursorX, cursorY);
			character->draw(stage);
		}
		if (isGameClear == 1)
		{
			DrawBox(0, 0, 1500, 844, GetColor(255, 255, 255), 1);
		}
		if (isGameOver == 1)
		{
			DrawBox(0, 0, 1500, 844, GetColor(255, 255, 0), 1);
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