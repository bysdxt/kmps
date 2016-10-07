#pragma once
#include <memory>
#include <exception>
#include "utils.h"
namespace kmps {
    class not_implement : public ::std::exception {
        using _Base = ::std::exception;
    public:
        inline not_implement() noexcept : _Base("Not Implement", -1) { }
        using _Base::operator=;
    };
    template <class T>
    class NodeBase {
    public:
        using Node = NodeBase<T>;
        using KeyType = T;
        void * tag = nullptr;
    protected:
        virtual Node * createChild(KeyType Key) = 0;
    public:
        virtual ~NodeBase() { }
        virtual KeyType operator*() const = 0;
        virtual const Node * operator[](KeyType key) const = 0;
        virtual Node * operator[](KeyType key) = 0;
        inline Node & operator()(KeyType Key) {
            auto pchild = (*this)[key];
            return *(pchild ? pchild : this->createChild(key));
        }
        virtual void operator_delete() = 0;
        virtual void operator_delete_arr() = 0;
        static inline void operator delete(void*thiz) { return (reinterpret_cast<Node*>(thiz))->operator_delete(); }
        static inline void operator delete[](void*thiz) { return (reinterpret_cast<Node*>(thiz))->operator_delete_arr(); }
        static inline void* operator new(size_t) noexcept(false) { throw not_implement(); }
        static inline void* operator new[](size_t) noexcept(false) { throw not_implement(); }
        static inline constexpr void* operator new(size_t, std::nothrow_t const&) noexcept { return nullptr; }
        static inline constexpr void* operator new[](size_t, std::nothrow_t const&) noexcept { return nullptr; }
    };

    template <class T>
    class NodeObjOnMemory : public NodeBase<T> {
    public:
        void operator_delete() {
            //return (::operator delete)(this);
            return;
        }
        void operator_delete_arr() {
            //return (::operator delete[])(this);
            return;
        }
        static inline void operator delete(void*thiz) { return (NodeBase<T>::operator delete)((NodeBase<T>*)reinterpret_cast<NodeObjOnMemory<T>*>(thiz)); }
        static inline void operator delete[](void*thiz) { return (NodeBase<T>::operator delete[])((NodeBase<T>*)reinterpret_cast<NodeObjOnMemory<T>*>(thiz)); }
        static inline void* operator new(size_t size) noexcept(false) { return (::operator new)(size); }
        static inline void* operator new[](size_t size) noexcept(false) { return (::operator new[])(size); }
        static inline void* operator new(size_t size, std::nothrow_t const& t) noexcept { return (::operator new)(size, t); }
        static inline void* operator new[](size_t size, std::nothrow_t const& t) noexcept { return (::operator new[])(size, t); }
    };

    class MemNode : public NodeObjOnMemory<unsigned __int8> {
    protected:
        Node * createChild(KeyType Key);
    public:
        KeyType operator*() const;
        const Node * operator[](KeyType key) const;
        Node * operator[](KeyType key);
    };
}