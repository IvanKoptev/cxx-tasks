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
        U2FsdGVkX18rY3j/AAAAAOi8uIkbLq0Bss7wsYGXuV5WPRj+92OCSV3G8U8PorQm8WXaIyFryVQ=
            U2FsdGVkX18rY3j/AAAAAF0y8ZyibBqg
            U2FsdGVkX18rY3j/AAAAAK++jrMACIG+
            U2FsdGVkX18rY3j/AAAAAFcoFKZQhArE
            U2FsdGVkX18rY3j/AAAAANaoOro3MFcFNwkrS34rGrA=
            U2FsdGVkX18rY3j/AAAAAGxBu5e6birqftMCGkIPhl0=
            U2FsdGVkX18rY3j/AAAAAHFEj3p+nhw1RZbsq7/avGCIGWW8sX5LsGDYGieiLSLe
            U2FsdGVkX18rY3j/AAAAAHFEj3p+nhw1RZbsq7/avGCwT1w6GMvOCUQ7Z6P4DIDn763bJbiW5Qo=
            U2FsdGVkX18rY3j/AAAAAHFEj3p+nhw1RZbsq7/avGCpAHvOTJ3CUhb0JHS4Q4BE
        U2FsdGVkX18rY3j/AAAAADqDhTbkcGRy

        U2FsdGVkX18rY3j/AAAAAP9Qr3OmDmIB8oZSvdCKs6voTcvB504lR5B5/fUfarI4B3GHZ6oYMIzOqFF57Bdnqw==
        U2FsdGVkX18rY3j/AAAAANSdTqkaEIrLIWwaIZqOki9YTOYAjoxpp/ljn/yWBdHwWkxnmNEPLoSgLXkePt9d0qvZtqy3AtEe

        U2FsdGVkX18rY3j/AAAAABFhZyhGduW29F5+sUe/DGxkZLB6Fx89o82ohWhSuKPTmjQ/3OnW1BXTSkBm36aBGiSh54gjGzR4
        U2FsdGVkX18rY3j/AAAAABTlhjN/yYk/
            U2FsdGVkX18rY3j/AAAAAOi8uIkbLq0B9Sc2OVkVI8S+FHTnybsiK/Rm/KRTBkZScQruuVMZCPMgmCzxOLsW1A==
            U2FsdGVkX18rY3j/AAAAAOi8uIkbLq0B9Sc2OVkVI8S+FHTnybsiK5f5ew+ZSEcLSGukGR8yN2c=
        U2FsdGVkX18rY3j/AAAAACyRUNu3KUfp
        //}
    }
}

namespace parser
{
    namespace json
    {
        //? Why I need ``sfloat_`` instead of just ``x3::float_``?
        //? What is the syntax ``class array_``? Is it wrong?
        const auto sfloat_ = x3::real_parser<float, x3::strict_real_policies<float>>();

        //{ describe json grammar
        U2FsdGVkX18rY3j/AAAAANG1o0Gm0rUPeM5XWXlrOlzztIOCPrX9ga+GTyaheinTUspNOXeDdEfRrHE+Qko0YQ==
        U2FsdGVkX18rY3j/AAAAANG1o0Gm0rUPe+83rgaYWabrVPjX8cHIXp3pq+q3UveC9oIlNY+UKBa7jGpj5pcugS9aK6/QHEqV

        U2FsdGVkX18rY3j/AAAAAPJi4Q02F3n08Yx6/NUO1tdkVfh30LrWQW6fxlm3YmsyGEzloeOzfUCgo5YZVF/Lnhs0bYuo8IFgvmZBNyjSz0M=
        U2FsdGVkX18rY3j/AAAAAPJi4Q02F3n07RI/k+eZfJky3dy07vWfpthQ9m43G577vb+FotoO1BU/gqYaSaU3CsbRshUFurdCUasHkZYVg+24ZGt1nH/XaQ==
        U2FsdGVkX18rY3j/AAAAAPJi4Q02F3n0pXmlD+MCN8HqR/yhCo8tv+6OwtZPqjvORS+H6Sa5UjMB8+sHIngN5QG3E0Gw3Fjyc5uIh0jN/fE=

        U2FsdGVkX18rY3j/AAAAANG1o0Gm0rUPPygZ4ZShuW3kob9jN5QsEMXTNswI2R7CYbINJB8SzoLCcbnp3n8NrOh/UnuIoEUy4jLhN0UIOJkr5bKGbI5ugg==
                         U2FsdGVkX18rY3j/AAAAAIjznJRjL0Icwxx3PmL2fCCHtjpLB1E6jpJGIT2XGR1ktfWNBQ5yw+NK+ivQgxrSfgA8MG2dCfwTztaLWAwzgg+A3txjzfNxhQ==

        U2FsdGVkX18rY3j/AAAAANG1o0Gm0rUP5/DMOaineB1uGqsDBGO3N2Fl/F80RB55z8EDYbPQMrw4LSICDW5iq8lYWdB0o4qGBl4blVvyha83uDSMCdeXTvXkCjCJUHzKjyCH3MNJRT5mLG7UBn6uC+5UwIYjqf+//GkX39ZqUG8=
                             U2FsdGVkX18rY3j/AAAAAI2pyCR55iqn8V5nQhL1mPXioqz7KW46/t2SNk7x+9v/e+Hgi/OXYWA=

        U2FsdGVkX18rY3j/AAAAANG1o0Gm0rUPL77eCAoXxfZC02oMfbv9hOVI9qIHD+SHAte9VHO+uprU7sY2GF01ZQ/XpCExnHsN
        U2FsdGVkX18rY3j/AAAAANG1o0Gm0rUPx/jhxnPTpbDgESh2tISVoBaniRA9PFQDcondPJup0afcWI7SM3LqEonBq8XAmBvh
        U2FsdGVkX18rY3j/AAAAANG1o0Gm0rUPax1Eoi74X1gE8URbVsMxoe/CT7EdaY2JRAI2C2nwSlA=
        //}

        BOOST_SPIRIT_DEFINE(array, object, json)
    }
}

namespace literals
{
    namespace json
    {
        //{ describe ``_json`` literal
        U2FsdGVkX18rY3j/AAAAADGncsMOXX7tqqi0c3z875Hr2K6SfA1QK0cGnIIS2nLrP11uoIKs/s3MbmHBhED0tQZT9EUYx8lV
        U2FsdGVkX18rY3j/AAAAABTlhjN/yYk/
            U2FsdGVkX18rY3j/AAAAACrdgNwAeAyjDYPlZDkesFi90rArTVa0f9aCHmwN0fmsNoBanoMTxYJhbqoTKZfrFBTYq8eS6wifl4uosiyRNsQ22NXpEkoQQwftL6uUC0D7/6TRBuK4xVoBb2v2yFz8wQ==
        U2FsdGVkX18rY3j/AAAAAKo28xp24gBJ
        //}
    }
}

#endif // __JSON_HPP__
