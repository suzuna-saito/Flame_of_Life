/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
FirstResult::FirstResult(const Scene& _nowScene)
	:ResultBase(_nowScene)
{
	mSprite = new Sprite("Assets/UI/FirstResult/FirstResultBase.png");

	// マップをつかってアイテムと説明画像を関連付け	
	mItemDescription[ItemNum::one] = "Assets/UI/FirstResult/Puzzles_1.png";
	mItemDescription[ItemNum::two] = "Assets/UI/FirstResult/Puzzles_2.png";
	mItemDescription[ItemNum::three] = "Assets/UI/FirstResult/Puzzles_3.png";

	// どのアイテムを取っているか検索
	mSearch();
}

/*
@fn	デストラクタ
*/
FirstResult::~FirstResult()
{
	delete mSprite;

	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::firstResult);
}

void FirstResult::Input(const InputState& _state)
{
	if (_state.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == ButtonState::Released ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		mDrawUpdate();
	}

	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_START) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_B) == ButtonState::Released)
	{
		mReturnTitleFlag = true;
	}
}


/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* FirstResult::update()
{
	if (mGameSceneFlag)
	{
		return new SecondStage(Scene::second);

		//return new Result(Scene::gameClear);
	}

	if (mReturnTitleFlag)
	{
		return new Title(Scene::title);
	}

	mResultUpdate();

	return this;
}