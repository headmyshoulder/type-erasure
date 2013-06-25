/*
 * enable_move_type.h
 * Date: 2013-06-26
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef ENABLE_MOVE_TYPE_H_INCLUDED
#define ENABLE_MOVE_TYPE_H_INCLUDED

#include "remove_rcv.h"

template< typename Args , typename Self >
struct enable_move_type : std::enable_if< !std::is_same< typename remove_rcv< Args >::type , Self >::value , void > { };

#endif // ENABLE_MOVE_TYPE_H_INCLUDED
