/*
 * test_shared.cpp
 * Date: 2013-05-16
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#include "condition.h"
#include "shared_memory_model.h"


#include <sstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define TestName test_shared

using namespace std;

struct mocker
{
    MOCK_METHOD0( DefaultConstruct , void() );
    MOCK_METHOD0( TypeConstruct , void() );
    MOCK_METHOD0( CopyConstruct , void() );
    MOCK_METHOD0( MoveConstruct , void() );
    MOCK_METHOD0( Destruct , void() );
    MOCK_METHOD0( CopyAssign , void() );
    MOCK_METHOD0( MoveAssign , void() );
};

std::unique_ptr< mocker > mocker_;

struct test_class
{

    int value;

    test_class( void ) : value( 0 ) { mocker_->DefaultConstruct(); }
    test_class( int v ) : value( v ) { mocker_->TypeConstruct(); }
    test_class( const test_class &t ) : value( t.value ) { mocker_->CopyConstruct(); }
    test_class( test_class &&t ) : value( std::move( t.value ) ) { mocker_->MoveConstruct(); }

    ~test_class( void ) { mocker_->Destruct(); }
    
    test_class& operator=( const test_class &t ) { value = t.value; mocker_->CopyAssign(); return *this; }
    test_class& operator=( test_class &&t ) { value = std::move( t.value ); mocker_->MoveAssign(); return *this; }
};


std::ostream& operator<<( std::ostream &out , const test_class &t )
{
    out << "mock_class with value " << t.value;
}

typedef condition< shared_memory_model_tag > con;

class ConditionTest : public ::testing::Test
{
protected:

    virtual void SetUp( void )
    {
        mocker_.reset( new mocker() );
    }

    virtual void TearDown( void )
    {
        mocker_.reset( nullptr );
    }
};


TEST_F( ConditionTest , default_construct )
{
    con c;
}

TEST_F( ConditionTest , type_construct )
{
    EXPECT_CALL( *mocker_ , DefaultConstruct() )
        .Times( 1 );
    EXPECT_CALL( *mocker_ , Destruct() )
        .Times( 2 );


    test_class m;
    con c( m );
}

