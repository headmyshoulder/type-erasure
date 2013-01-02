/*
 * generic_conditions.h
 * Date: 2012-11-27
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef GENERIC_CONDITIONS_H_INCLUDED
#define GENERIC_CONDITIONS_H_INCLUDED

#include "condition.h"

template< class Context >
struct unary_condition 
{
    condition< Context > m_child;
};

template< class Context >
struct binary_condition
{
    condition< Context > m_left;
    condition< Context > m_right;
};

template< class Context > struct not_condition : unary_condition< Context > { };
template< class Context > struct and_condition : binary_condition< Context > { };
template< class Context > struct or_condition : binary_condition< Context > { };
template< class Context > struct logging_condition_decorator
{
    condition< Context > m_decorated_condition;
    std::string m_name;
};








template< class Context >
not_condition< Context > make_not_condition( const condition< Context > &c )
{
    not_condition< Context > cond;
    cond.m_child = c;
    return cond;
}

template< class Context >
and_condition< Context > make_and_condition( const condition< Context > &l , const condition< Context > &r )
{
    and_condition< Context > cond;
    cond.m_left = l;
    cond.m_right = r;
    return cond;
}

template< class Context >
or_condition< Context > make_or_condition( const condition< Context > &l , const condition< Context > &r )
{
    or_condition< Context > cond;
    cond.m_left = l;
    cond.m_right = r;
    return cond;
}

template< class Context >
logging_condition_decorator< Context > make_logging_condition( const std::string &name , const condition< Context > d )
{
    logging_condition_decorator< Context > cond;
    cond.m_name = name;
    cond.m_decorated_condition = d;
    return cond;
}



template< class Context >
struct eval_impl< bool , Context >
{
    static bool eval( bool &value , Context &c ) 
    {
        return value;
    }
};

template< class Context > struct eval_impl< not_condition< Context > , Context >
{
    static bool eval( not_condition< Context > &n , Context & c )
    {
        return ! n.m_child.eval( c );
    }
};

template< class Context > struct eval_impl< and_condition< Context > , Context >
{
    static bool eval( and_condition< Context > &n , Context & c )
    {
        return n.m_left.eval( c ) && n.m_right.eval( c );
    }
};

template< class Context > struct eval_impl< or_condition< Context > , Context >
{
    static bool eval( or_condition< Context > &n , Context & c )
    {
        return n.m_left.eval( c ) || n.m_right.eval( c );
    }
};

template< class Context >
struct eval_impl< logging_condition_decorator< Context > , Context >
{
    static bool eval( logging_condition_decorator< Context > &l , Context &c )
    {
        std::cout << "Evaluate condition \"" << l.m_name << " ( \n";
        bool ret = l.m_decorated_condition.eval( c );
        std::cout << " ) Result : " << ret << std::endl;
        return ret;
    }
};



#endif // GENERIC_CONDITIONS_H_INCLUDED
