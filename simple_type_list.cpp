template<typename T> // прослойка что бы вытягивать типы
struct has_type
{
    using type = T;
};


// if meta
template<bool condition, typename THEN, typename ELSE>
struct if_;

template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> : has_type<THEN> {};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> : has_type<ELSE> {};

// if meta


// thats it type_list
template<typename...> 
struct type_list {};

// thats it type_list



// empty

template<typename LIST> // general empty
struct empty : std::false_type {};

template<template<typename...> class LIST> // spec-null empty
struct empty<LIST<>> : std::true_type {};

template<typename LIST>
static constexpr bool is_empty_v = empty<LIST>::value; // alias

// empty



// front


template<typename LIST> // general front
struct front;

template<template<typename...> class LIST,typename T0, typename... TonK> // spec front
struct front<LIST<T0, TonK...>> : has_type<T0> {};

template<typename LIST>
using front_t = typename front<LIST>::type; // alias

// front


// pop_front

template<typename LIST> // general pop_front
struct pop_front;

template <template <typename...> class LIST, typename T0, typename... T1toN>
struct pop_front<LIST<T0, T1toN...>> : has_type<LIST<T1toN...>> {};

template<typename LIST>
using pop_front_t = typename pop_front<LIST>::type; // alias

// pop_front



// back
template<typename LIST> // рекурсия
struct back : has_type<typename back<pop_front_t<LIST>>::type> {};

template<template<typename...> class LIST, typename T0> // если один элемент в списке
struct back<LIST<T0>> : has_type<T0> {};

template<typename LIST>
using back_t = typename back<LIST>::type;

// back


// push_back
template <typename LIST, typename T>
struct push_back;

template <template <typename...> class LIST, typename... T0toN, typename T>
struct push_back<LIST<T0toN...>, T> : has_type<LIST<T0toN..., T>> {}; // тут логика такая,изначально мы пишем структуру которая принимает структуру данных,и то что хотим добавить
// после в наследовании мы с помощью has_type невзначай намекаем что хотим что бы наш тип был ну...в листе)

template <typename LIST, typename T>
using push_back_t = typename push_back<LIST, T>::type;


// push_back


// pop_back

template <typename LIST, typename RET_LIST = type_list<>>
struct pop_back;

template <template <typename...> class LIST, typename T0, typename RET_LIST>
struct pop_back<LIST<T0>, RET_LIST> : has_type<RET_LIST> {};

template <template <typename...> class LIST, typename T0, typename T1, typename... T2toN, typename RET_LIST>
struct pop_back<LIST<T0, T1, T2toN...>, RET_LIST> : pop_back<LIST<T1, T2toN...>, push_back_t<RET_LIST, T0>> {};

template <typename LIST>
using pop_back_t = typename pop_back<LIST>::type;

// pop_back




// at
template<typename LIST, size_t index> // рекурсия
struct at : has_type<typename at<pop_front_t<LIST>, index - 1>::type> {};

template<typename LIST> // для одного элемента в списке
struct at<LIST, 0> : has_type<front_t<LIST>> {};

template<typename LIST, size_t index>
using at_t = typename at<LIST, index>::type;


// at



// any

template <template <typename> class PREDICATE, typename LIST>
struct any;

template <template <typename> class PREDICATE, template <typename...> class LIST>
struct any<PREDICATE, LIST<>> : std::false_type {};

template <template <typename> class PREDICATE, typename LIST>
struct any : if_<  // if predicate matches first type
    PREDICATE<front_t<LIST>>::value,
    // then
    std::true_type,
    // else
    typename any<PREDICATE, pop_front_t<LIST>>::type
               >::type {};

template <template <typename> class PREDICATE, typename LIST>
static constexpr bool any_v = any<PREDICATE, LIST>::value;

static_assert(any_v<std::is_integral, type_list<int, double, std::string>>);

// any



// contains_type

template<typename T>
struct same_as_pred
{
    template<typename U>
    struct predicate : std::is_same<T,U>{};
};

template<typename SEARCH,typename LIST>
static constexpr bool contains_type_v = any<same_as_pred<SEARCH>::template predicate, LIST>::value;

static_assert(contains_type_v<int, type_list<int, bool, float>>);
static_assert(contains_type_v<double, type_list<int, bool, float>> == false);

// contains_type
