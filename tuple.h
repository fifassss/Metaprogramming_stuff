template<typename... ELEMS>
struct Tuple
{
    constexpr Tuple() = default;
};

template<typename ELEM0,typename... ELEMS1toN>
struct Tuple<ELEM0, ELEMS1toN...> : Tuple<ELEMS1toN...>
{
    explicit constexpr Tuple(ELEM0 e1, ELEMS1toN... rest) : Tuple<ELEMS1toN...>(rest...), data(e1) {}
    ELEM0 data;
};


template<typename... ELEMS>
auto make_tuple(ELEMS... elems)
{
    return Tuple<std::unwrap_ref_decay_t<ELEMS>...>{elems...};
}


// подсказка компилятору,потому что в конструкторе прямо мы это сделать не можем.Но можем подсказать вот так отдельно. Это нужно также что бы для того,что бы мы могли не только делать
// auto tup = make_tuple(8, true, 1.5);
// но и Tuple tup2{1,false,4};

template <typename T,typename... Ts>
Tuple(T e1, Ts... rest) -> Tuple<std::unwrap_ref_decay_t<T>, std::unwrap_ref_decay_t<Ts>...>;