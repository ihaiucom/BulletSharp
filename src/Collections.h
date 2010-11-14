#pragma once

using namespace System::Collections;

namespace BulletSharp
{
	ref class CompoundShapeChild;
	ref class Dbvt;
	ref class DbvtNode;
	ref class DbvtProxy;

	ref class ListDebugView
	{
	private:
		IEnumerable^ _list;

	public:
		ListDebugView(IEnumerable^ list);

		[DebuggerBrowsable(DebuggerBrowsableState::RootHidden)]
		property ArrayList^ Items
		{
			ArrayList^ get();
		}
	};

	ref class Vector3ListDebugView
	{
	private:
		Generic::IList<Vector3>^ _list;

	public:
		Vector3ListDebugView(Generic::IList<Vector3>^ list);

		[DebuggerBrowsable(DebuggerBrowsableState::RootHidden)]
		property array<Vector3>^ Items
		{
			array<Vector3>^ get();
		}
	};

	generic<class T>
	public ref class ListEnumerator : IEnumerator, Generic::IEnumerator<T>
	{
	private:
		Generic::IList<T>^ _list;
		int i;

	public:
		ListEnumerator(Generic::IList<T>^ list);
		~ListEnumerator(){}

		property T GenericCurrent
		{
			virtual T get() = Generic::IEnumerator<T>::Current::get;
		}

		property Object^ Current
		{
			virtual Object^ get() = IEnumerator::Current::get;
		}

		virtual bool MoveNext();
		virtual void Reset();
	};

	generic<class T>
	public ref class GenericList abstract : Generic::IList<T>
	{
	private:
		void* _array;
		int _length;
		bool isReadOnly;

	internal:
		GenericList(void* array, int length);
		GenericList(const void* array, int length);

	public:
		virtual void Add(T item);
		virtual void Clear();
		virtual bool Contains(T item);
		virtual void CopyTo(array<T>^ array, int arrayIndex) = 0;
		virtual IEnumerator^ GetEnumerator() = IEnumerable::GetEnumerator;
		virtual Generic::IEnumerator<T>^ GetSpecializedEnumerator() = Generic::IEnumerable<T>::GetEnumerator;
		virtual int IndexOf(T item);
		virtual void Insert(int index, T item);
		virtual bool Remove(T item);
		virtual void RemoveAt(int index);

		property int Count
		{
			virtual int get();
		}

		property T default [int]
		{
			virtual T get (int index) = 0;
			virtual void set(int index, T value) = 0;
		}

		property bool IsReadOnly
		{
			virtual bool get();
		}

	internal:
		property void* UnmanagedPointer
		{
			virtual void* get();
			void set(void* value);
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class BoolArray : GenericList<bool>
	{
	internal:
		BoolArray(bool* boolArray, int length);
		BoolArray(const bool* boolArray, int length);

	public:
		virtual bool Contains(bool item) override;
		virtual void CopyTo(array<bool>^ array, int arrayIndex) override;
		virtual int IndexOf(bool item) override;

		property bool default[int]
		{
			virtual bool get(int index) override;
			virtual void set(int index, bool value) override;
		}

	internal:
		property bool* UnmanagedPointer
		{
			bool* get() new;
		}
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		ref class Body;

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class BodyArray : GenericList<Body^>
		{
		internal:
			BodyArray(btSoftBody::Body* bodyArray, int length);
			BodyArray(const btSoftBody::Body* bodyArray, int length);

		public:
			virtual void CopyTo(array<Body^>^ array, int arrayIndex) override;

			property Body^ default[int]
			{
				virtual Body^ get(int index) override;
				virtual void set(int index, Body^ value) override;
			}

		internal:
			property btSoftBody::Body* UnmanagedPointer
			{
				btSoftBody::Body* get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class CompoundShapeChildArray : GenericList<CompoundShapeChild^>
	{
	internal:
		CompoundShapeChildArray(btCompoundShapeChild* shapeArray, int length);
		CompoundShapeChildArray(const btCompoundShapeChild* shapeArray, int length);

	public:
		virtual void CopyTo(array<CompoundShapeChild^>^ array, int arrayIndex) override;

		property CompoundShapeChild^ default[int]
		{
			virtual CompoundShapeChild^ get(int index) override;
			virtual void set(int index, CompoundShapeChild^ value) override;
		}

	internal:
		property btCompoundShapeChild* UnmanagedPointer
		{
			btCompoundShapeChild* get() new;
		}
	};

#ifndef DISABLE_DBVT
	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class DbvtArray : GenericList<Dbvt^>
	{
	internal:
		DbvtArray(btDbvt* dbvtArray, int length);
		DbvtArray(const btDbvt* dbvtArray, int length);

	public:
		virtual void CopyTo(array<Dbvt^>^ array, int arrayIndex) override;

		property Dbvt^ default[int]
		{
			virtual Dbvt^ get(int index) override;
			virtual void set(int index, Dbvt^ value) override;
		}

	internal:
		property btDbvt* UnmanagedPointer
		{
			btDbvt* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class DbvtNodePtrArray : GenericList<DbvtNode^>
	{
	internal:
		DbvtNodePtrArray(btDbvtNode** nodePtrArray, int length);
		DbvtNodePtrArray(const btDbvtNode** nodePtrArray, int length);

	public:
		virtual void CopyTo(array<DbvtNode^>^ array, int arrayIndex) override;

		property DbvtNode^ default[int]
		{
			virtual DbvtNode^ get(int index) override;
			virtual void set(int index, DbvtNode^ value) override;
		}

	internal:
		property btDbvtNode** UnmanagedPointer
		{
			btDbvtNode** get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class DbvtProxyPtrArray : GenericList<DbvtProxy^>
	{
	internal:
		DbvtProxyPtrArray(btDbvtProxy** proxyPtrArray, int length);
		DbvtProxyPtrArray(const btDbvtProxy** proxyPtrArray, int length);

	public:
		virtual void CopyTo(array<DbvtProxy^>^ array, int arrayIndex) override;

		property DbvtProxy^ default[int]
		{
			virtual DbvtProxy^ get(int index) override;
			virtual void set(int index, DbvtProxy^ value) override;
		}

	internal:
		property btDbvtProxy** UnmanagedPointer
		{
			btDbvtProxy** get() new;
		}
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class FloatArray : GenericList<float>
	{
	internal:
		FloatArray(float* floatArray, int length);
		FloatArray(const float* floatArray, int length);

	public:
		FloatArray(int length);

		virtual bool Contains(float item) override;
		virtual void CopyTo(array<float>^ array, int arrayIndex) override;
		virtual int IndexOf(float item) override;

		property float default[int]
		{
			virtual float get(int index) override;
			virtual void set(int index, float value) override;
		}

	internal:
		property float* UnmanagedPointer
		{
			float* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class IntArray : GenericList<int>
	{
	internal:
		IntArray(int* intArray, int length);
		IntArray(const int* intArray, int length);

	public:
		IntArray(int length);

		virtual bool Contains(int item) override;
		virtual void CopyTo(array<int>^ array, int arrayIndex) override;
		virtual int IndexOf(int item) override;

		property int default[int]
		{
			virtual int get(int index) override;
			virtual void set(int index, int value) override;
		}

	internal:
		property int* UnmanagedPointer
		{
			int* get() new;
		}
	};

#ifndef DISABLE_SOFTBODY
	namespace SoftBody
	{
		ref class Node;

		[DebuggerDisplay("Count = {Count}")]
		[DebuggerTypeProxy(ListDebugView::typeid)]
		public ref class NodePtrArray : GenericList<Node^>
		{
		internal:
			NodePtrArray(btSoftBody::Node** nodePtrArray, int length);
			NodePtrArray(const btSoftBody::Node** nodePtrArray, int length);

		public:
			virtual void CopyTo(array<Node^>^ array, int arrayIndex) override;

			property Node^ default[int]
			{
				virtual Node^ get(int index) override;
				virtual void set(int index, Node^ value) override;
			}

		internal:
			property btSoftBody::Node** UnmanagedPointer
			{
				btSoftBody::Node** get() new;
			}
		};
	};
#endif

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class ScalarArray : GenericList<btScalar>
	{
	internal:
		ScalarArray(btScalar* scalarArray, int length);
		ScalarArray(const btScalar* scalarArray, int length);

	public:
		ScalarArray(int length);

		virtual bool Contains(btScalar item) override;
		virtual void CopyTo(array<btScalar>^ array, int arrayIndex) override;
		virtual int IndexOf(btScalar item) override;

		property float default[int]
		{
			virtual btScalar get(int index) override;
			virtual void set(int index, btScalar value) override;
		}

	internal:
		property btScalar* UnmanagedPointer
		{
			btScalar* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class UIntArray : GenericList<unsigned int>
	{
	internal:
		UIntArray(unsigned int* uintArray, int length);
		UIntArray(const unsigned int* uintArray, int length);

	public:
		virtual bool Contains(unsigned int item) override;
		virtual void CopyTo(array<unsigned int>^ array, int arrayIndex) override;
		virtual int IndexOf(unsigned int item) override;

		property unsigned int default[int]
		{
			virtual unsigned int get(int index) override;
			virtual void set(int index, unsigned int value) override;
		}

	internal:
		property unsigned int* UnmanagedPointer
		{
			unsigned int* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(ListDebugView::typeid)]
	public ref class UShortArray : GenericList<unsigned short>
	{
	internal:
		UShortArray(unsigned short* uShortArray, int length);
		UShortArray(const unsigned short* uShortArray, int length);

	public:
		virtual bool Contains(unsigned short item) override;
		virtual void CopyTo(array<unsigned short>^ array, int arrayIndex) override;
		virtual int IndexOf(unsigned short item) override;

		property unsigned short default[int]
		{
			virtual unsigned short get(int index) override;
			virtual void set(int index, unsigned short value) override;
		}

	internal:
		property unsigned short* UnmanagedPointer
		{
			unsigned short* get() new;
		}
	};

	[DebuggerDisplay("Count = {Count}")]
	[DebuggerTypeProxy(Vector3ListDebugView::typeid)]
	public ref class Vector3Array : GenericList<Vector3>
	{
	internal:
		Vector3Array(btVector3* vector3Array, int length);
		Vector3Array(const btVector3* vector3Array, int length);

	public:
		Vector3Array(int length);

		virtual bool Contains(Vector3 item) override;
		virtual void CopyTo(array<Vector3>^ array, int arrayIndex) override;
		virtual int IndexOf(Vector3 item) override;

		property Vector3 default[int]
		{
			virtual Vector3 get(int index) override;
			virtual void set(int index, Vector3 value) override;
		}

	internal:
		property btVector3* UnmanagedPointer
		{
			btVector3* get() new;
		}
	};
};
