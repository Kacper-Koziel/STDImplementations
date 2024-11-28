#ifndef PAIR_H
#define PAIR_H
    #include <iostream>

    template <typename F, typename S>
    struct Pair
    {
        F first;
        S second;


        Pair(F&& first, S&& second);
        Pair(const Pair<F, S>& other);
        Pair(Pair<F, S>&& other) noexcept;

        void swap(Pair<F, S>& other);

        Pair<F, S>& operator=(const Pair<F, S>& other);
        Pair<F, S>& operator=(Pair<F, S>&& other) noexcept;

        bool operator==(const Pair<F, S>& other);
        bool operator!=(const Pair<F, S>& other);

        bool operator<(const Pair<F, S>& other);
        bool operator>(const Pair<F, S>& other);

        bool operator<=(const Pair<F, S>& other);
        bool operator>=(const Pair<F, S>& other);
    };

    template <typename F, typename S>
    Pair<F, S> make_pair(F&& first, S&& second)
    {
        return Pair<F, S>(std::forward<F>(first), std::forward<S>(second)); //perfect forwarding r-v = r-v, l-v = l-v
    }
#endif
