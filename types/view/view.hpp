#ifndef ENN_VIEW_HPP
#define ENN_VIEW_HPP

#include <memory>

#include <cstddef>
#include <cassert>

#include <array>
#include <vector>

namespace enn {

    // list --------------------------------------------------------------------

    template<typename T, typename Deleter = std::default_delete<T>>
    class list {

        std::unique_ptr<T[], Deleter> data_;
        std::size_t size_;

    public:

        list() :
            data_(nullptr), size_(0) {}
        explicit list(std::size_t size) :
            data_(size > 0 ? new T[size] : nullptr), size_(size) {}
        list(std::unique_ptr<T[], Deleter> data, std::size_t size) :
            data_(std::move(data)), size_(size) {}

        std::size_t size() const { return size_; }

        T const* data() const { return data_.get(); }
        T* data() { return data_.get(); }

        T const* cbegin() const { return data(); }
        T const* cend() const { return data() + size(); }

        T const* begin() const { return cbegin(); }
        T const* end() const { return cend(); }

        T* begin() { return data(); }
        T* end() { return data() + size(); }

        T const& operator[](std::size_t idx) const {
            assert(idx < size());
            return data()[idx];
        }

        T& operator[](std::size_t idx) {
            assert(idx < size());
            return data()[idx];
        }

    };

    // view --------------------------------------------------------------------

    template<typename T>
    class view {

        T* data_;
        std::size_t size_;

    public:

        view() : data_(nullptr), size_(0) {}
        view(T* begin, T* end) : data_(begin), size_(end-begin) {}
        view(T* data, std::size_t size) : data_(data), size_(size) {}

        template<typename Deleter>
        view(list<T, Deleter>& list) : data_(list.data()), size_(list.size()) {}
        template<std::size_t N>
        view(std::array<T, N>& arr) : data_(arr.data()), size_(arr.size()) {}
        template<typename Alloc>
        view(std::vector<T, Alloc>& vec) : data_(vec.data()), size_(vec.size()) {}

        std::size_t size() const { return size_; }

        T const* data() const { return data_; }
        T* data() { return data_; }

        T const* cbegin() const { return data(); }
        T const* cend() const { return data() + size(); }

        T const* begin() const { return cbegin(); }
        T const* end() const { return cend(); }

        T* begin() { return data(); }
        T* end() { return data() + size(); }

        T const& operator[](std::size_t idx) const {
            assert(idx < size());
            return data()[idx];
        }

        T& operator[](std::size_t idx) {
            assert(idx < size());
            return data()[idx];
        }

    };

    // helpers -----------------------------------------------------------------

    template<typename T, typename Deleter>
    inline list<T, Deleter> make_list(std::unique_ptr<T[], Deleter> data, std::size_t size) {
        return list<T, Deleter>(data, size);
    }

    template<typename T>
    inline view<T> make_view(T* begin, T* end) {
        return view<T>(begin, end);
    }

    template<typename T>
    inline view<T> make_view(T* begin, std::size_t size) {
        return view<T>(begin, size);
    }

} // namespace enn

#endif // ENN_VIEW_HPP
