
/*class StateMachine : SynthesizableModule{
    
};
addTransition

StateMachine sm;

Symbol x;
Symbol y;

sm.addTransition( "S1" >> "S2") <= ( y > x );

sm.addAction ( "S1" ) <= ( x2 += x + 1);

*/

#include <gravel/StateMachine.h>

#include <gravel/Assignment.h>

    Gravel::StateMachine::StateMachine(Gravel::State state) : resetState(state) { 
        
    }
    
    void Gravel::StateMachine::synthesize() { 
        
    }
    Gravel::StateTransition Gravel::StateMachine::addTransition(StateTransition) { 
        
    }
    
    Gravel::StateAction Gravel::StateMachine::addAction(Gravel::State s) { 
        
    }
    
        Gravel::State::State(const std::string& ) {
            
        }
        
        void Gravel::StateTransition::condition(Gravel::RelativeExpression) { 
           
        }
     Gravel::StateAction Gravel::StateAction::action(Gravel::Assignment) { 
           
        }
        
           Gravel::StateTransition * Gravel::StateTransition::operator ->() {
               return this;
               
           }
        
           Gravel::StateAction * Gravel::StateAction::operator ->() {
               return this;  
           }
        
           Gravel::StateAction Gravel::StateAction::operator ()(Gravel::Assignment) { 
               return *this;
           }
           
           
  Gravel::StateTransition operator>> (Gravel::State, Gravel::State) {
      Gravel::StateTransition a;
      return a;
  }