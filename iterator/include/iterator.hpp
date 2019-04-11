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
private:
    friend class boost::iterator_core_access;
    using diff_type = typename image_iterator::difference_type;
    int width_;
    int stride_;
    Iterator row_;

    void advance(diff_type n)
    {
        auto offset = (this->base_reference() - row_);
        double delta = n + offset;
        double num_rows = delta / width_;
        if (delta > 0)
        {
            row_ += (int) num_rows * stride_;
            this->base_reference() = row_ + delta - (int) num_rows * width_;
        }
        else
        {
            row_ += floor(num_rows) * stride_;
            this->base_reference() = row_ + width_ + delta - (floor(num_rows) + 1) * width_;
        }
    }

    diff_type distance_to( image_iterator const &x ) const
    {
        return (x.row_ - row_) / stride_ * width_ + (x.base_reference() - x.row_) - (this->base_reference() - row_);
    }

    void increment()
    {
        if (this->base_reference() - row_ == width_ - 1)
        {
            this->base_reference() += stride_ - width_;
            row_ += stride_;
        }
        ++this->base_reference();
    }

    void decrement()
    {
        if (this->base_reference() - row_ == 0)
        {
            this->base_reference() -= stride_ - width_;
            row_ -= stride_;
        }
        --this->base_reference();
    }
    
public:
    image_iterator(Iterator iter, size_t width, size_t stride) :
            image_iterator::iterator_adaptor_(iter),
            width_(width),
            stride_(stride),
            row_(iter)
    {}
};
//}

template<class Container = std::vector<int>>
class image
{
public:
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
