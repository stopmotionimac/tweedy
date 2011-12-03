#include <tweedy/core/icommand.hpp>

#include <iostream>
#include <queue>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

#define BOOST_TEST_MODULE tweedy_undo
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( tweedy_undo_suite01 )

BOOST_AUTO_TEST_CASE( undo_integers )
{
	// simple example to manipulate a stack of undo/redo commands
	// with basic commands to manipulate integer, strings, ...
	std::queue<int> q;
        
	q.push(5);
	q.push(51);
	q.push(52);
	q.push(53);

	BOOST_CHECK_EQUAL( q.front(), 5 );

	q.pop();
	
	BOOST_CHECK_EQUAL( q.size(), 3 );
	BOOST_CHECK_EQUAL( q.front(), 51 );
	BOOST_CHECK_EQUAL( q.back(), 53 );
	
}



BOOST_AUTO_TEST_CASE( undo_floats )
{
	// simple example to manipulate a stack of undo/redo commands
	// with basic commands to manipulate integer, strings, ...
        std::vector<int> v;
	
	v.push_back(5);
	v.push_back(51);
	v.push_back(52);
	v.push_back(53);

	BOOST_CHECK_EQUAL( v.front(), 5 );

	v.pop_back();
	
	BOOST_CHECK_EQUAL( v.size(), 3 );
	BOOST_CHECK_EQUAL( v.front(), 5 );
	BOOST_CHECK_EQUAL( v.back(), 52 );
	
}


BOOST_AUTO_TEST_CASE( undo_command )
{
	//2 types de commandes, l'une contenant un int, l'autre
        //contenant un char
    
    
        boost::ptr_vector<ICommand> v;
        
        ICommand* ci1 = new CommandInt(1);
        ICommand* ci2 = new CommandInt(500);
        ICommand* cc1 = new CommandChar('o');
        ICommand* cc2 = new CommandChar('M');
	
        
        v.push_back(ci1);
        v.push_back(cc2);
        v.push_back(cc1);
        v.push_back(ci2);
        
        
	BOOST_CHECK_EQUAL( v.front(), *ci1 );
        BOOST_CHECK_EQUAL( v.size(), 4 );

	v.pop_back();
	
	BOOST_CHECK_EQUAL( v.size(), 3 );
	BOOST_CHECK_EQUAL( v.front(), *ci1 );
	BOOST_CHECK_EQUAL( v.back(), *cc1 );
	
}

BOOST_AUTO_TEST_SUITE_END()
