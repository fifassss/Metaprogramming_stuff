template<typename T>
struct has_type
{
	using type = T;
};

template<typename...> // thats it type_list
struct type_list {};

template<typename LIST> // general empty
struct empty : std::false_type {};

template<> // spec-null empty
struct empty<type_list<>> : std::true_type {};

template<typename LIST> // general front
struct front;

template<typename T0,typename... TonK> // spec front
struct front<type_list<T0,TonK...>>
{
	using Type = T0;
};

template<typename LIST> // general pop_front
struct pop_front;

template<typename T0,typename... TonK> // spec pop_front
struct pop_front<type_list<T0, TonK...>>
{
	using Type = type_list<TonK...>;
};

template<typename LIST>
static constexpr bool is_empty_v = empty<LIST>::value; // alias

template<typename LIST>
using front_t = typename front<LIST>::Type; // alias

template<typename LIST>
using pop_front_t = typename pop_front<LIST>::Type; // alias

// at

template<typename LIST,size_t index> // рекурсия
struct at : has_type<typename at<pop_front_t<LIST>,index-1>::type> {};

template<typename LIST> // для первого элемента
struct at<LIST,0> : has_type<front_t<LIST>> {};

template<typename LIST,size_t index>
using at_t = typename at<LIST, index>::type;

// at

// back

template<typename LIST> // рекурсия
struct back : has_type<typename back<pop_front_t<LIST>>::type> {};

template<typename T0> // для первого элемента
struct back<type_list<T0>> : has_type<T0> {};

template<typename LIST>
using back_t = typename back<LIST>::type;

