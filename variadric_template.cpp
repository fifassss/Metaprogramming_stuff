template<typename LAST>
void printn(LAST t)
{
    std::cout << t << '\n';
}

template<typename T0,typename... T1oN> // typename... T1oN - front name : значения элементов(имена типов)
void printn(T0 t,T1oN... rest) // (T0 t,T1oN... rest) - between names : определение второго имени как листа параметров,который дает первый
{
	std::cout << t << '\n';
	printn(rest...); // printn(rest...); - after name : расширяет имя в лист из всех элементов представления
}
