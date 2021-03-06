/*
プリプロセッサ
*/
#pragma once

class MeshComponent;
class SamplePlayer;

class FireObject :public GameObject
{
public:

	// コンストラクタ
	FireObject(Candle* _owner, const Vector3& _size, const Tag& _objectTag);

	/*
	@fn	デストラクタ
	*/
	~FireObject() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

private:

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	Candle* mOwner;
public://ゲッターセッター

};

