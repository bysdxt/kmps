#pragma once
#include <functional>
#include <utility>
namespace utils {
    template <bool v>
    struct Boolen {
        static constexpr const auto value = v;
    };
    using True = Boolen<true>;
    using False = Boolen<false>;
    namespace __internal {
        template <class T1, class T2>
        struct isSameType {
            using Result = False;
        };
        template <class T>
        struct isSameType<T, T> {
            using Result = True;
        };
        template <class T>
        struct op_and {
            static constexpr auto call(T v1, T v2) {
                return v1 && v2;
            }
        };
        template <class T>
        struct op_or {
            static constexpr auto call(T v1, T v2) {
                return v1 || v2;
            }
        };
        template <class T>
        struct op_xor {
            static constexpr auto call(T v1, T v2) {
                return v1 ^ v2;
            }
        };
        template <class T, class F, template <T> class M>
        struct Op {
            template <T v1, T v2>
            using Result = M<F::call(v1, v2)>;
        };
        template <class v1, class v2>
        struct And: public Op<bool, op_and<bool>, Boolen>::Result<v1::value, v2::value> { };
        template <class v1, class v2>
        struct Or: public Op<bool, op_or<bool>, Boolen>::Result<v1::value, v2::value> { };
        template <class v1, class v2>
        struct Xor: public Op<bool, op_xor<bool>, Boolen>::Result<v1::value, v2::value> { };
    }
    template <class T1, class T2>
    using isSameType = typename __internal::template isSameType<T1, T2>::Result;
    template <size_t index, class ... Ts>
    struct TypesGet;
    template <class T, class ... Ts>
    struct TypesGet<0, T, Ts...> {
        using Result = T;
    };
    template <size_t index, class T, class ... Ts>
    struct TypesGet<index, T, Ts...> {
        using Result = typename TypesGet<index - 1, Ts...>::Result;
    };
    template <class ... Ts>
    struct Types;
    template <class T, class ... Ts>
    struct Types<T, Ts...> {
        using Type = T;
        using rest = Types<Ts...>;
        template <size_t index>
        using Get = typename TypesGet<index, T, Ts...>::Result;
        static constexpr const size_t nTypes = 1 + sizeof...(Ts);
    };
    template <>
    struct Types<> {
        using rest = void;
        static constexpr const size_t nTypes = 0;
    };
    namespace Function {
        enum class CallingConvention : unsigned {
            Unknown,
            Cdecl,
            Clrcall,
            Stdcall,
            Fastcall,
            Thiscall,
            Vectorcall,
        };
        template <CallingConvention cc>
        struct ConventionType { static constexpr const auto Convention = cc; };
        template <class T, class ... Ts>
        struct DeclarationBase {
            using ResultType = T;
            using ArgumentTypes = Types<Ts...>;
            static constexpr const size_t nArguments = sizeof...(Ts);
        };
        template <class O, class T, class ... Ts>
        struct DeclarationBase2 {
            using OwnType = O;
            using ResultType = T;
            using ArgumentTypes = Types<Ts...>;
            static constexpr const size_t nArguments = sizeof...(Ts);
        };
        template <class T>
        struct Declaration {
            static constexpr const auto Convention = CallingConvention::Unknown;
            static constexpr const size_t nArguments = -1;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__cdecl)(Ts...)> : public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Cdecl>{
            using RawType = typename ::std::remove_pointer<T(__cdecl*)(Ts...)>::type;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__cdecl*)(Ts...)>: public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Cdecl> {
            using RawType = typename ::std::remove_pointer<T(__cdecl*)(Ts...)>::type;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__stdcall)(Ts...)>: public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Stdcall> {
            using RawType = typename ::std::remove_pointer<T(__stdcall*)(Ts...)>::type;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__stdcall*)(Ts...)>: public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Stdcall> {
            using RawType = typename ::std::remove_pointer<T(__stdcall*)(Ts...)>::type;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__fastcall)(Ts...)>: public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Fastcall> {
            using RawType = typename ::std::remove_pointer<T(__fastcall*)(Ts...)>::type;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__fastcall*)(Ts...)>: public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Fastcall> {
            using RawType = typename ::std::remove_pointer<T(__fastcall*)(Ts...)>::type;
        };
        template <class O, class T, class ... Ts>
        struct Declaration<T(O::*)(Ts...)>: public DeclarationBase2<O, T, Ts...>, public ConventionType<CallingConvention::Thiscall> {
            using RawType = typename ::std::remove_pointer<T(O::*)(Ts...)>::type;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__vectorcall)(Ts...)>: public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Vectorcall> {
            using RawType = typename ::std::remove_pointer<T(__vectorcall*)(Ts...)>::type;
        };
        template <class T, class ... Ts>
        struct Declaration<T(__vectorcall*)(Ts...)>: public DeclarationBase<T, Ts...>, public ConventionType<CallingConvention::Vectorcall> {
            using RawType = typename ::std::remove_pointer<T(__vectorcall*)(Ts...)>::type;
        };
        template <class T> struct Declaration<Declaration<T>>: public Declaration<T> { };
        template <class T> struct Declaration<::std::function<T>>: public Declaration<T> { };
    }
}