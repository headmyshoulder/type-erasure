/*
 * condition.h
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef CONDITION_H_INCLUDED
#define CONDITION_H_INCLUDED

#include "memory_model.h"
#include "enable_move_type.h"

#include <type_traits>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;



template< typename T , typename Concept >
struct eval_impl
{
    static bool eval( const T &t , Concept &c ) { std::cout << "[HUHUHUHU] from " << t << " argument is " << c << std::endl; }
};





template< typename MemoryModelTag >
class condition
{
public:
    
    struct model_getter;
    struct concept;
    
    typedef MemoryModelTag memory_model_tag;
    typedef typename memory_model< memory_model_tag , concept , model_getter >::type memory_model_type;
    typedef condition< memory_model_tag > self_type;
    
//     template< typename Args >
//     struct remove_rcv : std::remove_reference< typename std::remove_cv< Args >::type > { };
//     
//     template< typename Args , typename T >
//     struct enable_move_type : std::enable_if< !std::is_same< typename remove_rcv< Args >::type , self_type >::value , T > { };
//     
//     template< typename Args >
//     struct enable_move_type_ctor : enable_move_type< Args , int* > { };
//     
//     template< typename Args >
//     struct enable_move_type_assignment : enable_move_type< Args , self_type& > { };

    

public:
    
    typedef int context_type;

    
    condition( void )
    : m_data()
    {
#if DEBUG_CONDITION
        cout << "[condition] ctor " << this << endl;
#endif
        
    }
    
    condition( const condition &c )
    : m_data( c.m_data )
    {
#if DEBUG_CONDITION
        cout << "[condition] copy ctor " << this << " from " << &c << endl;
#endif
    }
    
    condition( condition &&c )
    : m_data( c.m_data )
    {
#if DEBUG_CONDITION
        cout << "[condition] move ctor " << this << " from " << &c << endl;
#endif
    }
    
    template< typename T , typename Enable = typename enable_move_type< T , self_type >::type >
    explicit condition( T &&t )
    : m_data( std::forward< T >( t ) )
    {
#if DEBUG_CONDITION
        cout << "[condition] move type ctor " << this << " from " << &t << endl;
#endif
    }

    ~condition( void )
    {
#if DEBUG_CONDITION
        cout << "[condition] dtor " << this << endl;
#endif
    }
    
    
    
    condition& operator=( const condition &c )
    {
#if DEBUG_CONDITION
        cout << "[condition] copy " << this << " from " << &c << endl;
#endif
        m_data = c.m_data;
        return *this;
    }

    condition& operator=( condition &&c )
    {
#if DEBUG_CONDITION
        cout << "[condition] move " << this << " from " << &c << endl;
#endif
        m_data = std::move( c.m_data );
        return *this;
    }
    
    template< typename T , typename Enable = typename enable_move_type< T , self_type >::type >
    condition& operator=( T &&t )
    {
#if DEBUG_CONDITION
        cout << "[condition] universal type move " << this << " from " << &t << endl;
#endif
        m_data = std::forward< T >( t );
        return *this;
    }
     



    bool eval( context_type &c ) { return m_data.model().evaluate( c ); }

// private:

    struct concept
    {
        virtual bool evaluate( context_type &c ) = 0;
        virtual concept* clone( void ) const = 0;
    };

    template< class T >
    struct model : public concept
    {
        model( void ) = delete;
        model( model const& ) = delete;
        
        template< class U >
        model( U &&u ) : m_data( std::forward< U >( u ) )
        {
#if DEBUG_CONDITION
            cout << "[model] : move type ctor " << this << " from " << &u << std::endl;
#endif
        }
        bool evaluate( context_type &c ) { return eval_impl< T , context_type >::eval( m_data , c ); }
        concept* clone( void ) const { return new model< T >( m_data ); }
        T m_data;
    };
    
    struct model_getter
    {
        template< class T >
        struct apply { typedef model< typename std::remove_reference< typename std::remove_cv< T >::type >::type > type; };
    };
    
    

    
    memory_model_type m_data;
};




#endif // CONDITION_H_INCLUDED
