/*
@file Renderer.h
@brief 描画の進行を行うクラス
*/

/*
@brief	プリプロセッサ
*/
#pragma once


#define RENDERER Renderer::GetInstance()

//平行光源用の構造体
struct DirectionalLight
{
	// 光の方向
	Vector3 m_direction;
	// 拡散反射色
	Vector3 m_diffuseColor;
	// 鏡面反射色
	Vector3 m_specColor;
};

/*
@enum テクスチャステージ
*/
enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

class SpriteComponent;
class Texture;
class Shader;
class VertexArray;

class Renderer
{
public:

	/*
	@fn	インスタンスを作成する
	*/
	static void CreateInstance();

	/*
	@fn	インスタンスを削除する
	*/
	static void DeleteInstance();

	/*
	@fn		初期化処理
	@return true : 成功 , false : 失敗(bool型)
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);

	/*
	@fn	終了処理
	*/
	void Shutdown();

	/*
	@fn	ロードしたデータの解放
	*/
	void UnloadData();

	/*
	@fn	描画処理
	*/
	void Draw();

	/*
	@fn		スプライトの追加
	@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@fn		スプライトの削除
	@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@fn		パーティクルの追加
	@param	_particleComponent　追加するParticleObjectクラスのポインタ
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@fn		パーティクルの削除
	@param	_particleComponent 削除するParticleObjectクラスのポインタ
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);

	/*
	@fn		メッシュコンポーネントの追加
	@param	_meshComponent　追加するMeshComponentクラスのポインタ
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);

	/*
	@fn		メッシュコンポーネントの削除
	@param	_meshComponent　削除するMeshComponentクラスのポインタ
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

private:

	//コンストラクタ、デストラクタの隠蔽
	Renderer();
	~Renderer();

	// スケルトンデータ
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// アニメーションデータ
	std::unordered_map<std::string, class Animation*> mAnims;
	// スケルトンメッシュの描画に使われる
	std::vector<class SkeletalMeshComponent*>       mSkeletalMeshes;

	//自分のインスタンス
	static Renderer* mRenderer;
	//レンダラーの状態を含む構造体
	SDL_Renderer* mSdlRenderer;

	/*
	@fn		光源情報をシェーダーの変数にセットする
	@param  _shader セットするShaderクラスのポインタ
	@param	_view ビュー行列
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& _view);


	/*
	@fn		シェーダーの読み込み
	@return true : 成功 , false : 失敗(bool型)
	*/
	bool LoadShaders();

	/*
	@fn	Sprite用の頂点バッファとインデックスバッファの作成
	*/
	void CreateSpriteVerts();

	/*
	@fn	Particle用の頂点バッファとインデックスバッファの作成
	*/
	void CreateParticleVerts();

	/*
	@fn	Particleの描画
	*/
	void DrawParticle();

	/*
	@fn	Particleの描画
	@param	_framebuffer フレームバッファ
	@param	_view ビュー行列
	@param	_proj 射影行列
	@param	_viewPortScale 表示領域スケール
	@param	_lit 光源情報をシェーダーの変数にセットするかのフラグ
	*/
	void Draw3DScene(unsigned int _framebuffer, const Matrix4& _view, const Matrix4& _proj,
		float _viewPortScale = 1.0f, bool _lit = true);

	/*
	@fn		光源情報をシェーダーの変数にセットする
	@param  _blendType パーティクルに対するブレンドの種類
	*/
	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM _blendType);

	/*
	@fn		テクスチャの変更
	@param	_changeTextureID 変更するテクスチャのid
	*/
	void ChangeTexture(int _changeTextureID);

	/*
	@fn	ワールド空間のカメラ座標を計算
	*/
	Vector3 CalcCameraPos();

	//ファイル名でメッシュを取得するための連想配列
	std::unordered_map<std::string, Mesh*> mMeshes;
	//メッシュコンポーネントのポインタの可変長コンテナ
	std::vector<MeshComponent*> mMeshComponents;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> mSprites;
	//パーティクルのポインタ
	std::vector<ParticleComponent*> mParticles;
	//ファイル名でテクスチャを取得するための連想配列
	std::unordered_map<std::string, Texture*> mTextures;

	//クラスのポインタ
	//スプライト
	Shader* mSpriteShader;

	//スプライト用頂点
	VertexArray* mSpriteVerts;

	//メッシュ
	Shader* mMeshShader;

	//スキンメッシュ
	class Shader* mSkinnedShader;
	Shader* mBasicShader;
	//パーティクル
	Shader* mParticleShader;
	//パーティクル用頂点
	VertexArray* mParticleVertex;

	//ビュー行列
	Matrix4 mView;
	//射影行列
	Matrix4 mProjection;
	//スクリーンの横幅
	float mScreenWidth;
	//スクリーンの縦幅
	float mScreenHeight;
	//環境光
	Vector3 mAmbientLight;
	//平行光源
	DirectionalLight mDirLight;
	//ウィンドウ
	SDL_Window* mWindow;

	//コンテキスト
	SDL_GLContext mContext;

	// UIの初期座標に加算される座標
	Vector2 mAddPosition;

	//未設定テクスチャの場合に割り当てられる黒色テクスチャ
	unsigned int mUndefineTexID;

public://ゲッターセッター

	/*
	@fn		インスタンスを取得する
	@return Rendererクラスのインスタンス(class Renderer)
	*/
	static Renderer* GetInstance() { return mRenderer; }

	/*
	@param	_fileName　取得したいテクスチャのファイル名
	@return Textureクラスのポインタ(class Texture)
	*/
	Texture* GetTexture(const std::string& _fileName);

	/*
	@param _fileName モデルへのアドレス
	@return スケルトンモデルの取得(class Skeleton)
	*/
	const class Skeleton* GetSkeleton(const char* _fileName);

	/*
	@param _fileName アニメーションへのアドレス
	@return スケルトンアニメーションの取得(class Animation)
	*/
	const class Animation* GetAnimation(const char* _fileName);                     // スケルタルアニメーションの取得

	/*
	@param	_fileName 取得したいメッシュのファイル名
	@return Meshクラスのポインタ(class Mesh)
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@return	平行光源の構造体(struct DirectionalLight）
	*/
	DirectionalLight& GetDirectionalLight() { return mDirLight; }


	/*
	@return	ビュー行列(class Matrix4)
	*/
	Matrix4 GetViewMatrix() const { return mView; };

	/*
	@return	射影行列(class Matrix4)
	*/
	Matrix4 GetProjectionMatrix() { return mProjection; }

	/*
	@return	射影行列(class Matrix4)
	*/
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	/*
	@return	未設定テクスチャの場合に割り当てられる黒色テクスチャ(unsigned int型)
	*/
	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	/*
	@param	_view ビュー行列
	*/
	void SetViewMatrix(const Matrix4& _view) { mView = _view; }

	/*
	@param	_ambient（環境光を表す）
	*/
	void SetAmbientLight(const Vector3& _ambient) { mAmbientLight = _ambient; }

	/*
	@fn	パーティクル用頂点を設定
	*/
	void SetParticleVertex();

};