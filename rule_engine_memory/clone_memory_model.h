/*
 * clone_memory_model.h
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef CLONE_MEMORY_MODEL_H_INCLUDED
#define CLONE_MEMORY_MODEL_H_INCLUDED

struct clone_memory_model_tag {};

template< typename Concept , typename Model >
struct clone_memory_model
{
    typedef Concept concept_type;
    typedef Model model_type;
    typedef clone_memory_model< concept_type , model_type > self_type;
    
    template< typename T >
    struct get_model
    {
        typedef typename model_type::template apply< T >::type type;
    };
    
    clone_memory_model( void ) : m_data() { };
    
    clone_memory_model( const self_type &m ) : m_data( m.m_data->clone() ) { }
    
    template< typename T >
    explicit clone_memory_model( const T &t ) : m_data( new typename get_model< T >::type( t ) ) { }
    
    const self_type& operator=( const self_type &m )
    {
        m_data.reset( m.m_data->clone() );
        return *this;
    }
    
    template< typename T >
    const self_type& operator=( const T &t )
    {
        m_data.reset( new typename get_model< T >::type( t ) );
        return *this;
    }
    
    
    
    concept_type& model( void ) { return *m_data; }
    
    std::unique_ptr< concept_type > m_data;
};

template< typename Concept , typename Model >
struct memory_model< clone_memory_model_tag , Concept , Model > { typedef clone_memory_model< Concept , Model > type; };




#endif // CLONE_MEMORY_MODEL_H_INCLUDED
