/* Type decorator for variant.
 * @file
 * @date 2018-08-15
 * @author Anonymous
 */

#ifndef __VARIANT_DECORATOR_HPP__
#define __VARIANT_DECORATOR_HPP__

#include <boost/spirit/home/x3/support/ast/variant.hpp>

namespace x3 = boost::spirit::x3;

//? How to inherit x3::variant constructor & ``operator=``?
//! Для наследования членов класса-родителя нужно использовать using
//? Why I need inherited constructor & ``operator=``?
//! Данный класс является декоратором, то есть добавляет новые методы для работы, но сама структура класса остается прежней. Поэтому мы не меняем конструктор и оператор =, а наследуем их
//? How many constructors did I inherit?
//! Конструктор по умолчанию и конструктор копирования. Все остальное проинициализировал компилятор (см. следующий ответ)
//? Do I need my own constructor & ``operator=``? Why?
//! Необходимо явно указать, что в качестве конструктора(и оператора =) будет использоваться реализация родительского класса. Иначе компилятор сам создаст создаст пустые тела для этих методов и выдаст ошибку
//{
template<class... Ts>
struct variant_decorator: public x3::variant<Ts...>
{
    using x3::variant<Ts...>::operator=;
    using x3::variant<Ts...>::variant;

    variant_decorator()=default;
    variant_decorator(variant_decorator const&)=default;
    variant_decorator& operator=(variant_decorator const&)=default;

    //? Do I need a ``const``-version?
    template<class T>
    T& as()
    {
        return const_cast<T&>(const_cast<const variant_decorator*>(this)->as<T>());
    }

    template<class T>
    const T& as() const
    {
        return boost::get<T>(*this);
    }
};
//}

#endif // __VARIANT_DECORATOR_HPP__
