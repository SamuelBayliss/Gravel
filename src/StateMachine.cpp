class StateMachine : SynthesizableModule{
    
};
addTransition

StateMachine sm;

Symbol x;
Symbol y;

sm.addTransition( "S1" >> "S2" ) -> ( y > x );

sm.addAction ( "S1") -> ( x2 += x + 1);

