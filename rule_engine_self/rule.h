/*
 * rule.h
 * Date: 2012-11-27
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#ifndef RULE_H_INCLUDED
#define RULE_H_INCLUDED

#include "condition.h"
#include "consequence.h"

template< class Context >
struct rule
{
    typedef Context context_type;

    condition< context_type > m_condition;
    consequence< context_type > m_consequence;
    
    void eval( context_type &c )
    {
        if( m_condition.eval( c ) ) m_consequence.run( c );
    }
};

#endif // RULE_H_INCLUDED
