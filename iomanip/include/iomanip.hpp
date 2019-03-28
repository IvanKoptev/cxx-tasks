/* Custom manipulators.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>

//{ endm manipulator
std::ostream& endm(std::ostream& stream)
{
    return stream << "[eol]" << std::endl;
}
//}

//{ squares manipulator
class squares_wrapper
{
public:
    squares_wrapper(std::ostream& stream) :
        stream(stream)
    {}

    template<class T>
    std::ostream & operator<<(const T& data)
    {
        return stream << '[' << data << ']';
    }
private:
    std::ostream& stream;
};

class squares_impl { } squares;
squares_wrapper operator<<(std::ostream& stream, const squares_impl&)
{
    return squares_wrapper(stream);
}
//}

//{ add manipulator
class add_wrapper
{
public:
    add_wrapper(std::ostream& stream) :
            stream(stream)
    {}

    template<class T1>
    class add_wrapper_next
    {
    public:
        add_wrapper_next(std::ostream& stream, const T1& op1):
            op1(op1),
            stream(stream)
        {}

        template<class T2>
        std::ostream & operator<<(const T2& op2)
        {
            return stream << (op1 + op2);
        }
    private:
        T1 op1;
        std::ostream& stream;
    };

    template<class T1>
    add_wrapper_next<T1> operator<<(const T1& op1)
    {
        return add_wrapper_next<T1>(stream, op1);
    }
private:
    std::ostream& stream;
};

class add_impl { } add;
add_wrapper operator<<(std::ostream& stream, const add_impl&)
{
    return add_wrapper(stream);
}
//}

#endif // __IOMANIP_HPP__
