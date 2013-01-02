/*
 * test_condition.cpp
 * Date: 2012-11-27
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#include "condition.h"
#include "generic_conditions.h"
#include "condition_factory.h"

#include <iostream>

#define tab "\t"

using namespace std;

struct my_context { };



int main( int argc , char *argv[] )
{
    cout << "Hello world!" << endl;

    // my_context context;
    // condition< my_context > c;

    // c = true;
    // cout << c.eval( context ) << endl;
    // c = false;
    // cout << c.eval( context ) << endl;
    // c = logging_condition_decorator< my_context >( "True" , true );
    // cout << c.eval( context ) << endl;
    // c = logging_condition_decorator< my_context >( "False" , false );
    // cout << c.eval( context ) << endl;


    my_context context;
    condition_factory< my_context > f = make_logging_condition_factory< my_context >();
    condition< my_context > c1 = f.true_factory();
    condition< my_context > c2 = f.false_factory();
    condition< my_context > c3 = f.not_factory( f.true_factory() );
    condition< my_context > c4 = f.and_factory( f.true_factory() , f.not_factory( f.false_factory() ) );

    bool b1 = c1.eval( context );
    bool b2 = c2.eval( context );
    bool b3 = c3.eval( context );
    bool b4 = c4.eval( context );


    cout << "Result : " << b1 << "\t" << b2 << "\t" << b3 << "\t" << b4 << "\n";


    return 0;
}
