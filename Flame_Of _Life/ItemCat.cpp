#include "pch.h"

ItemCat::ItemCat(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, _objectTag)
	, mCollisionFlag(false)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//Component基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Environment/Item/Cat.gpmesh"));

	//アイテムの当たり判定
	mSelfBoxCollider = new BoxCollider(this, ColliderTag::itemTag, GetOnCollisionFunc());
	AABB box = { Vector3(13.0f,-20.0f,0.0f),Vector3(-13.0f,16.5f,9.0f) };
	mSelfBoxCollider->SetObjectBox(box);

	//回転処理                        ↓回転する値
	float radian = Math::ToRadians(180.0f);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

}


void ItemCat::UpdateGameObject(float _deltaTime)
{
	// フラグが上がっていたら
	if (mCollisionFlag && GetState() != Disabling)
	{
		// ステートをdisablにする
		SetState(State::Disabling);

		Rose::mItemCount--;
	}
}


void ItemCat::OnCollision(const GameObject& _hitObject)
{
	//ヒットしたオブジェクトのタグを取得
	mTag = _hitObject.GetTag();

	// プレイヤーとこのオブジェクトが当たったら
	if (mTag == item)
	{
		// 当たったのでフラグを上げる
		mCollisionFlag = true;

		// 描画をやめる
		mMeshComponent->SetVisible(false);
	}
}
