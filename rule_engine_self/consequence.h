/*
 * consequence.h
 * Date: 2012-11-27
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef CONSEQUENCE_H_INCLUDED
#define CONSEQUENCE_H_INCLUDED

#include <memory>


template< class T , class Context >
struct run_impl;



template< class Context >
class consequence
{
public:

    typedef Context context_type;

    consequence( void )
        : m_data()
    { }

    consequence( const consequence &c )
        : m_data( c.m_data->clone() )
    { }

    // consequence( consequence &&c )
    // { }

    template< class C >
    consequence( const C &c )
        : m_data( new model< C >( c ) )
    { }

    // template< class C >
    // consequence( C &&c )
    // { }

    consequence& operator=( const consequence &c )
    {
        m_data.reset( c.m_data->clone() );
        return *this;
    }

    // consequence& operator=( consequence &&c )
    // {
    //     return *this;
    // }

    template< class C >
    consequence& operator=( const C &c )
    {
        m_data.reset( new model< C >( c ) );
        return *this;
    }

    // template< class C >
    // consequence& operator=( C &&c )
    // {
    //     return *this;
    // }

    void run( context_type &c ) { return m_data->run( c ); }

private:

    struct concept
    {
        virtual void run( context_type &c ) = 0;
        virtual concept* clone( void ) const = 0;
    };

    template< class T >
    struct model : concept
    {
        model( const T &t ) : m_data( t ) { }
        void run( context_type &c ) { run_impl< T , context_type >::run( m_data , c ); }
        concept* clone( void ) const { return new model< T >( m_data ); }
        T m_data;
    };

    std::unique_ptr< concept > m_data;
};


#endif // CONSEQUENCE_H_INCLUDED
