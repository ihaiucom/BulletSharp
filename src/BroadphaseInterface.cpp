#include "StdAfx.h"

#include "BroadphaseInterface.h"

BroadphaseInterface::BroadphaseInterface(btBroadphaseInterface* broadphase)
{
	_broadphase = broadphase;
}

BroadphaseInterface::~BroadphaseInterface()
{
	this->!BroadphaseInterface();
}

BroadphaseInterface::!BroadphaseInterface()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_broadphase = NULL;
	
	OnDisposed( this, nullptr );
}

bool BroadphaseInterface::IsDisposed::get()
{
	return (_broadphase == NULL);
}

void BroadphaseInterface::CalculateOverlappingPairs(IDispatcher^ dispatcher)
{
	_broadphase->calculateOverlappingPairs(dispatcher->UnmanagedPointer);
}

BroadphaseProxy^ BroadphaseInterface::CreateProxy(Vector3 aabbMin, Vector3 aabbMax,
	int shapeType, IntPtr userPtr, short int collisionFilterGroup,
	short int collisionFilterMask, IDispatcher^ dispatcher, IntPtr multiSapProxy)
{
	btBroadphaseProxy* proxy = new btBroadphaseProxy;
	proxy = _broadphase->createProxy(*Math::Vector3ToBtVec3(aabbMin), *Math::Vector3ToBtVec3(aabbMax),
		shapeType, userPtr.ToPointer(), collisionFilterGroup, collisionFilterMask,
		dispatcher->UnmanagedPointer, multiSapProxy.ToPointer());
	return gcnew BroadphaseProxy(proxy);
}

void BroadphaseInterface::DestroyProxy(BroadphaseProxy^ proxy, IDispatcher^ dispatcher)
{
	_broadphase->destroyProxy(proxy->UnmanagedPointer, dispatcher->UnmanagedPointer);
}

void BroadphaseInterface::GetAabb(BroadphaseProxy^ proxy, Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	_broadphase->getAabb(proxy->UnmanagedPointer, *tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVec3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVec3ToVector3(tmpAabbMax);
}

void BroadphaseInterface::GetBroadphaseAabb(Vector3% aabbMin, Vector3% aabbMax)
{
	btVector3* tmpAabbMin = new btVector3;
	btVector3* tmpAabbMax = new btVector3;
	
	_broadphase->getBroadphaseAabb(*tmpAabbMin, *tmpAabbMax);

	aabbMin = Math::BtVec3ToVector3(tmpAabbMin);
	aabbMax = Math::BtVec3ToVector3(tmpAabbMax);
}

void BroadphaseInterface::PrintStats()
{
	_broadphase->printStats();
}

#pragma managed(push, off)
void BroadphaseInterface_RayTest(btBroadphaseInterface* broadphase, btVector3* rayFrom, btVector3* rayTo, btBroadphaseRayCallback* rayCallback)
{
	broadphase->rayTest(*rayFrom, *rayTo, *rayCallback);
}
#pragma managed(pop)

void BroadphaseInterface::RayTest(Vector3 rayFrom, Vector3 rayTo, BroadphaseRayCallback^ rayCallback)
{
	BroadphaseInterface_RayTest(_broadphase, Math::Vector3ToBtVec3(rayFrom), Math::Vector3ToBtVec3(rayTo),
		rayCallback->UnmanagedPointer);
}

void BroadphaseInterface::ResetPool(IDispatcher^ dispatcher)
{
	_broadphase->resetPool(dispatcher->UnmanagedPointer);
}

void BroadphaseInterface::SetAabb(BroadphaseProxy^ proxy, Vector3 aabbMin, Vector3 aabbMax, IDispatcher^ dispatcher)
{
	_broadphase->setAabb(proxy->UnmanagedPointer, *Math::Vector3ToBtVec3(aabbMin), *Math::Vector3ToBtVec3(aabbMax), dispatcher->UnmanagedPointer);
}

OverlappingPairCache^ BroadphaseInterface::OverlappingPairCache::get()
{
	return _pairCache;
}

btBroadphaseRayCallback* BroadphaseRayCallback::UnmanagedPointer::get()
{
	return _rayCallback;
}
void BroadphaseRayCallback::UnmanagedPointer::set(btBroadphaseRayCallback* value)
{
	_rayCallback = value;
}

btBroadphaseInterface* BroadphaseInterface::UnmanagedPointer::get()
{
	return _broadphase;
}
void BroadphaseInterface::UnmanagedPointer::set(btBroadphaseInterface* value)
{
	_broadphase = value;
}