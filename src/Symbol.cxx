
#include <gravel/Symbol.h>
//#include <gravel/private/Symbol.h>



#include <gravel/Expression.h>
#include <gravel/private/Expression.h>
#include <gravel/Context.h>

#include <gravel/Assignment.h>

 Gravel::Symbol::Symbol() {
     
 }

 Gravel::Symbol::~Symbol() { 

     
     Gravel::Context * ctx = Gravel::Context::getInstance();
     
     if (!ctx->isOwned(symbol)) { 
       std::cout << "Orphan Symbol (" << getName() << ") was destroyed" << std::endl;
     }
     
}
 
 void Gravel::Symbol::attach(const Gravel::Pointer::Module& module) const { 
     // dynamic cast to a symbol
     // attach to context
     Gravel::Context * ctx = Gravel::Context::getInstance();
     ctx->insert(symbol, module);
     
     
 }
 
Gravel::Module Gravel::Symbol::getOwner() const {
      Gravel::Context * ctx = Gravel::Context::getInstance();
     // std::cout << "Finding owner for " << symbol->getName() << "\n";
      return ctx->owner(symbol);
 }
 
 Gravel::Symbol::Symbol(const std::string& name_) : symbol(new Gravel::Implementation::Symbol(name_)) {
     symbol->initialize(symbol);
 }
    const std::string Gravel::Symbol::getName() const {
        return symbol->getName();
    }
    
    
    Gravel::Interface::Symbol::Type Gravel::Symbol::getType() const{
        return symbol->getType();
    }
    
 Gravel::Implementation::Symbol::Symbol(const std::string& name_) : name(name_) {
     
    
      Gravel::Pointer::GraphNode inode = Gravel::GraphNode::Create(nodes, Gravel::Input);
      Gravel::Pointer::GraphNode onode = Gravel::GraphNode::Create(nodes, Gravel::Output);
 }
 
 Gravel::Implementation::Constant::Constant(int i) : value(i) {
        Gravel::Pointer::GraphNode onode = Gravel::GraphNode::Create(nodes, Gravel::Output);
 }
 
  Gravel::Pointer::GraphNode Gravel::Implementation::Constant::getOutput() const {
     Gravel::GraphNode::ConstNodeIterator cni = this->nodes.find(Gravel::Output);
     
     if (cni == nodes.end()) {
         throw Gravel::Exception::GraphNodeNotFound();
     }
     
     return cni->second;
  }

  Gravel::GraphNode::ConstNodeRange Gravel::Implementation::Constant::getInputs() const {
      // return empty set
      return Gravel::GraphNode::ConstNodeRange(nodes.end(), nodes.end());
  }
 
Gravel::TemporarySymbol::TemporarySymbol() : Gravel::Symbol(Context::getInstance()->getUniqueIdentifier()) {
        
}
 
// Make t

Gravel::Pointer::Symbol FindSymbol(Gravel::Pointer::Actor actor) {
     Gravel::Pointer::Symbol symbol = boost::dynamic_pointer_cast<Gravel::Implementation::Symbol>(actor);        
     Gravel::Pointer::Expression expression = boost::dynamic_pointer_cast<Gravel::Implementation::Expression>(actor);
     
     if (!symbol) {
     
         if (expression) {
            symbol = expression->getSymbol();
        } else { 
             Gravel::Pointer::Constant constant = boost::dynamic_pointer_cast<Gravel::Implementation::Constant>(actor);
            
             Gravel::Pointer::GraphNode onode = constant->getOutput();
             Gravel::GraphNode::BackMapRange range = Gravel::GraphNode::getConnections(onode);
             
             Gravel::GraphNode::BackMapIterator bit;
             
             for (bit = range.first ; bit != range.second ; bit++ ) {
                 
                 Gravel::WeakPointer::GraphNode wgn = bit->second;
                 
                 Gravel::Pointer::GraphNode gn = wgn.lock();
                 
                 actor = Gravel::GraphNode::getParent(gn);
                 symbol = FindSymbol(actor);
             }
             
             
             
        }
     }
     if (!symbol) throw Gravel::SymbolNotFoundException();
   
     return symbol;
}

 Gravel::Symbol::Symbol(Gravel::Pointer::Actor actor)  {
      // find graph node connections
     
 
      
      
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
    assert (Symbol::Owned(symbol));
     
 }

 bool Gravel::Symbol::Owned(const Gravel::Symbol& symbol) {
      Gravel::Context * ctx = Gravel::Context::getInstance();
      return ctx->isOwned(symbol.symbol);
  }
 

void Gravel::Symbol::attach(Gravel::Pointer::Module& module, const Gravel::Interface::Symbol::Direction& direction) const {
            Gravel::Context * ctx = Gravel::Context::getInstance();
            ctx->insert(module, symbol, direction);
}

std::ostream& Gravel::operator<< (std::ostream& os, const Gravel::Symbol& s) {
    os << s.getName();
    return os;
}

unsigned Gravel::Symbol::getSymbolWidth(const Gravel::Symbol& sym) { 
     Gravel::Context * ctx = Gravel::Context::getInstance();
   
     Gravel::Pointer::GraphNode node = sym.getOutput();

     return node->getWidth();

}
    const Gravel::Symbol Gravel::SymbolDeclaration::getSymbol() const {
        return symbol;
    }

    
    void Gravel::Symbol::setWidth(Gravel::Pointer::GraphNode, unsigned) { 
        
    }
    
    void Gravel::Implementation::Constant::setWidth(Gravel::Pointer::GraphNode, unsigned int) {
        
    }
    
    Gravel::Pointer::GraphNode Gravel::Symbol::getOutput() const {
        return symbol->getOutput();
    }
    Gravel::GraphNode::ConstNodeRange Gravel::Symbol::getInputs() const {
        return symbol->getInputs();
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

Gravel::Assignment Gravel::Symbol::operator=(const Gravel::Expression& rhs) {
    // assign rhs correctly
    Gravel::Symbol lhs = *this;
    
    Gravel::Assignment a = Gravel::Assignment::Create(lhs, rhs, 0);
    
    return a;
}

   bool Gravel::Symbol::operator<(const Gravel::Symbol& s) const {
       return s.symbol.get() < symbol.get();
   }

 Gravel::Symbol::operator const Gravel::Expression() const { 
     // make a concrete termExpression wrapped in a shared ptr
     // build an Expression from that shared pointer
     Gravel::Pointer::Expression ptr(new Gravel::Implementation::TermExpression(this->symbol));
     
     ptr->initialize(ptr);
     
     return Gravel::Expression(ptr);
     
 }
 
  Gravel::Symbol::Symbol(Gravel::Pointer::Symbol symbol ) : symbol(symbol) {
      
  }