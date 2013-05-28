
#include <gravel/Symbol.h>
#include <gravel/private/Symbol.h>



#include "gravel/Expression.h"

#include "gravel/private/Expression.h"
#include "gravel/Context.h"

 Gravel::Symbol::Symbol() {
     
 }

 Gravel::Symbol::Symbol(const std::string& name_) : symbol(new Gravel::Implementation::Symbol(name_)) {
     
 }
    const std::string Gravel::Symbol::getName() const {
        return symbol->getName();
    }
    
    
    Gravel::Interface::Symbol::Type Gravel::Symbol::getType() const{
        return symbol->getType();
    }
    
 Gravel::Implementation::Symbol::Symbol(const std::string& name_) : name(name_) { 
     
 }
 
Gravel::TemporarySymbol::TemporarySymbol() : Gravel::Symbol(Context::getInstance()->getUniqueIdentifier()) {
        
}
 
  Gravel::Symbol::Symbol(boost::weak_ptr<Gravel::GraphNode> graphNode )  {
      // find graph node connections
      
      Gravel::GraphNode::BackMapRange nr = GraphNode::getConnections(graphNode);
      
      Gravel::GraphNode::BackMapIterator ci;
      
      
      bool found = false;
      
      for(ci = nr.first ; ci != nr.second ; ci++ ) {
          
         Gravel::Pointer::Actor actor = GraphNode::getParent(ci->second);
          
          Gravel::Implementation::TermExpression * te = dynamic_cast< Gravel::Implementation::TermExpression * >(actor.get());
          if(te) {
              symbol = te->getSymbol().symbol;
              found = true;
              break;
          }
      }
      
      if (!found) {
          throw SymbolNotFoundException();
      }
      
      // find out the parent of each connected graph node and try and cast to a term expression
      
      // if all fail,  throw exception
      
      // else, build an appropriate symbol;
      
  }
 
const std::string Gravel::Implementation::Symbol::getName() const {
    return name;
}

bool Gravel::Symbol::operator==(const Gravel::Symbol& sm) const {
    return (getName() == sm.getName());
    
}

    Gravel::Interface::Symbol::Type Gravel::Implementation::Symbol::getType() const {
        return Gravel::Interface::Symbol::Wire;
    }
    
/*Gravel::Interface::Symbol::Type Gravel::SymbolDeclaration::getType() const{
    return symbol.getType();
}
   const std::string Gravel::SymbolDeclaration::getName() const{
    return symbol.getName();
}
*/
 Gravel::SymbolDeclaration::SymbolDeclaration(const Gravel::Symbol& symbol) : symbol(symbol) {
    Gravel::Context * ctx = Gravel::Context::getInstance();
     assert(ctx->isOwned(symbol));
     
 }

std::ostream& Gravel::operator<< (std::ostream& os, const Gravel::Symbol& s) {
    os << s.getName();
    return os;
}

unsigned Gravel::Symbol::getSymbolWidth(const Gravel::Symbol& sym) { 
     Gravel::Context * ctx = Gravel::Context::getInstance();
     return (rand() % 16);

}
    const Gravel::Symbol Gravel::SymbolDeclaration::getSymbol() const {
        return symbol;
    }

    
    void Gravel::Symbol::setWidth(Gravel::GraphNode::NodePtr, unsigned) { 
        
    }
    
    Gravel::GraphNode::NodePtr Gravel::Symbol::getOutput() const {
        
    }
    Gravel::GraphNode::ConstNodeRange Gravel::Symbol::getInputs() const {
        
    }
    
    
std::ostream& Gravel::operator<< (std::ostream& os, const Gravel::SymbolDeclaration& s) { 
    
    Gravel::Interface::Symbol::Direction direction = Interface::Symbol::Input;
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    
   switch(direction) { 
       case Interface::Symbol::Local :  {
        os << ((s.getSymbol().getType() == Gravel::Interface::Symbol::Wire) ? ("wire") : ("reg")) << " ";
    } break;
       case Interface::Symbol::Input : { 
           os << "input" << " ";
       } break;
       case Interface::Symbol::Output : { 
           os << "output" << " ";
       } break;
   }
    
    
   unsigned width = Gravel::Symbol::getSymbolWidth(s.getSymbol());
 
   if (width != 1) {
       os << "[" << width -1 << ":" << "0" << "]" << " ";
   }
   
   os << s.getSymbol().getName() << ";";
   return os;
}

Gravel::Symbol Gravel::Symbol::operator=(const Gravel::Expression& rhs) {
    // assign rhs correctly
    
    
    return *this;
}

   bool Gravel::Symbol::operator<(const Gravel::Symbol& s) const {
       return s.symbol.get() < symbol.get();
   }

 Gravel::Symbol::operator Gravel::Expression() { 
     // make a concrete termExpression wrapped in a shared ptr
     // build an Expression from that shared pointer
     Gravel::Pointer::Expression ptr(new Gravel::Implementation::TermExpression(*this));
     return Gravel::Expression(ptr);
     
 }