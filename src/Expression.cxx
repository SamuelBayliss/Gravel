
#include <gravel/Expression.h>
#include <gravel/private/Expression.h>
#include <gravel/private/Node.h>

#include "gravel/Context.h"

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

/*Gravel::TermExpression::TermExpression(Gravel::Symbol sym) : ptr(Gravel::Pointer::TermExpression(new Gravel::Implementation::TermExpression(sym))) {
    
}
*/

   const Gravel::Symbol Gravel::Implementation::Expression::getSymbol() { 
       
   }

Gravel::Implementation::TermExpression::TermExpression(Gravel::Symbol sym) : symbol(sym) {
    
  
    // normalize expression and symbol ownership
  
    boost::shared_ptr<Gravel::GraphNode> onode = boost::shared_ptr<Gravel::GraphNode>(new Gravel::GraphNode());
    nodes.insert(Gravel::GraphNode::NodePair(Gravel::Output, onode));
    
    boost::shared_ptr<Gravel::GraphNode> inode = boost::shared_ptr<Gravel::GraphNode>(new Gravel::GraphNode());
    nodes.insert(Gravel::GraphNode::NodePair(Gravel::Input, inode));
    
   // GraphNode::connect(inode, sym.getOutput());
    
    
}

const Gravel::Symbol Gravel::Implementation::TermExpression::getSymbol() { 
    return symbol;
}

Gravel::Implementation::BinaryExpression::BinaryExpression(const Gravel::Expression lhs, 
                                                           const Gravel::Expression rhs, 
                                                           const Gravel::BinaryExpressionType binop) : 
lhs(lhs), rhs(rhs), binop(binop) { 
    
 
    Gravel::Context * ctx = Context::getInstance();
    
    if (ctx->isOwned(lhs) && ctx->isOwned(rhs)) { 
        if (ctx->owner(lhs) != ctx->owner(rhs)) {
            // throw InvalidExpressionException
        }
    }
      
    boost::shared_ptr<Gravel::GraphNode> lnode = boost::shared_ptr<Gravel::GraphNode>(new Gravel::GraphNode());
    nodes.insert(Gravel::GraphNode::NodePair(Gravel::Input, lnode));
    boost::shared_ptr<Gravel::GraphNode> rnode = boost::shared_ptr<Gravel::GraphNode>(new Gravel::GraphNode());
    nodes.insert(Gravel::GraphNode::NodePair(Gravel::Input, rnode));
    boost::shared_ptr<Gravel::GraphNode> onode = boost::shared_ptr<Gravel::GraphNode>(new Gravel::GraphNode());
    nodes.insert(Gravel::GraphNode::NodePair(Gravel::Output, rnode));
    
    
    
    GraphNode::connect(rnode, rhs.getOutput());
    GraphNode::connect(lnode, lhs.getOutput());
    
    Gravel::Expression temp = Gravel::TemporarySymbol() ;
    
    GraphNode::ConstNodeRange nr = temp.getInputs();
    for (GraphNode::ConstNodeIterator ni = nr.first ; ni != nr.second ; ni++) {
        GraphNode::connect(onode, Gravel::GraphNode::NodePtr(ni->second));
    }
    ctx->normalize();
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

Gravel::GraphNode::NodePtr Gravel::Expression::getOutput() const { 
      return ptr->getOutput();
  }

void Gravel::Expression::setWidth(Gravel::GraphNode::NodePtr node, unsigned width) {
     return ptr->setWidth(node, width); 
}

 Gravel::GraphNode::ConstNodeRange Gravel::Expression::getInputs() const {
      return ptr->getInputs();
 }

 Gravel::Expression::Expression(int) {
     
 } // promotion of int, creates constant and registers termExpression
 
 Gravel::Expression::Expression(const Gravel::Pointer::Expression e) : ptr(e) {
     
 }
 
Gravel::Expression Gravel::operator*(const Gravel::Expression& lhs, const Gravel::Expression& rhs)   { 
    
    Gravel::Pointer::Expression ptr(new Gravel::Implementation::BinaryExpression(lhs,rhs, Gravel::Multiply));
    
  //  GraphNode::setParents(ptr);
            
    return Gravel::Expression(ptr);
}

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

      Gravel::Symbol tmp = this->getOutput();
      Gravel::Symbol lhs = lhs.getOutput();
      Gravel::Symbol rhs = rhs.getOutput();
      
        os << "assign" << " " << tmp << "=" << lhs << " ";
        
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
  
  