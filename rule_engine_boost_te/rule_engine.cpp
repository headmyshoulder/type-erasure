/*
 * rule_engine.h
 * Date: 2012-07-26
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#include <iostream>

#include "rule_engine.h"

#define tab "\t"

using namespace std;
using namespace rule_engine;



int main( int argc , char *argv[] )
{
    true_ t;
    expr e( t );

    not_ n( expr( t ) );
    // not_ n( t );          // Why does that not work

    expr e2( n );  // why does that not work?


    cout << e() << endl;
//    cout << e2() << endl;

    return 0;
}
