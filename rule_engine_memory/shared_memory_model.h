/*
 * shared_memory_model.h
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef SHARED_MEMORY_MODEL_H_INCLUDED
#define SHARED_MEMORY_MODEL_H_INCLUDED

#include "memory_model.h"
#include "enable_move_type.h"

#include <memory>
#include <type_traits>

#if DEBUG_SHARED_MEMORY_MODEL

#include <iostream>

using std::cout;
using std::endl;

#endif 

struct shared_memory_model_tag {};

template< typename Concept , typename Model >
struct shared_memory_model
{
    typedef Concept concept_type;
    typedef Model model_type;
    typedef shared_memory_model< concept_type , model_type > self_type;
    
    template< typename T >
    struct get_model
    {
        typedef typename std::remove_cv< typename std::remove_reference< typename model_type::template apply< T >::type >::type >::type type;
    };
    
    shared_memory_model( void )
    : m_data()
    {
#if DEBUG_SHARED_MEMORY_MODEL
        cout << "[shared_memory_model] : ctor " << this << endl;
#endif
    };
    
    shared_memory_model( const self_type &m ) : m_data( m.m_data )
    {
#if DEBUG_SHARED_MEMORY_MODEL
        cout << "[shared_memory_model] : copy ctor " << this << " from " << &m << endl;
#endif
    }

    shared_memory_model( self_type &&m ) : m_data( m.m_data )
    {
#if DEBUG_SHARED_MEMORY_MODEL
        cout << "[shared_memory_model] : move ctor " << this << " from " << &m << endl;
#endif
    }

    template< typename T , typename Enabler = typename enable_move_type< T , self_type >::type >
    explicit shared_memory_model( T &&t )
    : m_data( std::make_shared< typename get_model< T >::type >( std::forward< T >( t ) ) )
    {
#if DEBUG_SHARED_MEMORY_MODEL        
        cout << "[shared_memory_model] : move type ctor " << this << " from " << &t << endl;
#endif        
    }
    
    ~shared_memory_model( void )
    {
#if DEBUG_SHARED_MEMORY_MODEL
        cout << "[shared_memory_model] : dtor " << this << endl;
#endif
    }
    
    
    self_type& operator=( const self_type &m )
    {
#if DEBUG_SHARED_MEMORY_MODEL        
        cout << "[shared_memory_model] : copy " << this << " from " << &m << endl;
#endif
        m_data = m.m_data;
        return *this;
    }

    self_type& operator=( self_type &&m )
    {
#if DEBUG_SHARED_MEMORY_MODEL        
        cout << "[shared_memory_model] : move " << this << " from " << &m << endl;
#endif
        m_data = m.m_data;
        return *this;
    }
    
    template< typename T >
    self_type& operator=( T &&t )
    {
#if DEBUG_SHARED_MEMORY_MODEL
        cout << "[shared_memory_model] : type move " << this << " from " << &t << endl;
#endif
        m_data = std::make_shared< typename get_model< T >::type >( std::forward< T >( t ) );
        return *this;
    }
    
    
    
    concept_type& model( void ) { return *m_data; }
    
    std::shared_ptr< concept_type > m_data;
};

template< typename Concept , typename Model >
struct memory_model< shared_memory_model_tag , Concept , Model > { typedef shared_memory_model< Concept , Model > type; };




#endif // SHARED_MEMORY_MODEL_H_INCLUDED
