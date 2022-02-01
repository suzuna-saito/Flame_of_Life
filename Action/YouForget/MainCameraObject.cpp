/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
MainCameraObject::MainCameraObject()
	: GameObject(SceneBase::Scene::other, Tag::Camera, true)
	, mHasParentObject(false)
	, mOffsetPos(Vector3::Zero)
	, mLerpObject(Vector3::Zero)
{
	SetPosition(Vector3(-100.0f, 0.0f, 0.0f));
	mTag = Tag::Camera;
}

/*
@fn	�f�X�g���N�^
*/
MainCameraObject::~MainCameraObject()
{
}

/*
@fn		���̃N���X�̓|�[�Y���ɕʃN���X����X�V�֐����Ă΂�邱�Ƃ�����
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	Vector3 pos = mOffsetPos + mPosition;
	pos = mLerpObject + mOffsetPos;
	
	mPosition = pos;

	SetPosition(mPosition);
	Matrix4 view = Matrix4::CreateLookAt(mPosition, mLerpObject, Vector3::UnitZ);
	RENDERER->SetViewMatrix(view);
}

/*
@param _offset�@���������W�Ƃ̍�
@param _parentPos�@������W
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos)
{
	mHasParentObject = true;
	mOffsetPos = _offset;
	mLerpObject = _parentPos;
}

/*
@brief �Q�[�����̈ړ�����
@param	_deltaTime �O�̃t���[���ł�����������
*/
void MainCameraObject::InGameMovableProcess(float _deltaTime)
{
	//// �J�������a�̕␳�֐�
	//CorrectionRadius();

	//// �|�W�V�����v�Z�֐�
	//CalculationPosition(_deltaTime);

	//// �r���[�s��v�Z�֐�
	//CalculationViewMatrix();

	//// �v���C���[���ɓn���O���x�N�g���𐶐�
	//mForwardVec = lerpObjectPos - position;
	//// ���K��
	//mForwardVec.Normalize();
	//// Z�����Œ�
	//mForwardVec.z = 0.0f;

	//// �����蔻����s���I�u�W�F�N�g�Ɠ��������|�W�V������ۑ�
	//tmpHitFlag = hitFlag;

	//// �����蔻����s���ۂɗ��p����ϐ��̏�����
	//hitPosition = Vector3::Zero;
	//hitFlag = false;
}