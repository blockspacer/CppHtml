#ifndef ARRAY_VIEW_HPP
#define ARRAY_VIEW_HPP

#include <algorithm>
#include <iterator>

namespace html
{
    class char_array_view
    {
    private:
        const char* m_data;
        std::size_t m_size;

    public:
        using value_type = char;
        using reference = value_type&;
        using const_reference = const value_type&;
        using const_pointer = const value_type*;
        using const_iterator = const_pointer;

        static constexpr std::size_t npos = static_cast<std::size_t>(-1);

        constexpr char_array_view() noexcept : char_array_view(nullptr, 0) {}
        constexpr char_array_view(const char* data, std::size_t size) noexcept : m_data(data), m_size(size) {}

        constexpr bool empty() const noexcept { return !m_size; }
        constexpr std::size_t size() const noexcept { return m_size; }

        constexpr const_pointer data() const noexcept { return m_data; }
        constexpr const_reference operator[](std::size_t index) const { return m_data[index]; }

        constexpr const_reference front() const { return *m_data; }
        constexpr const_reference back() const { return m_data[m_size - 1]; }

        constexpr const_iterator begin() const noexcept { return m_data; }
        constexpr const_iterator cbegin() const noexcept { return m_data; }
        constexpr const_iterator end() const noexcept { return m_data + m_size; }
        constexpr const_iterator cend() const noexcept { return m_data + m_size; }

        constexpr std::size_t find(const char& value) const noexcept
        {
            for (std::size_t i = 0; i < m_size; i++)
            {
                if (m_data[i] == value) return i;
            }
            return npos;
        }
        constexpr std::size_t find(std::initializer_list<char> values) const noexcept
        {
            for (std::size_t i = 0; i < m_size; i++)
            {
                for (const char value : values)
                {
                    if (m_data[i] == value) return i;
                }
            }
            return npos;
        }

        constexpr char_array_view& operator+=(std::size_t n)
        {
            n = std::min(n, m_size);
            m_size -= n;
            m_data += n;
            return *this;
        }
        constexpr char_array_view& operator++()
        {
            if (m_size > 0)
            {
                m_data++;
                m_size--;
            }
            return *this;
        }
        constexpr char_array_view operator++(int)
        {
            char_array_view result = *this;
            operator++();
            return result;
        }

        friend constexpr char_array_view operator+(char_array_view b, std::size_t n)
        {
            n = std::min(n, b.m_size);
            return char_array_view(b.m_data + n, b.m_size - n);
        }
        friend constexpr char_array_view operator+(std::size_t n, char_array_view b) { return b + n; }
    };
} // namespace html

#endif //!ARRAY_VIEW_HPP