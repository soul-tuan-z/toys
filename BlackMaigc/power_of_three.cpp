/*
 * 计算3的整数次幂中，不大与N的，最大的那个。
 * 如 N ＝ 10 时，值为9，N ＝ 19 时，值为 18，以此类推
 *
 * */

#include <iostream>
#include <climits>
using namespace std;

template <bool, typename, typename>
struct _IF {
};

template <typename _if, typename _else>
struct _IF<true, _if, _else> {
    typedef _if retType;
};

template <typename _if, typename _else>
struct _IF<false, _if, _else> {
    typedef _else retType;
};

template<template<typename> class Cond, typename stat>
struct _WHILE {
    template<typename st>
    struct STOP {
        typedef st retType;
    };
    typedef
    typename _IF<Cond<stat>::val, _WHILE<Cond, typename stat::NEXT>,
    STOP<stat>>::retType::retType
    retType;
};

template<int power>
struct power_of_three { 
	enum { val = (power_of_three<power - 1>::val * 3 / 3) == power_of_three<power - 1>::val ? power_of_three<power - 1>::val * 3 : 0 }; 
};
template<>
struct power_of_three<0> { enum { val = 1 }; };


template<int bound>
struct max_power {
    template<int p>
    class stat {
    public:
        typedef stat<p + 1> NEXT;
        enum { val = power_of_three<p>::val, power = p };
    };

    template<typename stat>
    struct cond {
        enum { val = power_of_three<stat::power + 1>::val < bound && power_of_three<stat::power + 1>::val != 0};
    };

    typedef typename _WHILE<cond, stat<0>>::retType retType;
	enum { val = retType::val };
};


int  main() {
	cout << max_power<INT_MAX>::val << endl;
	cout << max_power<19>::val << endl;
	return 0;
}
