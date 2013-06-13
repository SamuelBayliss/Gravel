
#include <gravel/Expression.h>
#include <gravel/private/Expression.h>
#include <gravel/private/Node.h>

#include "gravel/Context.h"

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

/*Gravel::TermExpression::TermExpression(Gravel::Symbol sym) : ptr(Gravel::Pointer::TermExpression(new Gravel::Implementation::TermExpression(sym))) {
    
}
*/

void Gravel::Expression::attach(const Gravel::Pointer::Module& module) const {
  
   Gravel::Context * ctx = Gravel::Context::getInstance();
    ctx->insert(ptr, module);
}

Gravel::Module Gravel::Expression::getOwner() const { 
      Gravel::Context * ctx = Gravel::Context::getInstance();
      return ctx->owner(ptr);
}

   const Gravel::Pointer::Symbol Gravel::Implementation::Expression::getSymbol() const { 
       // find output graphNode
       
       Gravel::Pointer::GraphNode cr = this->getOutput();
       
       // find nodes connected to the output graphnode
       
        Gravel::GraphNode::BackMapRange br = Gravel::GraphNode::getConnections(cr);
        
        Gravel::GraphNode::BackMapIterator bit;
        for (bit = br.first ; bit != br.second ; bit++ ) {
            
            Gravel::WeakPointer::GraphNode wgn = bit->second;
            Gravel::Pointer::GraphNode gn = wgn.lock();
            
             boost::shared_ptr<const Gravel::Implementation::TermExpression> te = 
                boost::dynamic_pointer_cast<const Gravel::Implementation::TermExpression>(Gravel::GraphNode::getParent(gn));
             
             if (te) {
                 return te->getSymbol();
             }
             
        }
        assert(false);
       // one should be a TermExpression
       
       // return symbol from TermExpression
       
   }

        
   
   /* Gravel::Implementation::TermExpression::TermExpression(Gravel::Constant constant) {
    
        boost::shared_ptr<Gravel::GraphNode> onode = boost::shared_ptr<Gravel::GraphNode>(new Gravel::GraphNode());
        nodes.insert(Gravel::GraphNode::NodePair(Gravel::Output, onode));
    
         GraphNode::connect(inode, sym.getOutput());
        
    }*/
   
   
   
Gravel::Implementation::TermExpression::TermExpression(Gravel::Pointer::Constant constant)  {
    

     Gravel::Pointer::GraphNode onode = Gravel::GraphNode::Create(nodes, Gravel::Output);
     
     Gravel::Pointer::GraphNode inode = Gravel::GraphNode::Create(nodes, Gravel::Input);
   
     GraphNode::connect(inode, constant->getOutput());
}

Gravel::Implementation::TermExpression::TermExpression(Gravel::Pointer::Symbol symbol)  {
    
 
     Gravel::Pointer::GraphNode onode = Gravel::GraphNode::Create(nodes, Gravel::Output);
     
     Gravel::Pointer::GraphNode inode = Gravel::GraphNode::Create(nodes, Gravel::Input);
   
   
    GraphNode::connect(inode, symbol->getOutput());
}


    
    /*try { 
           const Gravel::Implementation::Constant & constant = dynamic_cast<const Gravel::Implementation::Constant&>(actor);
           
           // build a symbol to accept the constant
           Gravel::TemporarySymbol symbol;
           // get inputs of symbol and connect to this term expression output

           Gravel::GraphNode::ConstNodeRange cr = this->getInputs();
  
        Gravel::GraphNode::ConstNodeIterator nit;
        for (nit = cr.first ; nit != cr.second ; nit++) {
                GraphNode::connect(onode, nit->second);
        }
           
           
    } catch(std::bad_cast&) { 
        
    }
 */
    // normalize expression and symbol ownership
    
    
Gravel::Expression::~Expression() { 
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    
    if (! ctx->isOwned(ptr) ) {
         std::cout << "Orphan Expression was destroyed" << std::endl;
    }
}



const Gravel::Pointer::Symbol Gravel::Implementation::TermExpression::getSymbol() const { 
    
    // get input actors
    
   //Gravel::Context * ctx =  Gravel::Context::getInstance();
    
    Gravel::GraphNode::ConstNodeRange cr = this->getInputs();
  
    Gravel::GraphNode::ConstNodeIterator nit;
    for (nit = cr.first ; nit != cr.second ; nit++) {
        
       // if input actor is a constant, return the symbol attached to output actor
    
        Gravel::GraphNode::BackMapRange br = Gravel::GraphNode::getConnections(nit->second);
        
        Gravel::GraphNode::BackMapIterator bit;
     
        for (bit = br.first ; bit != br.second ; bit++ ) {
            
            Gravel::WeakPointer::GraphNode wgn = bit->second;
            Gravel::Pointer::GraphNode gn = wgn.lock();
            
            boost::shared_ptr<const Gravel::Implementation::Constant> constant = 
                boost::dynamic_pointer_cast<const Gravel::Implementation::Constant>(Gravel::GraphNode::getParent(gn));
            
            if (constant ) {
            
            Gravel::Pointer::GraphNode onode = this->getOutput();
            
            Gravel::GraphNode::BackMapRange bnr = Gravel::GraphNode::getConnections(onode);
            
             Gravel::WeakPointer::GraphNode bwgn = bnr.first->second;
             Gravel::Pointer::GraphNode bgn = bwgn.lock();
            
            return boost::dynamic_pointer_cast<Gravel::Implementation::Symbol>(Gravel::GraphNode::getParent(bgn));
            
            }

            boost::shared_ptr<Gravel::Implementation::Symbol> symbol = 
                boost::dynamic_pointer_cast<Gravel::Implementation::Symbol>(Gravel::GraphNode::getParent(gn));
            
            if (symbol != boost::shared_ptr<Gravel::Implementation::Symbol>() ) {
            
                return symbol;
            
            }
        
        }
       // if input actor is a symbol, return the symbol
        
        
    }
    assert(false);

    
}

 bool Gravel::Expression::Owned(const Gravel::Expression& e) { 
   Gravel::Context * ctx = Gravel::Context::getInstance();  
   
   return ctx->isOwned(e.ptr);
 }

Gravel::Implementation::BinaryExpression::BinaryExpression(const Gravel::Expression lhs, 
                                                           const Gravel::Expression rhs, 
                                                           const Gravel::BinaryExpressionType binop) : 
lhs(lhs), rhs(rhs), binop(binop) { 
    
 
    Gravel::Context * ctx = Context::getInstance();
    
    if (Gravel::Expression::Owned(lhs) && Gravel::Expression::Owned(rhs)) { 
        if (lhs.getOwner() != rhs.getOwner()) {
            // throw InvalidExpressionException
        }
    }
      
    Gravel::Pointer::GraphNode lnode = Gravel::GraphNode::Create(nodes, Gravel::Input);
    Gravel::Pointer::GraphNode rnode = Gravel::GraphNode::Create(nodes, Gravel::Input);   
    Gravel::Pointer::GraphNode onode = Gravel::GraphNode::Create(nodes, Gravel::Output);   

    GraphNode::connect(rnode, rhs.getOutput());
    GraphNode::connect(lnode, lhs.getOutput());
    
    Gravel::Expression temp = Gravel::TemporarySymbol() ;
    
    GraphNode::ConstNodeRange nr = temp.getInputs();
    for (GraphNode::ConstNodeIterator ni = nr.first ; ni != nr.second ; ni++) {
        GraphNode::connect(onode, Gravel::Pointer::GraphNode(ni->second));
    }
    ctx->propagate();
    // normalize expression and symbol ownership
    
    
      /*
       
       Add Temporary Symbols to context (store pointers to them here too)
      
      */
      
    // check if rhs expression is assigned to a particular module
    
    // throw exception if they belong to different modules
    
    // connect to existing nodes in graph
    
    // create input nodes
  
    
}

//Gravel::BinaryExpression::BinaryExpression(const Gravel::Expression& lhs, const Gravel::Expression& rhs, const Gravel::BinaryExpression::BinaryExpressionType& binop) :
//ptr(boost::shared_ptr<Gravel::Implementation::BinaryExpression>( new Gravel::Implementation::BinaryExpression(lhs, rhs, binop))) {
        
    // check if lhs expression is assigned to a particular module
    
/*
 */   
//}
 /*  const Gravel::Expression& Gravel::BinaryExpression::getLHS() { 
       return ptr->getLHS();
   }
        const Gravel::Expression& Gravel::BinaryExpression::getRHS() { 
            return ptr->getRHS();
        }
*/

Gravel::Pointer::GraphNode Gravel::Expression::getOutput() const { 
      return ptr->getOutput();
  }

void Gravel::Expression::setWidth(Gravel::Pointer::GraphNode node, unsigned width) {
     return ptr->setWidth(node, width); 
}

 Gravel::GraphNode::ConstNodeRange Gravel::Expression::getInputs() const {
      return ptr->getInputs();
 }

 Gravel::Implementation::NullExpression::NullExpression() { 
     
 }
 
    std::ostream& Gravel::Implementation::NullExpression::emit(std::ostream&) const {
        
    }
 
 Gravel::Expression::Expression(int i) : ptr(Gravel::Pointer::Expression(new Gravel::Implementation::TermExpression(
        Gravel::Pointer::Constant(new Gravel::Implementation::Constant(i))))) {
        ptr->initialize(ptr);
  
         
     
 } // promotion of int, creates constant and registers termExpression
 
 Gravel::Expression::Expression(const Gravel::Pointer::Expression e) : ptr(e) {
         
 }
 
 const Gravel::Pointer::Symbol Gravel::Expression::getSymbol() const{ 
  return ptr->getSymbol();
 }
 
Gravel::Expression Gravel::operator*(const Gravel::Expression& lhs, const Gravel::Expression& rhs)   { 
    
    Gravel::Pointer::Expression ptr(new Gravel::Implementation::BinaryExpression(lhs,rhs, Gravel::Multiply));
    
    ptr->initialize(ptr);
    
    return Gravel::Expression(ptr);
}

Gravel::Expression Gravel::operator+(const Gravel::Expression& lhs, const Gravel::Expression& rhs)   { 
    
    Gravel::Pointer::Expression ptr(new Gravel::Implementation::BinaryExpression(lhs,rhs, Gravel::Add));
    
  //  GraphNode::setParents(ptr);
    ptr->initialize(ptr);
    
    return Gravel::Expression(ptr);
}

    Gravel::RelativeExpression operator==(const Gravel::Symbol& lhs, const Gravel::Expression& rhs) {
        Gravel::Pointer::Expression ptr(new Gravel::Implementation::RelativeExpression(lhs, rhs, Gravel::Equals));
        
        ptr->initialize(ptr);
        
        return Gravel::RelativeExpression(ptr);
    }
    
    
      std::ostream& Gravel::Implementation::RelativeExpression::emit(std::ostream& ) const {
          
      }
    
    Gravel::Implementation::RelativeExpression::RelativeExpression(const Gravel::Expression lhs, const Gravel::Expression rhs, const Gravel::RelativeExpressionType) { 
     
         Gravel::Pointer::GraphNode lnode = Gravel::GraphNode::Create(nodes, Gravel::Input);
         Gravel::Pointer::GraphNode rnode = Gravel::GraphNode::Create(nodes, Gravel::Input);   
         Gravel::Pointer::GraphNode onode = Gravel::GraphNode::Create(nodes, Gravel::Output);   

         GraphNode::connect(rnode, rhs.getOutput());
         GraphNode::connect(lnode, lhs.getOutput());
    
    }
    
    Gravel::RelativeExpression::RelativeExpression(const Gravel::Pointer::Expression e) : Gravel::Expression(e) { 

    }
 
    Gravel::RelativeExpression Gravel::operator==(Gravel::Symbol const& lhs, Gravel::Expression const& rhs) {
              Gravel::Pointer::Expression ptr(new Gravel::Implementation::RelativeExpression(lhs, rhs, Gravel::Equals));
              
              ptr->initialize(ptr);
        return RelativeExpression(ptr);
    }
    
  /*  Gravel::RelativeExpression operator==(const Gravel::Symbol& lhs, const Gravel::Constant& rhs) {
        Gravel::Expression elhs = lhs;
        Gravel::Expression erhs = rhs;
        Gravel::Pointer::Expression ptr(new Gravel::Implementation::RelativeExpression(elhs, erhs, Gravel::Equals));
        
        return Gravel::RelativeExpression(ptr);
    }
*/
     const Gravel::Expression& Gravel::Implementation::BinaryExpression::getLHS() {
                return lhs;
            }
            
     const Gravel::Expression& Gravel::Implementation::BinaryExpression::getRHS() {
                return rhs;
            }
     
       bool Gravel::Expression::operator==(const Gravel::Expression& e) const {
           if (e.ptr.get() == ptr.get()) {
               return true;
           }
       }
       
       bool Gravel::Expression::operator<(const Gravel::Expression & e) const {
           if (e.ptr.get() < ptr.get() ) {
               return true;
           }
           return false;
       }
  
    
 std::ostream& Gravel::operator<<(std::ostream& os, const Gravel::Expression& expression) {
        expression.emit(os);
        return os;
    }
 
 
 
 
 std::ostream& Gravel::Expression::emit(std::ostream& os) const{
       return os;
 }
 
  std::ostream& Gravel::Implementation::MuxExpression::emit(std::ostream& os) const{
      os << "Mux";
        return os;
  }
  
  std::ostream& Gravel::Implementation::TermExpression::emit(std::ostream& os) const{
      // nothing needed
        return os;
  }
  
  std::ostream& Gravel::Implementation::BinaryExpression::emit(std::ostream& os) const {
      try { 

      Gravel::Pointer::GraphNode onode = this->getOutput();
      
      Gravel::Collection::GraphNodeRange inodes = this->getInputs();
      
      Gravel::Symbol output = GraphNode::getParent(onode);
      
      Gravel::Symbol lhs = GraphNode::getParent(inodes.first);
      Gravel::Symbol rhs = GraphNode::getParent(inodes.second);
      
        os << "assign" << " " << output << "=" << lhs << " ";
        
        switch(binop) { 
            case Sub : {
                os << "-";
            }  break;
            case Add : {
                    os << "+";
            }  break;
            case Multiply : {
                    os << "*";
            }  break;
            case XOR : { 
                    os << "^";
            } break;
        }
                
        os << " " << rhs << ";";
      } catch (Gravel::SymbolNotFoundException & noe) { 
          
      }
                
                
        return os;
  }
  
  