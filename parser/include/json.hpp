/* Json object.
 * @file
 * @date 2018-08-09
 * @author Anonymous
 */

#ifndef __JSON_HPP__
#define __JSON_HPP__

#include <map>
#include <string>
#include <vector>

#include <boost/spirit/home/x3.hpp>
//? Why I need ``std_pair`` header? Do I need one for std::map?
//! std_pair.hpp содержит необходимые адаптеры для создания объектов key_value
#include <boost/fusion/adapted/std_pair.hpp>

#include "parser.hpp"
#include "quoted_string.hpp"
#include "variant_decorator.hpp"

/* Json EBNF specification (https://www.json.org)
 *      string := \" ([^\"] | \\\")* \"
 *      number := [0-9]+(\.[0-9]*)?
 *      boolean := "true" | "false"
 *      nullable := "null"
 *      value := number | string | boolean | nullable | array | object
 *      array := '[' value (',' value)* ']'
 *      key_value := string ':' value
 *      object := '{' key_value (',' key_value)* '}'
 *      json := array | object
 */

namespace types
{
    namespace json
    {
        //{ describe json data types
        using value = variant_decorator<int, float, bool, std::string, std::nullptr_t, struct array, struct object>;

        struct array : public std::vector<value> {};
        struct object : public std::map<std::string, value> {};

        using json = variant_decorator<array, object>;
        //}
    }
}

namespace parser
{
    namespace json
    {
        //? Why I need ``sfloat_`` instead of just ``x3::float_``?
        //! В формате sfloat_ должна быть точка, что позволяет разделить float и int при парсинге
        //? What is the syntax ``class array_``? Is it wrong?
        //! class array_ это всего лишь указатель. Если мы не будем разыменовывать его, то его можно не определять
        const auto sfloat_ = x3::real_parser<float, x3::strict_real_policies<float>>();

        //{ describe json grammar
        const auto number = sfloat_ | x3::int_;
        const auto nullable = x3::lit("null") >> x3::attr(nullptr);

        x3::rule<class array_, types::json::array> array;
        x3::rule<class obect_, types::json::object> object;
        x3::rule<class json_, types::json::json> json;

        const auto value = x3::rule<struct value, types::json::value> () 
                         = nullable | number | x3::ascii::bool_ | quoted_string | array | object;

        const auto key_value = x3::rule<struct key_value, std::pair<std::string, types::json::value>> {} = quoted_string >> ':' >> value;

        const auto array_def =  '[' >> value % ',' >> ']';
        const auto object_def = '{' >> key_value % ',' >> '}';
        const auto json_def = array | object;
        //}

        BOOST_SPIRIT_DEFINE(array, object, json)
    }
}

namespace literals
{
    namespace json
    {
        //{ describe ``_json`` literal
        types::json::json operator "" _json(const char* str, size_t str_size)
        {
            return parser::load_from_string<types::json::json>(std::string(str, str_size), parser::json::json);
        }
        //}
    }
}

#endif // __JSON_HPP__
