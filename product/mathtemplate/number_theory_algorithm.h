#ifndef NUMBER_THEORY_ALGORITHM_H
#define NUMBER_THEORY_ALGORITHM_H

#include <stddef.h>
#include <stdio.h>

template <class Z>
Z extended_euclidean(Z a, Z b, Z &x, Z &y)
{
    Z d;
    Z zero;
    zero = 0;
    if (b == zero)
    {
        x = 1;
        y = 0;
        // printf("xy\n");
        // x.print();printf("\n");
        // y.print();printf("\n");
        return a;
    }
    d = extended_euclidean(b, a % b, y, x);
    // x.print();printf("1\n");
    // y.print();printf("2\n");
    //((a / b)).print();printf("2.4\n");
    y = y - ((a / b) * x);
    // printf("xy\n");
    // x.print();printf("3\n");
    // y.print();printf("4\n");
    return d;
}

template <class G>
G fast_power(G a, size_t b)
{
    G ans;
    ans = 1;
    G res = a;
    while (b)
    {
        if (b % 2 == 1)
        {
            ans = ans * a;
        }
        a = a * a;
        b = b / 2;
    }
    return ans;
}

template <class A>
A fast_addition(A a, size_t b)
{
    A ans;
    ans = 0;
    A res = a;
    while (b)
    {
        if (b % 2 == 1)
        {
            ans = ans + a;
        }
        a = a + a;
        b = b / 2;
    }
    return ans;
}
#endif
