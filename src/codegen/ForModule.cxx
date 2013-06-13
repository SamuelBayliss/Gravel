
#include <potholes/codegen/ForModule.h>

#include <gravel/Gravel.h>
#include <gravel/private/Expression.h>

Potholes::Generator::ForModule::ForModule(clast_stmt * stmt) : 
        Potholes::Generator::Module(stmt), 
        upper_bound(((clast_for *)(stmt))->UB), 
        lower_bound(((clast_for *)(stmt))->LB), 
        fill_counter(Gravel::Symbol("FillCounter"))
        {
    
    // Calculate Output Range
    
    for_stmt = (clast_for *)(stmt);

    
  
    
   
}


Potholes::BoundExpression::BoundExpression(clast_expr * e) : 
Gravel::Expression(Gravel::Pointer::Expression(new Gravel::Implementation::NullExpression())) { 
        // build some kind of expression from this clast expr
}

void Potholes::Generator::ForModule::register_symbols() {
    
    Potholes::Generator::Module::register_symbols();
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    
    //ctx->insert(Gravel::Context::getPointer(this), fill_counter, Gravel::Interface::Symbol::Local);
    
 /* Build the two expressions for upper bound and lower bound */
   
 /* Build the necessary state machine for controlling module */
    Gravel::State fill("Fill");
    Gravel::State run("Run");

    Gravel::StateMachine sm(fill);


   
    sm.addTransition(fill >> run) -> condition( fill_counter == 1);
    sm.addAction(fill) ->action(fill_counter = fill_counter + 1);
    
 /* add appropriate symbols to module definition */
    
    
}


void Potholes::Generator::ForModule::build_chain() {
 

/* attach instantiated symbol to existing modules in top module */
    

    
}