/*
 * main.cpp
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#include "condition.h"
#include "shared_memory_model.h"
#include "clone_memory_model.h"
#include "unique_memory_model.h"

#include <iostream>

#define tab "    "

using namespace std;

struct test_class
{
    int value;
    
    test_class( int v ) : value( v ) { cout << "[test class] type ctor( " << v << " ) " << this << endl; }
    test_class( void ) : value( 0 ) { cout << "[test class] default ctor " << this << endl; }
    ~test_class( void ) { cout << "[test class] dtor " << this << endl; }
    test_class( const test_class &t ) : value( t.value ) { cout << "[test class] copy ctor " << this << " from " << &t << endl; }
    test_class( test_class &&t ) : value( std::move( t.value ) ) { cout << "[test class] move ctor " << this << " from " << &t << endl; }
    test_class operator=( const test_class &t ) { value = t.value; cout << "[test class] copy " << this << " from " << &t << endl; }
    test_class operator=( test_class &&t ) { value = std::move( t.value ); cout << "[test class] move " << this << " from " << &t << endl; }
};

std::ostream& operator<<( std::ostream &out , const test_class &t )
{
    out << "test_class with value " << t.value;
}



int main( int argc , char *argv[] )
{
    int context = 23;
    
    cout << endl;


    
    cout << "[TESTING SHARED DEFAULT CONSTRUCTOR]" << endl;
    {
        condition< shared_memory_model_tag > cond;
    }
    cout << "[TESTING SHARED DEFAULT CONSTRUCTOR - FINISHED]" << endl << endl;

    cout << "[TESTING SHARED TYPE COPY CONSTRUCTOR]" << endl;
    {
        test_class t( 151 );
        condition< shared_memory_model_tag > cond( t );
        cond.eval( context );
    }
    cout << "[TESTING SHARED TYPE COPY CONSTRUCTOR - FINISHED]" << endl << endl;

//     cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR]" << endl;
//     {
//         test_class t( 151 );
//         condition< shared_memory_model_tag > cond( std::move( t ) );
//         cond.eval( context );
//     }
//     cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR - FINISHED]" << endl << endl;
// 
//     cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR II]" << endl;
//     {
//         condition< shared_memory_model_tag > cond( test_class( 152 ) );
//         cond.eval( context );
//     }
//     cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR II - FINISHED]" << endl << endl;
// 
//     cout << "[TESTING SHARED COPY CONSTRUCTOR]" << endl;
//     {
//         condition< shared_memory_model_tag > cond1( test_class( 152 ) );
//         condition< shared_memory_model_tag > cond2( cond1 );
//         cond1.eval( context );
//         cond2.eval( context );
//     }
//     cout << "[TESTING SHARED COPY CONSTRUCTOR - FINISHED]" << endl << endl;
// 
//     cout << "[TESTING SHARED MOVE CONSTRUCTOR]" << endl;
//     {
//         condition< shared_memory_model_tag > cond1( test_class( 152 ) );
//         condition< shared_memory_model_tag > cond2( std::move( cond1 ) );
//         cond1.eval( context );
//         cond2.eval( context );
//     }
//     cout << "[TESTING SHARED MOVE CONSTRUCTOR - FINISHED]" << endl << endl;






//         cond2 = cond1;
//         cond2 = test_class( 23 );

    //         test_class t2( 56 );
    //         condition< shared_memory_model_tag > cond6( 32 );
    //         cond6 = std::move( t2 );
    //

//         test_class t3( 77 );
//         condition< shared_memory_model_tag > cond7;
//         cond7 = t3;

//             condition< shared_memory_model_tag > cond8;
//             condition< shared_memory_model_tag > cond9;
//             cond8 = cond9;
        
//         cond1.eval( context );
//         cond2.eval( context );
//         cond3.eval( context );

//         condition< shared_memory_model_tag >::test_type_move_ctor( cond4 );
//         condition< shared_memory_model_tag >::test_type_move_ctor( std::move( cond4 ) );
//         condition< shared_memory_model_tag >::test_type_move_ctor( 32 );
//         int a = 32;
//         condition< shared_memory_model_tag >::test_type_move_ctor( a );
//         condition< shared_memory_model_tag >::test_type_move_ctor( std::move( a ) );
//    }
    cout << "Finished test shared memory model" << endl << endl;
    
    
    
//     cout << "Testing cloning memory model" << endl;
//     {
//         test_class t( 151 );
// 
//         condition< clone_memory_model_tag > cond1( t );
//         condition< clone_memory_model_tag > cond2( cond1 );
//         condition< clone_memory_model_tag > cond3( test_class( 12 ) );
//         
//         cond2 = cond1;
//         cond2 = test_class( 23 );
//         
//         cond1.eval( context );
//         cond2.eval( context );
//         cond3.eval( context );
//     }
//     cout << "Finished test clone memory model" << endl << endl;
//     
//     
//     
//     
//     cout << "Testing unique memory model!" << endl;
//     {
//         test_class t( 151 );
//         
//         condition< unique_memory_model_tag > cond1( t );
//         condition< unique_memory_model_tag > cond2;
//         
//         cond1.eval( context );
//     }
//     cout << "Finished test unique memory model" << endl << endl;
//     
    
    
//     condition< copy_memory_model_tag > cond2;
//     condition< unique_memory_model_tag > cond3;


    cout << "[TESTING condition::model< T >]" << endl;
    {
        typedef condition< shared_memory_model_tag >::model< test_class > model_type;
        test_class t1( 12 ) , t2( 13 );
        model_type m1( t1 );
        model_type m2( std::move( t2 ) );
    }
    cout << "[TESTING condition::model< T > - FINISHED]" << endl << endl;
    
    return 0;
}
