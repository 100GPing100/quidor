#ifndef QUIDOR_PROPERTY_H
#define QUIDOR_PROPERTY_H

// quidor
#include "Type.h"


#define ObjectBoolProperty(ownerclass, propname) \
	private: \
		bool propv_##propname; \
	\
	public: \
		static const quidor::Property<ownerclass, bool> propname##Property; \
		\
		virtual bool is##propname() const { \
			return propname##Property.get(this); \
		} \
		\
		virtual void set##propname(bool value) { \
			propname##Property.set(this, value); \
		} \
	private:

#define ObjectBoolPropertyBody(ownerclass, propname) \
	const quidor::Property<ownerclass, bool> ownerclass::propname##Property = quidor::Property<ownerclass, bool>(&ownerclass::propv_##propname);


#define ObjectProperty(owner, type, name) \
	private: \
		type propv_##name; \
	\
	public: \
		static const quidor::Property<owner, type> name##Property; \
		\
		virtual type get##name() const { \
			return name##Property.get(this); \
		} \
		\
		virtual void set##name(type value) { \
			name##Property.set(this, value); \
		} \
	private:

#define ObjectPropertyBody(ownerclass, proptype, propname) \
	const quidor::Property<ownerclass, proptype> ownerclass::propname##Property = quidor::Property<ownerclass, proptype>(&ownerclass::propv_##propname);

#define ObjectUserProperty(owner, type, name) \
	private: \
		type propv_##name; \
	public: \
		static const quidor::Property<owner, type> name##Property; \
	private:

#define ObjectUserPropertyBody(owner, type, name) \
	const quidor::Property<owner, type> owner::name##Property = quidor::Property<owner, type>(&owner::propv_##name);


namespace quidor
{

[[deprecated("Outdated and possible removal in the future")]]
template<class owner, typename T>
class Property final
{
	T owner:: * member;

public:
	inline size_t size() const {
		return sizeof(T);
	}

	void set(owner * owner, T value) const {
		owner->*member = value;
	}
	T get(const owner * owner) const {
		return owner->*member;
	}

	Property(T owner:: * offset)
		: member(offset)
	{
	}
	virtual ~Property() { }
}; // Property<owner, T>

} // quidor

#endif // QUIDOR_PROPERTY_H