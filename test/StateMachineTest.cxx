
#include <boost/test/unit_test.hpp>

#include <gravel/Gravel.h>

#include <gravel/test/GenerateFixture.h>

BOOST_FIXTURE_TEST_SUITE ( StateMachineTest , GenerateFixture )

BOOST_AUTO_TEST_CASE( state_machine_constructor_test)
{
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    BOOST_CHECK ( ctx != NULL);
       Gravel::State a("A");
       
    Gravel::StateMachine sm(a);
    
}




/*
 * BOOST_AUTO_TEST_CASE( state_machine_add_state_test)
{
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    BOOST_CHECK ( ctx != NULL);
    
    Gravel::Module top("state_top");
    
    Gravel::Symbol x("x"); 
    top << x;
    Gravel::Symbol y("y");
    top << y;
    Gravel::Symbol z("z");
    top >> z;
    
    Gravel::Expression te(y);
    
    Gravel::State a("A");
    
    Gravel::State b("B");
   
    Gravel::StateMachine sm(a);
    
    sm.addTransition(a >> b) -> condition( x == te ); // on condition that x == te, make transition from a to b
    sm.addAction(a) -> action ( y = 5 )( x = 10)(z = 15);
    
    sm.synthesize(); // when synthesize is called, state machine must have attached to a module (otherwise runtime error)
    

    ctx->emit(std::cout);
}
*/

BOOST_AUTO_TEST_CASE( assignment ) {
       Gravel::Context * ctx = Gravel::Context::getInstance();
    
    BOOST_CHECK ( ctx != NULL);
    
    Gravel::Module top("assignment_top");
    
    Gravel::Symbol x("x"); 
    top << x;
    Gravel::Symbol y("y");
    top << y;
    Gravel::Symbol z("z");
    top >> z;
      
    
   Gravel::Assign(z << x);
    
    //Gravel::Delay(z = Gravel::Expression(x) , 2);
    //Gravel::Reset( z , 2);
    
    ctx->emit(std::cout);
    
}

BOOST_AUTO_TEST_CASE( sequential_assignment ) {
       Gravel::Context * ctx = Gravel::Context::getInstance();
       ww
    BOOST_CHECK ( ctx != NULL);
    
    Gravel::Module top("sequential_top");
    
    Gravel::Symbol x("x"); 
    top << x;
    Gravel::Symbol y("y");
    top << y;
    Gravel::Symbol z("z");
    top >> z;
      
    
    Gravel::Delay( z << x );
   // Gravel::Reset( z , 2 );
    
    ctx->emit(std::cout);
    
}

BOOST_AUTO_TEST_SUITE_END()
        