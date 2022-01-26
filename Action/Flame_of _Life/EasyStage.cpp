/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_nowScene 現在のシーン
*/
EasyStage::EasyStage(const Scene& _nowScene)
	:SceneBase()
{
	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// 床の生成
		mMapCreate->CreateGround();
		// スイッチの生成
		mMapCreate->CreateSwitch();
		// ろうそくの生成
		mMapCreate->CreateCandle();
		// プレイヤーの生成
		mMapCreate->CreatePlayer();
		// アイテムの生成
		mMapCreate->CreateItem();
	}

	// カウントアップ
	new CountUp(_nowScene);
}

/*
@fn	デストラクタ
*/
EasyStage::~EasyStage()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(Scene::easy);

	delete mMapCreate;
}


void EasyStage::Input(const InputState& _state)
{
	// 当たり判定表示モードの切り替え
	if (_state.m_keyboard.GetKeyState(SDL_SCANCODE_0) == ButtonState::Pressed)
	{
		PHYSICS->ToggleDebugMode();
	}
}

/*
@fn	現在のシーン時に毎フレーム更新処理をする
*/
SceneBase* EasyStage::update()
{
	if (Candle::mCandleCount == 2)
	{
		return new NormalStage(Scene::normal);
		//return new Result(Scene::result);
	}

	CountUp::SetCountStartFlag(true);

	return this;
}
