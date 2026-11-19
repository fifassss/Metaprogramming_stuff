template<size_t n>
struct fibonnachi
{
    static_assert(n <= 93,"N have to be n <= 93");
    static constexpr size_t value = fibonnachi<n - 2>::value + fibonnachi<n - 1>::value;
};

template<>
struct fibonnachi<0>
{
    static constexpr size_t value = 0;
};

template<>
struct fibonnachi<1>
{
    static constexpr size_t value = 1;
};
