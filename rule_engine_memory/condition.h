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
    
    template< class T >
    struct enable_type_move_ctor : public
        std::enable_if< !std::is_same<
                            typename std::remove_reference< typename std::remove_cv< T >::type >::type ,
                            self_type >::value , void* > { };
                           
    
public:
    
    typedef int context_type;

    template< typename T >
    static void test_type_move_ctor( T &&t )
    {
        cout << !std::is_same< typename std::remove_reference< typename std::remove_cv< T >::type >::type , self_type >::value << "\t";
        cout << typeid( T ).name() << endl;
    }
    

    
    condition( void ) : m_data() { cout << "[condition] ctor " << this << endl; }
    
    condition( const condition &c ) : m_data( c.m_data ) { cout << "[condition] copy ctor " << this << " from " << &c << endl; }
    
    condition( condition &&c ) : m_data( c.m_data ) { cout << "[condition] move ctor " << this << " from " << &c << endl; }
    
    template< typename T >
    explicit condition( T &&t , typename enable_type_move_ctor< T >::type dummy = nullptr ) : m_data( std::forward< T >( t ) ) { cout << "[condition] move type ctor " << this << " from " << &t << endl; }

    ~condition( void ) { cout << "[condition] dtor " << this << endl; }
    
    const condition& operator=( const condition &c )
    {
        cout << "[condition] copy " << this << " from " << &c << endl;
        m_data = c.m_data;
        return *this;
    }

    const condition& operator=( condition &&c )
    {
        cout << "[condition] move " << this << " from " << &c << endl;
        m_data = c.m_data;
        return *this;
    }
    
//     template< typename T >
//     const condition& operator=( T &&t )
//     {
//         cout << "[condition] universal type move " << this << " from " << &t << endl;
//         m_data = std::forward< T >( t );
//         return *this;
//     }
     



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
            cout << "[model] : move type ctor " << this << " from " << &u << std::endl;
//             cout << "[model] : type of T = " << typeid( T ).name() << endl;
//             cout << "[model] : type of U = " << typeid( U ).name() << endl;
//             cout << "[model] : lvref(T) = " << std::is_reference< T >::value << " , rvref(T) = " << std::is_rvalue_reference< T >::value << std::endl;
//             cout << "[model] : lvref(U) = " << std::is_reference< U >::value << " , rvref(U) = " << std::is_rvalue_reference< U >::value << std::endl;
//             typedef decltype( std::forward< U >( u ) ) xyz_type;
//             cout << "[model] ref(XYZ) : " << std::is_reference< xyz_type >::value << " " << std::is_rvalue_reference< xyz_type >::value << endl;

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
