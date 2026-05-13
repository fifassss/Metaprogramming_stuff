// statemate if in metaprogramming
template<bool condition,typename THEN,typename ELSE>
struct if_;

template<typename THEN,typename ELSE>
struct if_<true, THEN, ELSE>
{
    using Type = THEN;
};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE>
{
    using Type = ELSE;
};
