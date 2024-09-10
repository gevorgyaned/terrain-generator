#ifndef USING_HPP
#define USING_HPP

#include <memory>

template <typename T>
using UP = std::unique_ptr<T>;

template <typename T>
using SP = std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

#endif /* USING_HPP */

