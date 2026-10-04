template<long long int n>
struct factorial
{
    static constexpr long long int value = n * factorial<n-1>::value; // n how parametrs function accept,in <...>,late we n * 'function' with paramets <n-1> late call value,with help '::' and then n * value,with paramets 'func' n-1
};

template<>
struct factorial<0>
{
    static constexpr long long int value{ 1 };
}; // spec for base-case
