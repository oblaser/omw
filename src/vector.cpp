/*
author          Oliver Blaser
date            25.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <cstddef>
#include <cstdint>
#include <vector>

#include "omw/vector.h"

namespace
{
}



/*!
* \class omw::vector
*
* A with `std::vector` interchangeable class to add more functionalities.
* This class does not override/implement any (virtual) methods of the base class and has no attributes. It's basically a `std::vector` with some more methods.
*/

/*!
* \fn omw::vector<T, Allocator>::reserveAdd(size_type addCap)
* 
* Reserves additional memory.
* 
* `this->reserve(this->size() + addCap)`
* 
* See <tt><a href="https://en.cppreference.com/w/cpp/container/vector/reserve" target="_blank">std::vector<T,Allocator>::reserve</a></tt>
* and <tt><a href="https://en.cppreference.com/w/cpp/container/vector/size" target="_blank">std::vector<T,Allocator>::size</a></tt>.
*/
