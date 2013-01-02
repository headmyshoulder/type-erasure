/*
 * condition_factory.h
 * Date: 2012-11-27
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef CONDITION_FACTORY_H_INCLUDED
#define CONDITION_FACTORY_H_INCLUDED

#include "condition.h"
#include "generic_conditions.h"

#include <functional>

template< class Context >
struct condition_factory
{
    typedef Context context_type;
    typedef condition< context_type > condition_type;

    std::function< condition_type( void ) > true_factory;
    std::function< condition_type( void ) > false_factory;
    std::function< condition_type( condition_type ) > not_factory;
    std::function< condition_type( condition_type , condition_type ) > and_factory;
    std::function< condition_type( condition_type , condition_type ) > or_factory;
};

template< class Context >
condition_factory< Context > make_simple_condition_factory( void )
{
    typedef condition< Context > condition_type;

    condition_factory< Context > f;
    f.true_factory = []( void ) {
        return condition_type( true ); };
    f.false_factory = []( void ) {
        return condition_type( false ); };
    f.not_factory = []( condition_type c ) {
        return make_not_condition( c ); };
    f.and_factory = []( condition_type l , condition_type r ) {
        return make_and_condition( l , r  ); };
    f.or_factory = []( condition_type l , condition_type r ) {
        return make_and_condition( l , r  ); };
    return f;
}

template< class Context >
condition_factory< Context > make_logging_condition_factory( void )
{
    typedef condition< Context > condition_type;

    condition_factory< Context > f;
    f.true_factory = []( void ) {
        return make_logging_condition< Context >( "True" , true ); };
    f.false_factory = []( void ) {
        return make_logging_condition< Context >( "False" , false ); };
    f.not_factory = []( condition_type c ) {
        return make_logging_condition< Context >( "Not" , make_not_condition( c ) ); };
    f.and_factory = []( condition_type l , condition_type r ) {
        return make_logging_condition< Context >( "And" , make_and_condition( l , r  ) ); };
    f.or_factory = []( condition_type l , condition_type r ) {
        return make_logging_condition< Context >( "Or" , make_and_condition( l , r  ) ) ; };
    return f;
}


#endif // CONDITION_FACTORY_H_INCLUDED
