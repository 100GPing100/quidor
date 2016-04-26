#ifndef QUIDOR_TYPE_H
#define QUIDOR_TYPE_H

// std
#include <vector>

namespace quidor
{

template<class owner, typename T> class Property;

class Type final
{
private:
	const char * _name;
	const Type * _parenttype;
	std::vector<const Type *> _children;

public:
	const char * name() const;
	const Type * parenttype() const;
	bool isChildOf(const Type * type) const;
	bool isParentOf(const Type * type) const;

	Type(const char * name, Type * parenttype);
	~Type();
}; // Type

} // quidor

#endif // QUIDOR_TYPE_H