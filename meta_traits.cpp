// my own type_traits

template<typename T,typename U>
struct is_samess : std::false_type {};

template<typename T>
struct is_samess<T,T> : std::true_type {};


template<typename T>
struct delets_ref
{
    using Type = T;
};


template<typename T>
struct delets_ref<T&>
{
    using Type = T;
};


template<typename T>
struct delets_ref<T&&>
{
    using Type = T;
};

template<typename T>
struct deletess_poiner
{
    using Type = T;
};

template<typename T>
struct deletess_poiner<T*>
{
    using Type = T;
};
