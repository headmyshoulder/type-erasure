/*
 * remove_rcv.h
 * Date: 2013-06-26
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef REMOVE_RCV_H_INCLUDED
#define REMOVE_RCV_H_INCLUDED

#include <type_traits>

template< typename Args >
struct remove_rcv : std::remove_reference< typename std::remove_cv< Args >::type > { };

#endif // REMOVE_RCV_H_INCLUDED
