#pragma once
#include <memory>
#include <exception>
namespace kmps {
    class not_implement : public ::std::exception {
    public:
        inline not_implement() throw() : ::std::exception("Not Implement", -1) { }
        using ::std::exception::operator=;
    };
    template <class T>
    class NodeBase {
    public:
        using MyTy = NodeBase;
        using Ty = T;
        virtual ~NodeBase() { }
        virtual MyTy * operator[](Ty key) = 0;
        virtual const MyTy * operator[](Ty key) const = 0;
        virtual void operator_delete() = 0;
        virtual void operator_delete_arr() = 0;
        static inline void operator delete(void*thiz) { return reinterpret_cast<MyTy*>(thiz)->operator_delete(); }
        static inline void operator delete[](void*thiz) { return reinterpret_cast<MyTy*>(thiz)->operator_delete_arr(); }
        static inline void* operator new(size_t) noexcept(false) { throw not_implement(); }
        static inline void* operator new[](size_t) noexcept(false) { throw not_implement(); }
        static inline void* operator new(size_t, std::nothrow_t const&) noexcept { return nullptr; }
        static inline void* operator new[](size_t, std::nothrow_t const&) noexcept { return nullptr; }
    };

    class MemNode : public NodeBase<unsigned __int8> {
    public:
        int b;
        MyTy * operator[](Ty key);
        const MyTy * operator[](Ty key) const;
        void operator_delete();
        void operator_delete_arr();
    };
}