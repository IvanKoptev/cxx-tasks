/* Variant classes.
 * @file
 * @date 2018-08-12
 * @author Anonymous
 */

#ifndef __VARIANT_HPP__
#define __VARIANT_HPP__

#include <map>
#include <memory>
#include <variant>
#include <vector>

#include <boost/variant.hpp>

//{ number
struct number : std::variant<int, float>
{
    using variant::variant;
};
//}

//{ array
struct array : std::vector<number>
{
    using vector::vector;
};
//}

//{ recursive_array
struct recursive_array : std::vector<std::variant<number, std::shared_ptr<recursive_array>>>
{
    using vector::vector;
};
//}

//{ recursive_array2
struct recursive_array2 : std::vector<std::variant<number, boost::recursive_wrapper<recursive_array2>>>
{
    using vector::vector;
};
//}

//{ variant_decorator
template<class... Ts>
struct variant_decorator : std::variant<Ts...>
{
    using std::variant<Ts...>::variant;

    template <class T>
    const T& as() const
    {
        if constexpr (std::disjunction_v<std::is_same<T, Ts>...>)
        {
            return std::get<T>(*this);
        }
        else
        {
            return std::get<boost::recursive_wrapper<T>>(*this).get();
        }
    }

    template <class T>
    T& as()
    {
        return const_cast<T&>(const_cast<const variant_decorator *>(this)->as<T>());
    }
};
//}

//{ recursive_map
struct recursive_map : std::map<std::string, variant_decorator<int, bool, std::string, boost::recursive_wrapper<recursive_map>>>
{
    using map::map;
};
//}

#endif // __VARIANT_HPP__
