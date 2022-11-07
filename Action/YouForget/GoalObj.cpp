#include "pch.h"

// 静的メンバ変数の初期化
bool GoalObj::mGoalFlag = false; // ゴールしたかどうか

GoalObj::GoalObj(const Vector3 _pos)
	: GameObject(ObjTag::eGoal)
{
	// 生成した時にゴールしたかどうかフラグをfalseにする
	mGoalFlag = false;

	// ゴールの当たり判定を設定
	mSelfBoxCollider = new BoxCollider(this, mTag, GetOnCollisionFunc());
	AABB box = { Vector3(-300.0f,-10.0f,-300.0f),Vector3(300.0f,10.0f,300.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	// GameObjectメンバ変数の初期化
	SetPosition(_pos);					// オブジェクトのポジション

	// ゴールエフェクトの生成
	new GoalEffect(this);
}

void GoalObj::OnCollision(const GameObject& _hitObject)
{
	// プレイヤーが行動可能な時プレイヤーがゴールに当たったら
	if (Player::mOperable)
	{
		// ゴールしたかどうかフラグをtrueにする
		mGoalFlag = true;
	}
}