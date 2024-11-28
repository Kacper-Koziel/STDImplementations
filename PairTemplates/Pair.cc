#pragma once

#include "Pair.h"

template <typename F, typename S>
Pair<F, S>::Pair(F&& first, S&& second) : first(std::forward<F>(first)), second(std::forward<S>(second))
{

}

template <typename F, typename S>
Pair<F, S>::Pair(const Pair<F, S>& other)
{
    this->first = other.first;
    this->second = other.second;
}

template <typename F, typename S>
Pair<F, S>::Pair(Pair<F, S> &&other) noexcept
{
    this->first = std::move(other.first);
    this->second = std::move(other.second);
}

template <typename F, typename S>
void Pair<F, S>::swap(Pair<F, S> &other)
{
    std::swap(this->first, other.first);
    std::swap(this->second, other.second);
}

template <typename F, typename S>
Pair<F, S> &Pair<F, S>::operator=(const Pair<F, S> &other)
{
    if (this == &other)
    {
        return *this;
    }
    
    this->first = other.first;
    this->second = other.second;

    return *this;
}

template <typename F, typename S>
Pair<F, S> &Pair<F, S>::operator=(Pair<F, S> &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    this->first = std::move(other.first);
    this->second = std::move(other.second);
    
    return *this;
}

template <typename F, typename S>
bool Pair<F, S>::operator==(const Pair<F, S>& other)
{
    return this->first == other.first && this->second == other.second;
}

template <typename F, typename S>
bool Pair<F, S>::operator!=(const Pair<F, S> &other)
{
    return !(*this == other);
}

template <typename F, typename S>
bool Pair<F, S>::operator<(const Pair<F, S> &other)
{
    return (this->first < other.first) || (this->first == other.first && this->second < other.second);
}

template <typename F, typename S>
bool Pair<F, S>::operator>(const Pair<F, S> &other)
{
    return (this->first > other.first) || (this->first == other.first && this->second > other.second);
}

template <typename F, typename S>
bool Pair<F, S>::operator<=(const Pair<F, S> &other)
{
    return (this->first < other.first) || (this->first == other.first && this->second <= other.second);
}

template <typename F, typename S>
bool Pair<F, S>::operator>=(const Pair<F, S> &other)
{
    return (this->first > other.first) || (this->first == other.first && this->second >= other.second);
}

template <typename F, typename S>
void Pair<F, S>::operator<<()
{
}
