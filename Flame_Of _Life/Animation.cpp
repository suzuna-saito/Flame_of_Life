/*
@file	Animation.h
@brief	Skeletonを用いたアニメーションのデータクラス
*/

/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn アニメーション読み込み
@param アニメーションへのパス
*/
bool Animation::Load(const std::string& _fileName)
{
	// filenameからテキストファイルとして読み込み、rapidJSONに解析させる
	std::ifstream file(_fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Animation %s", _fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	// JSONオブジェクトか？
	if (!doc.IsObject())
	{
		SDL_Log("Animation %s is not valid json", _fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata　メタデータのチェック。バージョンは１か？
	if (ver != 1)
	{
		SDL_Log("Animation %s unknown format", _fileName.c_str());
		return false;
	}

	// "sequece"情報読み込めるか？
	const rapidjson::Value& sequence = doc["sequence"];
	if (!sequence.IsObject())
	{
		SDL_Log("Animation %s doesn't have a sequence.", _fileName.c_str());
		return false;
	}

	// "frames" "length" "bonecount"はあるか？
	const rapidjson::Value& frames = sequence["frames"];
	const rapidjson::Value& length = sequence["length"];
	const rapidjson::Value& bonecount = sequence["bonecount"];

	if (!frames.IsUint() || !length.IsDouble() || !bonecount.IsUint())
	{
		SDL_Log("Sequence %s has invalid frames, length, or bone count.", _fileName.c_str());
		return false;
	}

	// フレーム数、アニメーション時間、ボーン数、フレームあたりの時間を取得
	mNumFrames = frames.GetUint();
	mDuration = static_cast<float>(length.GetDouble());
	mNumBones = bonecount.GetUint();
	mFrameDuration = mDuration / (mNumFrames - 1);

	// トラック配列を確保
	mTracks.resize(mNumBones);

	// トラック配列が取得できるか？
	const rapidjson::Value& tracks = sequence["tracks"];

	if (!tracks.IsArray())
	{
		SDL_Log("Sequence %s missing a tracks array.", _fileName.c_str());
		return false;
	}

	// トラック数分ループ
	for (rapidjson::SizeType i = 0; i < tracks.Size(); i++)
	{
		// tracs[i]はオブジェクトか？
		if (!tracks[i].IsObject())
		{
			SDL_Log("Animation %s: Track element %d is invalid.", _fileName.c_str(), i);
			return false;
		}

		// tracks[i]の中の "bone"をuintで読み込み。ボーン番号を取得
		size_t boneIndex = tracks[i]["bone"].GetUint();

		// tracks[i]の中の "transforms"が取得できるか？
		const rapidjson::Value& transforms = tracks[i]["transforms"];
		if (!transforms.IsArray())
		{
			SDL_Log("Animation %s: Track element %d is missing transforms.", _fileName.c_str(), i);
			return false;
		}

		BoneTransform temp;
		// transformのサイズとアニメーションフレーム数が不具合ないか？
		if (transforms.Size() < mNumFrames)
		{
			SDL_Log("Animation %s: Track element %d has fewer frames than expected.", _fileName.c_str(), i);
			return false;
		}

		// transformsのサイズ分ループ。ボーン番号boneIndexの変換情報として取り込む
		for (rapidjson::SizeType j = 0; j < transforms.Size(); j++)
		{
			// ローテーション(quaternion)とtrans(平行移動成分)を読み込む
			const rapidjson::Value& rot = transforms[j]["rot"];
			const rapidjson::Value& trans = transforms[j]["trans"];

			if (!rot.IsArray() || !trans.IsArray())
			{
				SDL_Log("Skeleton %s: Bone %d is invalid.", _fileName.c_str(), i);
				return false;
			}

			// temp.mRotationに　quaternionとしてコピー、
			temp.mRotation.x = static_cast<float>(rot[0].GetDouble());
			temp.mRotation.y = static_cast<float>(rot[1].GetDouble());
			temp.mRotation.z = static_cast<float>(rot[2].GetDouble());
			temp.mRotation.w = static_cast<float>(rot[3].GetDouble());

			// temp.mTranslationに平行移動成分としてコピー
			temp.mTranslation.x = static_cast<float>(trans[0].GetDouble());
			temp.mTranslation.y = static_cast<float>(trans[1].GetDouble());
			temp.mTranslation.z = static_cast<float>(trans[2].GetDouble());

			// ボーン番号boneIndexの姿勢データとして、mTracks配列に入れる。
			mTracks[boneIndex].emplace_back(temp);
		}
	}

	return true;
}

// inTime時刻時点のグローバルポーズ配列の取得
void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& _outPoses, const Skeleton* _inSkeleton, float _inTime) const
{
	if (_outPoses.size() != mNumBones)
	{
		_outPoses.resize(mNumBones);
	}

	// Figure out the current frame index and next frame
	// (This assumes inTime is bounded by [0, AnimDuration]
	// 現在のフレームと次のフレームを見つけ出す。
	// これはinTimeが [0〜AnimDuration] の間にいることを前提としています。
	size_t frame = static_cast<size_t>(_inTime / mFrameDuration);
	size_t nextFrame = frame + 1;
	// Calculate fractional value between frame and next frame
	// フレームと次のフレームの間の小数値を計算します。
	float pct = _inTime / mFrameDuration - frame;

	if (mNumFrames <= nextFrame)
	{
		--nextFrame;
	}
	// Setup the pose for the root
	// ルートのポーズをセットアップ
	if (mTracks[0].size() > 0)
	{
		// Interpolate between the current frame's pose and the next frame
		// 現在のフレームのポーズと次のフレームの間を補間する
		BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame],
			mTracks[0][nextFrame], pct);
		_outPoses[0] = interp.ToMatrix();
	}
	else
	{
		_outPoses[0] = Matrix4::Identity;
	}

	const std::vector<Skeleton::Bone>& bones = _inSkeleton->GetBones();
	// Now setup the poses for the rest
	// 残りのポーズを設定します
	for (size_t bone = 1; bone < mNumBones; bone++)
	{
		Matrix4 localMat; // (Defaults to identity)　（デフォルトは単位行列）
		if (mTracks[bone].size() > 0)
		{
			// [bone][frame]のボーン姿勢と[bone][nextframe]を 小数点以下の pctで補間した姿勢を interpに算出
			BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
				mTracks[bone][nextFrame], pct);
			// interp を行列に変換して、localMatに変換する
			localMat = interp.ToMatrix();
		}

		// 出力ポーズ行列[bone] = ローカルポーズ行列 * 出力ポーズ行列[親bone]
		_outPoses[bone] = localMat * _outPoses[bones[bone].mParent];
	}
}
