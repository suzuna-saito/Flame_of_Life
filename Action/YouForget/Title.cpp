#include "pch.h"

Title::Title(const SceneType& _nowScene)
	:SceneBase(_nowScene)
{
	// mClearEndFlagをtrueにする
	ResultBase::mClearEndFlag = true;

	// タイトル画像の生成
	mFullPicture = new FullPicture("Assets/UI/Title/TitleB.png");
	
	// mGetNumberを空にする
	ItemBase::mGetNumber.clear();
}

Title::~Title()
{
	// 現在のシーンで生成したオブジェクトを全て削除
	GAME_OBJECT_MANAGER->RemoveGameObjects(SceneType::eTitle);
}

void Title::Input(const InputState& _state)
{
	// コントローラーのAボタン、または、スペースキーが押された瞬間
	if (_state.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) == 1 ||
		_state.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Released)
	{
		// シーン遷移フラグをtrueにする
		mGameSceneFlag = true;
	}
}

SceneBase* Title::update()
{
	// mGameSceneFlagがtrueだったら
	if (mGameSceneFlag)
	{
		// 次のシーンのポインタを返す
		return new FirstStage(SceneType::eFirst);
		//return new FirstResult(SceneType::eFirstResult);
		//return new Tutorial(Scene::tutorial);
		//return new SecondStage(Scene::second);
		//return new ThirdStage(Scene::third);
		//return new Result(Scene::result);
	}

	return this;
}