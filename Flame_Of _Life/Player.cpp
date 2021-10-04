/*
@brief	インクルード
*/
#include "pch.h"


// 定数と静的メンバーの初期化
const float Player::Gravity = 5.0f;

/*
@fn		コンストラクタ
@param	_pos プレイヤーの座標
@param	_size プレイヤーのサイズ
@param	_objectTag プレイヤーのタグ
@param	_sceneTag シーンのタグ
*/
Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mIsGroundFlag(false)
	, mNowJump(false)
	, mMoveSpeed(7.0f)
	, mAccelerator(8.0f)
	, mJump(7.0f)
	, mMaxJump(150.0f)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//生成したPlayerの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Player/Candle/Candle_1.gpmesh"));


	////プレイヤー自身の当たり判定(スフィア)
	//mSelfSphereCollider = new SphereCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	//Sphere sphere = { Vector3::Zero,30.0f };
	//mSelfSphereCollider->SetObjectSphere(sphere);
	
	//プレイヤー自身の当たり判定(ボックス)
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::playerTag, GetOnCollisionFunc());
	AABB box = { Vector3(0.0f,0.0f,0.0f),Vector3(0.5f,0.5f,0.5f) };
	mSelfBoxCollider->SetObjectBox(box);

	//new SampleFireObject(this, Vector3(1.0f, 1.0f, 1.0f), _objectTag);
}

/*
@fn		プレイヤーのアップデート
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void Player::UpdateGameObject(float _deltaTime)
{

	//プレイヤーを見下ろす位置にカメラをセット
	mMainCamera->SetViewMatrixLerpObject(Vector3(0, -500, 200), mPosition);

	// 座標をセット
	mPosition += mVelocity;

	// コード汚すぎ　書き直せ------------

	//if (mNowJump)
	//{
 //		mVelocity.z = mJump;
	//}
	//if(mPosition.z >= mMaxJump)
	//{
	//	mNowJump = false;
	//	mVelocity.z = 3.0f;
	//}

	/*if (!mIsGroundFlag)
	{
		mPosition.z -= Gravity;
	}*/

	SetPosition(mPosition);

	////回転処理(回転用サンプルコード)
	//float radian = Math::ToRadians(mAngle);
	//Quaternion rot = this->GetRotation();
	//Quaternion inc(Vector3::UnitX, radian);
	//Quaternion target = Quaternion::Concatenate(rot, inc);
	//SetRotation(target);
}

/*
@fn		入力を引数で受け取る更新関数
@brief	基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 各入力機器の入力状態
@brief	キーボード、マウス、コントローラー
*/
void Player::GameObjectInput(const InputState& _keyState)
{
	// Wで奥に移動
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		mVelocity.y = mMoveSpeed;
	}
	// Sで手前に移動
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		mVelocity.y = -mMoveSpeed;
	}
	// どちらも押されていなければｙ軸の移動を止める
	else
	{
		mVelocity.y = 0.0f;
	}

	// Aで左に移動
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		mVelocity.x = mMoveSpeed;
	}
	// Dで右に移動
	else if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		mVelocity.x = -mMoveSpeed;
	}
	// どちらも押されていなければｘ軸の移動を止める
	else
	{
		mVelocity.x = 0.0f;
	}


	// スペースでジャンプ
	if (mIsGroundFlag && _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE))
	{
		mVelocity.z = mAccelerator;
		mIsGroundFlag = false;
		mNowJump = true;
	}
	else
	{
		mVelocity.z = 0.0f;
	}
}

/*
@fn		プレイヤーがヒットした時の処理
@param	_hitObject ヒットした対象のゲームオブジェクトのアドレス
*/
void Player::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	mTag = _hitObject.GetTag();

	if (mTag == ground)
	{
		//CalcCollisionFixVec();
		mIsGroundFlag = true;

		mVelocity.z = 0.0f;
	}
}