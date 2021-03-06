/*
@brief	プリプロセッサ
*/
#pragma once

class Stage01 : public SceneBase
{
public:

	/*
	@fn		コンストラクタ
	@param	_nowScene 現在のシーン
	*/
	Stage01(const Scene& _nowScene);

	/*
	@fn	デストラクタ
	*/
	~Stage01();

	void Input(const InputState& state)override;

	/*
	@fn	現在のシーン時に毎フレーム更新処理をする
	*/
	SceneBase* update() override;

private:

};

