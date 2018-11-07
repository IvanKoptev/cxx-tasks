/* Map of types.
 * @file
 * @date 2018-08-25
 * @author Anonymous
 */

#ifndef __TYPE_MAP_HPP__
#define __TYPE_MAP_HPP__

#include <array>
#include <tuple>

namespace detail
{
    template<class T, class Tuple>
    struct type_to_index;

    template<class T, class... Ts>
    struct type_to_index<T, std::tuple<T, Ts...>>
    {
        constexpr static size_t v = 0;
    };

    template<class T, class U, class... Ts>
    struct type_to_index<T, std::tuple<U, Ts...>>
    {
        constexpr static size_t v = 1 + type_to_index<T, std::tuple<Ts...>>::v;
    };
}

//? What is wrong with ``*this[i]``?
//{
U2FsdGVkX18rY3j/AAAAANx44hwxjb53f81ro55FgjVXvVruuQY9rxw3P+/2qV0E
U2FsdGVkX18rY3j/AAAAADFERDBOf8Y5a3w89XcQibw2D9oodSQv4Uw663gCGgUZrcqywCOEt9TxdByyY9Nzg5cD8HadT91K
U2FsdGVkX18rY3j/AAAAABTlhjN/yYk/
U2FsdGVkX18rY3j/AAAAALLJcs7sOMBehwfeh/I05UI=
    U2FsdGVkX18rY3j/AAAAAN8uiGH/hwvKzWdsDeUR6wX257j/FFnaMZQ3WybA/DyIXzvYSLcKyt8=

    U2FsdGVkX18rY3j/AAAAAAE2FEuHRET/hvfsd/OPRRX/m6qR5EL3uxjnQVPGP//83Tu+jRP0yj5Wz0J4O+fEa5cYFS3hbYA417xw+m73Rd4S1hzz0ovTEwBUNoq/qQl2D52wxMXYwIA=
    U2FsdGVkX18rY3j/AAAAAPhJEBE1FgSp

    U2FsdGVkX18rY3j/AAAAANx44hwxjb53pgRNcuzzorI1gl+fBNs2pg==
    U2FsdGVkX18rY3j/AAAAAJtWaYX/I8hLyqWd2uXlrBY=
    U2FsdGVkX18rY3j/AAAAABTlhjN/yYk/
        U2FsdGVkX18rY3j/AAAAAICMVMxRSuaL2Sqe2bNlEi8eZ4WrTxDeqQTLfHn7K5pxjqwPyZEJFRF0uCb/9MFlOPhhgt1ugxpHRltbwBE08oyu1/kOb7kKTQ==
    U2FsdGVkX18rY3j/AAAAAKo28xp24gBJ

    U2FsdGVkX18rY3j/AAAAANx44hwxjb53pgRNcuzzorI1gl+fBNs2pg==
    U2FsdGVkX18rY3j/AAAAAOk/bpa31BFXbmL32RxGW1YKI/76XiK7vA==
    U2FsdGVkX18rY3j/AAAAABTlhjN/yYk/
        U2FsdGVkX18rY3j/AAAAAA0T1FZXPkuhqe/9HCuGHBwsW59AEd7C3EC4L7oxHbatk1ZmRLFT/FJWVzvCKVvc/cPM8mWXqYESyGhYSScUJ1oI8+HmmnCEgw==
        U2FsdGVkX18rY3j/AAAAAOSQrmTHWW41LZ0F5adiS/c2YvbASDgJdw==
    U2FsdGVkX18rY3j/AAAAAKo28xp24gBJ
U2FsdGVkX18rY3j/AAAAACyRUNu3KUfp
//}

namespace std
{
    template<typename T, class TypeMap>
    decltype(auto) get(TypeMap& tm)
    {
        //{ How to call ``as``?
        U2FsdGVkX18rY3j/AAAAAH8QVkn3mKfo+JzdRrwIup7s7d0fZ2u6bDV3RAFsM4PK
        //}
    }
}

#endif // __TYPE_MAP_HPP__
