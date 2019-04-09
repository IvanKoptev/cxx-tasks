/* Image iterator.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <algorithm>
#include <type_traits>
#include <vector>
#include <utility>

#include <boost/iterator/iterator_adaptor.hpp>

//{ image iterator
template<class Iterator>
class image_iterator: public boost::iterator_adaptor<image_iterator<Iterator>, Iterator>
{
public:
    using diff_type = typename image_iterator::difference_type;

    image_iterator(Iterator iter, size_t width, size_t stride) :
            image_iterator::iterator_adaptor_(iter),
            width_(width),
            stride_(stride)
    {}

    void advance(diff_type n)
    {
        size_t rest = (n > 0) ? width_ - index_ % stride_  - 1: index_ % stride_;
        size_t stride_count = 0;

        if (abs(n) > (int)rest)
        {
            stride_count = ceil((double)(abs(n) - rest) / width_);
        }
        int res = n/abs(n) * (stride_count * (stride_ - width_) + abs(n));
        this->base_reference() += res;
        index_ += res;
    }

    diff_type distance_to( image_iterator const &x ) const
    {
        auto n = x.base() - this->base();
        auto rest = (n > 0) ? index_ : x.index_ % stride_;
        auto s = abs(n) + rest;
        auto res = abs(n)/n * (s/(int)stride_ * (int)width_ + s%(int)stride_  - rest);

        return res;
    }

    void increment()
    {
        if (index_ % stride_ == 0)
        {
            this->base_reference() += stride_ - width_ + 1;
            index_ += stride_ - width_ + 1;
        }
        else
        {
            this->base_reference()++;
            index_++;
        }
    }

    void decrement()
    {
        if (width_- index_ % (int)stride_ == 0)
        {
            this->base_reference() -= width_- index_ % (int)stride_ + 1;
            index_ += width_- index_ % (int)stride_ + 1;
        }
        else
        {
            this->base_reference()--;
            index_--;
        }
    }

private:
    size_t width_;
    size_t stride_;
    size_t index_ = 0;
};
//}

template<class Container = std::vector<uint8_t>>
class image
{
public:
    // stride > width
    image(size_t width, size_t height, size_t stride):
        data(stride * height),
        width_(width),
        stride_(stride)
    {}

    auto begin()
    {
        return image_iterator(data.begin(), width_, stride_);
    }

    auto end()
    {
        return image_iterator(data.end(), width_, stride_);
    }

    auto begin() const
    {
        return image_iterator(data.begin(), width_, stride_);
    }

    auto end() const
    {
        return image_iterator(data.end(), width_, stride_);
    }

private:
    Container data; // image data including strides. Access by (x, y): data[y * stride_ + x]
    size_t width_;
    size_t stride_;
};

#endif // __ITERATOR_HPP__
