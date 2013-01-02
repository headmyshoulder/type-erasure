/*
 * condition.h
 * Date: 2012-11-27
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef CONDITION_H_INCLUDED
#define CONDITION_H_INCLUDED

#include <memory>
#include <iostream>

template< class T , class Context >
struct eval_impl;



template< class Context >
class condition
{
public:

    typedef Context context_type;

    condition( void )
        : m_data()
    { }

    condition( const condition &c )
        : m_data( c.m_data->clone() )
    { }

    // condition( condition &&c )
    // { }

    template< class C >
    condition( const C &c )
        : m_data( new model< C >( c ) )
    { }

    // template< class C >
    // condition( C &&c )
    // { }

    condition& operator=( const condition &c )
    {
        m_data.reset( c.m_data->clone() );
        return *this;
    }

    // condition& operator=( condition &&c )
    // {
    //     return *this;
    // }

    template< class C >
    condition& operator=( const C &c )
    {
        m_data.reset( new model< C >( c ) );
        return *this;
    }

    // template< class C >
    // condition& operator=( C &&c )
    // {
    //     return *this;
    // }

    bool eval( context_type &c ) { return m_data->evaluate( c ); }

private:

    struct concept
    {
        virtual bool evaluate( context_type &c ) = 0;
        virtual concept* clone( void ) const = 0;
    };

    template< class T >
    struct model : concept
    {
        model( const T &t ) : m_data( t ) { }
        bool evaluate( context_type &c ) { return eval_impl< T , context_type >::eval( m_data , c ); }
        concept* clone( void ) const { return new model< T >( m_data ); }
        T m_data;
    };

    std::unique_ptr< concept > m_data;
};




#endif // CONDITION_H_INCLUDED
