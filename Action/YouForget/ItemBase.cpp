#include "pch.h"

// �ÓI�ϐ��̏�����
int ItemBase::mItemCount = 0;
vector<itemNames> ItemBase::mGetNames;

ItemBase::ItemBase(const SceneBase::Scene _sceneTag, const Tag& _objectTag)
	: GameObject(_sceneTag, _objectTag)
	, mMeshComponent(0)
	, mSelfBoxCollider(0)
	, mMove(60.0f)
	, mMaxMove(50.0f)
	, mMinMove(0.0f)
	, mUpFlag(true)
	, mCollisionFlag(false)
	, mItemName(itemNames::first)
{
	// �A�C�e������������邽�тɃJ�E���g�����B
	mItemCount++;
}

// �O�u�C���N�������g
//itemNames& operator++(itemNames& rhs)
//{
//	if (rhs == itemNames::end)
//	{
//		throw std::out_of_range("for outof range Tag& operator ++ (Tag&)");
//	}
//	rhs = itemNames(static_cast<std::underlying_type<itemNames>::type>(rhs) + 1);
//
//	return rhs;
//}