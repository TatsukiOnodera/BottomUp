#include "DxLib.h"
#include "Character.h"
#include "Item.h"
#include "Stage.h"
#include "Poison.h"

const char TITLE[] = "Bottom Up";

const int WIN_WIDTH = 1500; //ウィンドウ横幅
const int WIN_HEIGHT = 844; //ウィンドウ縦幅


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(0.8);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0, 0, 255);		// 画面の背景色を設定する
	//ChangeWindowMode(1);		//フルスクリーン
	SetMouseDispFlag(TRUE);				//マウス表示

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像などのリソースデータの変数宣言と読み込み
	int soundHandle[9];
	soundHandle[0] = LoadSoundMem("スタートBGM.mp3");
	soundHandle[1] = LoadSoundMem("ステージBGM.mp3");
	soundHandle[2] = LoadSoundMem("セレクトSE.mp3");
	soundHandle[3] = LoadSoundMem("金属.mp3");
	soundHandle[4] = LoadSoundMem("革靴で走る.mp3");
	soundHandle[5] = LoadSoundMem("警報が鳴る.mp3");
	soundHandle[6] = LoadSoundMem("「きゃああーー！」.mp3");
	soundHandle[7] = LoadSoundMem("ゲームクリアBGM.mp3");
	soundHandle[8] = LoadSoundMem("ゲームオーバーBGM.mp3");

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

	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報
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

	// ゲームループ
	while (1)
	{
		//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
		oldMouse = mouse;
		mouse = 0;
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
		{
			mouse = 1;
		}

		//最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//マウス座標
		GetMousePoint(&cursorX, &cursorY);

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		//入力処理
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

		//更新処理
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

		//描画処理
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

		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}