#ifndef QUIDOR_OBJECT_H
#define QUIDOR_OBJECT_H

// quidor
#include "Type.h"

#define ObjectMeta(class, parent) \
	public: \
		static quidor::Type * classtype() { \
			static quidor::Type type = quidor::Type(#class, parent::classtype()); \
			return &type; \
		} \
		\
		virtual quidor::Type * type() const { \
			return class::classtype(); \
		} \
	private:
// ObjectMeta

namespace quidor
{

class Object
{
public:
	static Type * classtype() {
		static Type type = Type("quidor::Object", nullptr);
		return &type;
	}

	virtual Type * type() const {
		return Object::classtype();
	}

	virtual const char * tostring() const {
		return this->type()->name();
	}

	bool isParentOf(const Object & o) const {
		return type()->isParentOf(o.type());
	}

	bool isChildOf(const Object & o) const {
		return type()->isChildOf(o.type());
	}

	template<class T>
	T * cast() {
		if (T::classtype()->isParentOf(this->type())) {
			return (T *) this;
		}
		
		return nullptr;
	}

	Object() { }
	virtual ~Object() { }
}; // Object

} // quidor

#endif // QUIDOR_OBJECT_H