#ifndef ARRAY_VIEW_HPP
#define ARRAY_VIEW_HPP

#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <vector>

namespace html
{
    namespace impl
    {
        template <typename T>
        class array_view
        {
        private:
            T* m_data;
            std::size_t m_size;

        public:
            using value_type = T;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = T*;
            using const_pointer = const T*;
            using iterator = pointer;
            using const_iterator = const_pointer;

            static constexpr std::size_t npos = static_cast<std::size_t>(-1);

            constexpr array_view() noexcept : array_view(nullptr, 0) {}
            constexpr array_view(T* data, std::size_t size) noexcept : m_data(data), m_size(size) {}

            constexpr bool empty() const noexcept { return !m_size; }
            constexpr std::size_t size() const noexcept { return m_size; }

            constexpr pointer data() noexcept { return m_data; }
            constexpr const_pointer data() const noexcept { return m_data; }
            constexpr reference operator[](std::size_t index) { return m_data[index]; }
            constexpr const_reference operator[](std::size_t index) const { return m_data[index]; }

            constexpr reference front() { return *m_data; }
            constexpr const_reference front() const { return *m_data; }
            constexpr reference back() { return m_data[m_size - 1]; }
            constexpr const_reference back() const { return m_data[m_size - 1]; }

            constexpr iterator begin() noexcept { return m_data; }
            constexpr const_iterator begin() const noexcept { return m_data; }
            constexpr const_iterator cbegin() const noexcept { return m_data; }
            constexpr iterator end() noexcept { return m_data + m_size; }
            constexpr const_iterator end() const noexcept { return m_data + m_size; }
            constexpr const_iterator cend() const noexcept { return m_data + m_size; }

            constexpr std::size_t find(const T& value) const noexcept
            {
                for (std::size_t i = 0; i < m_size; i++)
                {
                    if (m_data[i] == value) return i;
                }
                return npos;
            }
            constexpr std::size_t find(std::initializer_list<T> values) const noexcept
            {
                for (std::size_t i = 0; i < m_size; i++)
                {
                    for (const T value : values)
                    {
                        if (m_data[i] == value) return i;
                    }
                }
                return npos;
            }

            constexpr array_view& operator+=(std::size_t n)
            {
                n = std::min(n, m_size);
                m_size -= n;
                m_data += n;
                return *this;
            }
            constexpr array_view& operator++()
            {
                if (m_size > 0)
                {
                    m_data++;
                    m_size--;
                }
                return *this;
            }
            constexpr array_view operator++(int)
            {
                array_view result = *this;
                operator++();
                return result;
            }

            friend constexpr array_view operator+(array_view b, std::size_t n)
            {
                n = std::min(n, b.m_size);
                return array_view{ b.m_data + n, b.m_size - n };
            }
            friend constexpr array_view operator+(std::size_t n, array_view b) { return b + n; }
        };
    } // namespace impl

    template <typename T>
    impl::array_view<T> array_view(T* data, std::size_t size)
    {
        return { data, size };
    }
    template <typename T>
    impl::array_view<const T> array_view(const T* data, std::size_t size)
    {
        return { data, size };
    }

    template <typename T, std::size_t Size>
    impl::array_view<T> array_view(T data[Size])
    {
        return { data, Size };
    }
    template <typename T, std::size_t Size>
    impl::array_view<const T> array_view(const T data[Size])
    {
        return { data, Size };
    }
    template <typename T, std::size_t Size>
    impl::array_view<T> array_view(std::array<T, Size>& data)
    {
        return { data.data(), data.size() };
    }
    template <typename T, std::size_t Size>
    impl::array_view<const T> array_view(const std::array<T, Size>& data)
    {
        return { data.data(), data.size() };
    }

    template <typename T>
    impl::array_view<T> array_view(std::vector<T>& data)
    {
        return { data.data(), data.size() };
    }
    template <typename T>
    impl::array_view<const T> array_view(const std::vector<T>& data)
    {
        return { data.data(), data.size() };
    }

    template <typename T>
    impl::array_view<T> array_view(std::basic_string<T>& data)
    {
        return { data.data(), data.size() };
    }
    template <typename T>
    impl::array_view<const T> array_view(const std::basic_string<T>& data)
    {
        return { data.data(), data.size() };
    }

    template <typename T>
    impl::array_view<const T> array_view(std::basic_string_view<T> data)
    {
        return { data.data(), data.size() };
    }
} // namespace html

#endif //!ARRAY_VIEW_HPP
