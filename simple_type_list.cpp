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
