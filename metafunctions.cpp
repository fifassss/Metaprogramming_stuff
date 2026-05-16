// my own metafunctions



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
