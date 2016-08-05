//
// Created by Super on 05/08/2016.
//

#ifndef QUIDOR_TYPE_H
#define QUIDOR_TYPE_H


// std
#include <string>
#include <vector>

namespace quidor {
    class Type final {
        using Children = std::vector<const Type*>;

    public:
        const char * getName() const {
            return name.c_str();
        }

        const Type * getParent() const {
            return parent;
        }

        const Children getChildren() const {
            return children;
        }

        template<class T>
        bool isChildOf() const {
            // parent == type : comparing pointers, each quidor::Object
            // has it's own unique type, owned by ..::classType()
            return parent == T::classType() || parent->isChildOf<T>();
        }

        bool isChildOf(const Type * type) const {
            // parent == type : check isChildOf<T>
            return type != nullptr && (parent == type || parent->isChildOf(type));
        }

        template<class T>
        bool isParentOf() const {
            for (auto it : children) {
                // it == type : check isChildOf<T>
                if (it == T::classType() || it->isParentOf<T>()) {
                    return true;
                }
            }

            return false;
        }

        bool isParentOf(const Type * type) const {
            for (auto it : children) {
                // it == type : check isChildOf<T>
                if (it == type || it->isParentOf(type)) {
                    return true;
                }
            }

            return false;
        }

        Type() = delete;
        ~Type() = default;

        Type(std::string name, const Type * parent)
            : name(name)
            , parent(parent)
        {
            if (parent == nullptr) {
                return;
            }
            //this->children = Children();

            // quidor::Type is always passed around as const
            // we hack here as an exception so we do not
            // allow a non-const quidor::Type outside
            Type * hack = reinterpret_cast<Type *>((void *) parent);
            hack->children.push_back(this);
        }
    private:
        std::string name;
        const Type * parent;
        Children children;
    };
}


#endif //QUIDOR_TYPE_H
