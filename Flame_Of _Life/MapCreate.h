/*
@brief	プリプロセッサ
*/
#pragma once


class MapCreate : public GameObject
{
public:

	/*
	@fn	コンストラクタ
	*/
	MapCreate();

	/*
	@fn	デストラクタ
	*/
	~MapCreate();

	/*
	@fn		jsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
	@return	ファイルを開けたか(bool型)
	*/
	bool OpenFile();

	/*
	@fn	床を生成する
	*/
	void CreateGround();

	/*
	@fn	プレイヤーを生成する
	*/
	void CreatePlayer();

	/*
	@fn	ろうそくを生成する
	*/
	void CreateCandle();

	/*
	@fn	花を生成する
	@param	_objectPos 生成するポジション
	*/
	void CreateRose(Vector3 _objectPos);
private:

	bool readTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName);

	//床マップデータ
	vector<vector<int>> mGroundMapData;

	//プレイヤーマップデータ
	vector<vector<int>> mPlayerMapData;
	//ろうそくマップデータ
	vector<vector<int>> mCandleMapData;

	// 前のデータ
	int mTmpName;
	// 今のデータ
	int mNowName;

	//現在のシーン
	int mScene;
	//幅のマップデータ
	int	mSizeX;
	//高さのマップデータ
	int	mSizeY;
	//奥行のマップデータ
	int	mSizeZ;

	// 床の高さをずらす
	float mChagePosY;
	float mHardChagePosY;

	//オブジェクトごとの距離
	float mOffsetX;
	float mOffsetY;
	float mOffsetZ;

	// 床のスケール
	const float MGroundScale;
	// ろうそくのスケール
	const float MCandleScale;
	// プレイヤーのスケール
	const float MPlayerScale;
	// 花のスケール
	const float MRoseScale;

	const float MPlayerZPos;
	// 地面に埋まらないためにろうそくに足してあげるポジションｚ軸
	const float MCandleZPos;
	// 地面に埋まらないためにアイテムに足してあげるポジションｚ軸
	const float MItemZPos;
};

