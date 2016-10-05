#pragma once
#include <memory>
#include <exception>
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
        using Node = NodeBase;
        using KeyType = T;
    protected:
        virtual Node * createChild(KeyType Key) = 0;
    public:
        virtual ~NodeBase() { }
        virtual bool isEnd() const = 0;
        virtual bool setEnd(bool isEnd, void *) = 0;
        virtual KeyType operator*() const = 0;
        virtual const Node * operator[](KeyType key) const = 0;
        virtual Node * operator[](KeyType key) = 0;
        virtual Node & operator()(KeyType key) {
            auto pchild = this->operator[](key);
            return *(pchild ? pchild : this->createChild(key));
        }
        virtual void operator_delete() = 0;
        virtual void operator_delete_arr() = 0;
        /*
            subclass must override operator delete like
            static inline void operator delete(void*thiz) { delete (Node*)reinterpret_cast<C*>(thiz); }
            when (Node*)(C*)0 != 0
        */
        static inline void operator delete(void*thiz) { return reinterpret_cast<Node*>(thiz)->operator_delete(); }
        /*
        subclass must override operator delete[] like
        static inline void operator delete[](void*thiz) { delete[] (Node*)reinterpret_cast<C*>(thiz); }
        when (Node*)(C*)0 != 0
        */
        static inline void operator delete[](void*thiz) { return reinterpret_cast<Node*>(thiz)->operator_delete_arr(); }
        static inline void* operator new(size_t) noexcept(false) { throw not_implement(); }
        static inline void* operator new[](size_t) noexcept(false) { throw not_implement(); }
        static inline constexpr void* operator new(size_t, std::nothrow_t const&) noexcept { return nullptr; }
        static inline constexpr void* operator new[](size_t, std::nothrow_t const&) noexcept { return nullptr; }
    };

    //class MemNode : public NodeBase<unsigned __int8> {
    //public:
    //};
}