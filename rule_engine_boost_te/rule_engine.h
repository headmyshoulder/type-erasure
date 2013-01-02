/*
 * rule_engine.h
 * Date: 2012-07-26
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */


#ifndef RULE_ENGINE_H_INCLUDED
#define RULE_ENGINE_H_INCLUDED

#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/callable.hpp>
#include <boost/type_erasure/constructible.hpp>
#include <boost/type_erasure/relaxed_match.hpp>




namespace rule_engine
{

    namespace te = boost::type_erasure;
    namespace mpl = boost::mpl;


    typedef mpl::vector<
        te::copy_constructible<> ,
        te::typeid_<> ,
        te::callable< bool( void ) > ,
        te::relaxed_match 
        > requirements ;
    typedef te::any< requirements > expr;


    class unary_expr
    {
    public:
        unary_expr( expr child ) : m_child( child ) { }
        expr& child( void ) { return m_child; }
        const expr& child( void ) const { return m_child; }
    protected:
        expr m_child;
    };

    class binary_expr
    {
    public:
        binary_expr( expr left , expr right ) : m_left( left ) , m_right( right ) { }
        expr& left( void ) { return m_left; }
        const expr& left( void ) const { return m_left; }
        expr& right( void ) { return m_right; }
        const expr& right( void ) const { return m_right; }
    protected:
        expr m_left , m_right;
    };



    struct true_ { bool operator()( void ) const { return true; } };

    struct false_ { bool operator()( void ) const { return false; } };

    struct not_ : public unary_expr
    {
        not_( expr child ) : unary_expr( child ) { }
        bool operator()( void ) { return ! m_child(); }
    };

    class and_ : public binary_expr
    {
    public:
        and_( expr left , expr right ) : binary_expr( left , right ) { } 
        bool operator()( void ) { return m_left() && m_right(); }
    };

    class or_ : public binary_expr
    {
    public:
        or_( expr left , expr right ) : binary_expr( left , right ) { } 
        bool operator()( void ) { return m_left() || m_right(); }
    };


}



#endif // RULE_ENGINE_H_INCLUDED
