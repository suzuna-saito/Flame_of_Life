/*
@brief	プリプロセッサ
*/
#pragma once

class BackGround :public GameObject
{
public:
	/*
	@fn		コンストラクタ
	@param	_pos ポジション
	@param	_size サイズ
	@param	_objectTag オブジェクトのタグ
	@param	_sceneTag シーンタグ
	*/
	BackGround(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const int _type);

	// デストラクタ
	~BackGround() {};

	/*
	@fn		床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	//void UpdateGameObject(float _deltaTime)override;

private:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	const int mType;

};

