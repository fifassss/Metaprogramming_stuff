// type traits

template<typename T,typename U>
struct is_samess : std::false_type {};

template<typename T>
struct is_samess<T,T> : std::true_type {};

template<typename T>
struct is_pointer : std::false_type {};

template<typename T>
struct is_pointer<T*> : std::true_type{};

template<typename T>
struct is_ref : std::false_type {};

template<typename T>
struct is_ref<T&> : std::true_type {};

template<typename T>
struct is_ref<T&&> : std::true_type {};

template<typename T>
struct is_lvalue_ref : std::false_type {};

template<typename T>
struct is_lvalue_ref<T&> : std::true_type{};

template<typename T>
struct is_rvalue_ref : std::false_type {};

template<typename T>
struct is_rvalue_ref<T&&> : std::true_type {};
