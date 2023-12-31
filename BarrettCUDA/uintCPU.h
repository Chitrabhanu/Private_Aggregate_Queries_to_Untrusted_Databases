#ifndef __UINT_H__
#define __UINT_H__

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

#define BITS_PER_LIMB	(sizeof(uint) * 8)
#define BITS_IN(limbs)	((limbs) * BITS_PER_LIMB)

typedef unsigned int uint;
typedef uint  uint32;
typedef uint uint64;
typedef uint uint96;
typedef uint uint128;

template <typename T>
struct uintXp
{
    T lo;
    uint hi;
};

template <typename T>
static inline NTL::ZZ to_ZZ(const T & n)
{
    //std::cout<<"to_ZZ inside uint.h"<<"\n";
    //std::cout<<sizeof(T)<<"\n";
    return NTL::ZZFromBytes((unsigned char *)&n, sizeof(T));
}

template <typename T>
static inline T & to_uint(const NTL::ZZ & n, T & ret)
{
    NTL::BytesFromZZ((unsigned char *)&ret, n, sizeof(T));
    return ret;
}

template <typename T>
static inline T & to_uint(const NTL::ZZ_p & n, T & ret)
{
    NTL::BytesFromZZ((unsigned char *)&ret, rep(n), sizeof(T));
    return ret;
}

template <typename T>
static inline NTL::ZZ_p to_ZZ_p(const T & n)
{
    return NTL::to_ZZ_p(to_ZZ(n));
}

template <typename T>
static inline void print(const T & n)
{
    std::cout << to_ZZ<T>(n);
}

template <typename T>
static inline void print_limbs(const T & n, const uint limbs)
{
    if (!limbs) return;
    const uint * _n = (uint *)&n;
    std::cout << _n[0];
    for (int i = 1; i < limbs; ++i) std::cout << "." << _n[i];
	std::cout<<"\n";
}

template <typename T>
static inline void print_limbs(const NTL::ZZ & n, const uint limbs)
{
    T ret;
    print_limbs(to_uint(n, ret), limbs);
}

template <typename T>
static inline void print_limbs(const NTL::ZZ_p & n, const uint limbs)
{
    T ret;
    print_limbs(to_uint(n, ret), limbs);
}

template <typename T>
static inline void _print_limbs(const T & n, const uint limbs)
{
    if (!limbs) return;
    const uint * _n = (uint *)&n;
    printf("%u", _n[0]);
    for (int i = 1; i < limbs; ++i) printf(".%u", _n[i]);
	printf("\n");
}

#endif
