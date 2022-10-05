/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
Result::Result(const SceneType& _nowScene)
	:ResultBase(_nowScene)
{
	if (mTrueEndFlag)
	{
		mFullPicture = new FullPicture("Assets/UI/EndResult/Clear_1.png");
	}
	else
	{
		mFullPicture = new FullPicture("Assets/UI/EndResult/Clear_4.png");
	}

	mSearch();
}

/*
@fn	デストラクタ
*/
Result::~Result()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eGameClear);
}

void Result::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mDrawUpdate();
	}
}


/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* Result::update()
{
	if (mGameSceneFlag)
	{
		return new Title(SceneType::eTitle);
	}

	mResultUpdate();

	return this;
}