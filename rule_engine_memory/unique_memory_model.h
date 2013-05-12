/*
 * unique_memory_model.h
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef UNIQUE_MEMORY_MODEL_H_INCLUDED
#define UNIQUE_MEMORY_MODEL_H_INCLUDED

struct unique_memory_model_tag {};


template< typename Concept , typename Model >
struct unique_memory_model
{
    typedef Concept concept_type;
    typedef Model model_type;
    typedef unique_memory_model< concept_type , model_type > self_type;
    
    template< typename T >
    struct get_model
    {
        typedef typename model_type::template apply< T >::type type;
    };
    
    unique_memory_model( void ) : m_data() { };
    
    unique_memory_model( const self_type & ) = delete;
    
    template< typename T >
    explicit unique_memory_model( const T &t ) : m_data( new typename get_model< T >::type( t ) ) { }
    
    const self_type& operator=( const self_type &m ) = delete;
    
    
    
    concept_type& model( void ) { return *m_data; }
    
    std::unique_ptr< concept_type > m_data;
};

template< typename Concept , typename Model >
struct memory_model< unique_memory_model_tag , Concept , Model > { typedef unique_memory_model< Concept , Model > type; };


#endif // UNIQUE_MEMORY_MODEL_H_INCLUDED
