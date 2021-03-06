/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Title::Title(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	// タイトル画像
	mSprite = new Sprite("Assets/UI/Title.png");

}

/*
@fn	デストラクタ
*/
Title::~Title()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(title);
	delete mSprite;
}

void Title::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
	{
		mGameSceneFlag = true;
	}
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Title::update()
{

	if (mGameSceneFlag)
	{
		return new Tutorial(tutorial);
	}

	return this;
}