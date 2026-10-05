template<long long int n>
struct factorial
{
    static_assert(n >= 0,"N have to be non-negative number"); // check n - number non-negative
    static_assert(n <= 20, "N have to be n <= 20"); // check n - number n <= 20
    static constexpr long long int value = n * factorial<n-1>::value; // n how parametrs function accept,in <...>,late we n * 'function' with paramets <n-1> late call value,with help '::' and then n * value,with paramets 'func' n-1
};

template<>
struct factorial<0>
{
    static constexpr long long int value{ 1 };
}; // spec for base-case
