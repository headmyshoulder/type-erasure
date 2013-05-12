/*
 * shared_memory_model.h
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef SHARED_MEMORY_MODEL_H_INCLUDED
#define SHARED_MEMORY_MODEL_H_INCLUDED

#include "memory_model.h"

#include <memory>
#include <type_traits>

#include <iostream>
using std::cout;
using std::endl;

struct shared_memory_model_tag {};

template< typename Concept , typename Model >
struct shared_memory_model
{
    typedef Concept concept_type;
    typedef Model model_type;
    typedef shared_memory_model< concept_type , model_type > self_type;
    
    template< typename T >
    struct enable_type_move_ctor : public
        std::enable_if< !std::is_same<
                        typename std::remove_cv< typename std::remove_reference< typename std::remove_cv< T >::type >::type >::type ,
                        self_type >::value , void* > { };
    
    template< typename T >
    struct get_model
    {
        typedef typename std::remove_reference< typename model_type::template apply< T >::type >::type type;
    };
    
    shared_memory_model( void ) : m_data() { };
    
    shared_memory_model( const self_type &m ) : m_data( m.m_data ) { }
    
//     template< typename T >
//     explicit shared_memory_model( const T &t ) : m_data( std::make_shared< typename get_model< T >::type >( t ) ) { }

    template< typename T >
    explicit shared_memory_model( T &&t ) : m_data( std::make_shared< typename get_model< T >::type >( std::forward< T >( t ) ) ) { }
    
    const self_type& operator=( const self_type &m )
    {
        m_data = m.m_data;
        return *this;
    }
    
    template< typename T >
    const self_type& operator=( const T &t )
    {
        m_data = std::make_shared< typename get_model< T >::type >( t );
        return *this;
    }
    
    
    
    concept_type& model( void ) { return *m_data; }
    
    std::shared_ptr< concept_type > m_data;
};

template< typename Concept , typename Model >
struct memory_model< shared_memory_model_tag , Concept , Model > { typedef shared_memory_model< Concept , Model > type; };




#endif // SHARED_MEMORY_MODEL_H_INCLUDED
