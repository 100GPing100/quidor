//
// Created by Super on 05/08/2016.
//

#ifndef QUIDOR_OBJECT_H
#define QUIDOR_OBJECT_H


// std
#include <memory>

// quidor
#include "Type.h"


#define ObjectMeta(class, parent) \
    public: \
        static const quidor::Type * classType() { \
            static quidor::Type type (#class, parent::classType()); \
            return &type; \
        } \
        \
        virtual const quidor::Type * getClassType() const { \
            return class::classType(); \
        } \
    private:
//ObjectMeta(class, parent)

namespace quidor {
    class Object {
    public:
        static const Type * classType() {
            // owned here, comparable by pointer comparison (const Type * A == const Type * B)
            static Type type ("quidor::Object", nullptr);
            return &type;
        }

        virtual const Type * getClassType() const {
            return quidor::Object::classType();
        }

        virtual std::string toString() const {
            return this->getClassType()->getName();
        }

        Object() = default;
        virtual ~Object() = default;
    };
}


#endif //QUIDOR_OBJECT_H
