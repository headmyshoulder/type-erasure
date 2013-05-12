/*
 * condition.h
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef CONDITION_H_INCLUDED
#define CONDITION_H_INCLUDED

#include "memory_model.h"

#include <type_traits>

#include <iostream>

using std::cout;
using std::endl;


template< typename T , typename Concept >
struct eval_impl
{
    static bool eval( const T &t , Concept &c ) { std::cout << "huhu from " << t << " argument is " << c << std::endl; }
};





template< typename MemoryModelTag >
class condition
{
    struct model_getter;
    struct concept;
    
    typedef MemoryModelTag memory_model_tag;
    typedef typename memory_model< memory_model_tag , concept , model_getter >::type memory_model_type;
    typedef condition< memory_model_tag > self_type;
    
    template< class T >
    struct enable_type_move_ctor : public
        std::enable_if< !std::is_same<
                            typename std::remove_cv< typename std::remove_reference< typename std::remove_cv< T >::type >::type >::type ,
                            self_type >::value , void* > { };
                           
    
public:
    
    typedef int context_type;
    

    
    condition( void ) : m_data() { cout << "[condition] ctor " << this << endl; }
    
    condition( const condition &c ) : m_data( c.m_data ) { cout << "[condition] copy ctor " << this << " from " << &c << endl; }
    
    condition( condition &&c ) : m_data( c.m_data ) { cout << "[condition] move ctor " << this << " from " << &c << endl; }
    
    template< typename T >
    explicit condition( const T& t ) : m_data( t ) { cout << "[condition] type ctor " << this << " from " << &t << endl; }
    
    template< typename T >
    explicit condition( T &&t , typename enable_type_move_ctor< T >::type dummy = nullptr ) : m_data( t ) { cout << "[condition] move type ctor " << this << " from " << &t << endl; }
    
    const condition& operator=( const condition &c )
    {
        cout << "[condition] copy " << this << " from " << &c << endl;
        m_data = c.m_data;
        return *this;
    }
    
    template< typename T >
    const condition& operator=( const T &t )
    {
        cout << "[condition] type copy " << this << " from " << &t << endl;
        m_data = t;
        return *this;
    }
     



    bool eval( context_type &c ) { return m_data.model().evaluate( c ); }

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
    
    struct model_getter
    {
        template< class T >
        struct apply { typedef model< T > type; };
    };
    
    

    
    memory_model_type m_data;
};




#endif // CONDITION_H_INCLUDED
