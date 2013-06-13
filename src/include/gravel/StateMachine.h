/* 
 * File:   StateMachine.h
 * Author: sb1708
 *
 * Created on May 29, 2013, 12:24 PM
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include <gravel/Module.h>
#include <gravel/Expression.h>


namespace Gravel { 

class StateTransition { 
public:
    StateTransition * operator ->();
    StateTransition operator()();
    void condition(Gravel::RelativeExpression);
};

class StateAction {
public:
    StateAction * operator ->();
    StateAction operator()(Gravel::Assignment);
    StateAction action(Gravel::Assignment);
};


class State {
public:

    State(const std::string&);
};

class StateMachine : public SynthesizableModule{
public : 
    StateMachine(Gravel::State);
    void synthesize();
    StateTransition addTransition (StateTransition);
    StateAction addAction(Gravel::State);
private:
    Gravel::State resetState;
};



};



Gravel::StateTransition operator>> (Gravel::State,Gravel::State);



#endif	/* STATEMACHINE_H */

