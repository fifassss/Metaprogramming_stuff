// + добавили везде поддержку идеальной передачи.
// нужно подключить type_list.hpp или .h

template<typename... ELEMS>
struct Tuple
{
    constexpr Tuple() = default;
};

template<typename ELEM0, typename... ELEMS1toN>
struct Tuple<ELEM0, ELEMS1toN...> : Tuple<ELEMS1toN...>
{
    template<typename T,typename...Ts>
    explicit constexpr Tuple(T&& e1, Ts&&... rest) : Tuple<ELEMS1toN...>(std::forward<Ts>(rest)...), data(std::forward<T>(e1)) {}
    ELEM0 data;
};

// подсказка компилятору,потому что в конструкторе прямо мы это сделать не можем.Но можем подсказать вот так отдельно. Это нужно также что бы для того,что бы мы могли не только делать
// auto tup = make_tuple(8, true, 1.5);
// но и Tuple tup2{1,false,4};

template <typename T, typename... Ts>
Tuple(T e1, Ts... rest) -> Tuple<std::unwrap_ref_decay_t<T>, std::unwrap_ref_decay_t<Ts>...>;

template<typename... ELEMS>
constexpr auto make_tuple(ELEMS&&... elems)
{
    return Tuple<std::unwrap_ref_decay_t<ELEMS>...>{std::forward<ELEMS>(elems)...};
}


namespace detail
{
    template<size_t i, typename TUPLE>
    struct get_impl : get_impl<i - 1, pop_front_t<TUPLE>> {}; // рекурсивно идем до интересующего нас типа

    template<typename TUPLE>
    struct get_impl<0, TUPLE> // специализация когда остался в списке один тип,и в этой специализации с помощью функции значение даем
    {
        template<typename T>
        constexpr static decltype(auto) get(T&& t)
        {
            constexpr bool is_lvalue = std::is_lvalue_reference_v<T>; // что бы учитывались ссылки
            constexpr bool is_const = std::is_const_v<std::remove_reference_t<T>>; // что бы учитывалась константность.

            using data_t = front_t<TUPLE>; // для того что бы мы могли менять прям содержимое get<2> = 5,а было к примеру 4.

            if constexpr (is_lvalue && is_const)
            {
                return static_cast<const data_t&>(static_cast<const TUPLE&>(t).data);
            }
            if constexpr (is_lvalue && !is_const)
            {
                return static_cast<data_t&>(static_cast<TUPLE&>(t).data);
            }
            if constexpr (!is_lvalue && is_const)
            {
                return static_cast<const data_t&&>(static_cast<const TUPLE&&>(t).data);
            }
            if constexpr (!is_lvalue && !is_const)
            {
                return static_cast<data_t&&>(static_cast<TUPLE&&>(t).data); //static_cast<data_t&&> нужно как я и говорил для того что мы могли  get<2> = 5,а было к примеру 4.
                // а изначально вообще просто было static_cast<TUPLE&>(t).data;
            }

        }
    };
}

template<size_t i, typename TUPLE>
constexpr decltype(auto) get(TUPLE&& tuple) // передаем индекс + сам кортеж в структуру,где оно рекурсивно ищет тип,а потом вызывает функцию которую с помощью кастов возращает тип
{
    return detail::get_impl<i, std::remove_cvref_t<TUPLE>>::get(std::forward<TUPLE>(tuple));
}
