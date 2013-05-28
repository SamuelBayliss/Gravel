/* 
 * File:   Symbol.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 4:53 PM
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <gravel/Object.h>


#include <map>

#include "private/Actor.h"
namespace Gravel { 
    
    class Expression;
    class TermExpression;
    class BinaryExpression;
    
    class Module;
   
    namespace Pointer{
        
    }
    
    namespace Implementation {
        class Symbol;
        class Constant;
    }

    namespace Interface { 
        class Symbol : public virtual Gravel::Interface::Actor { 
        
        public : 
            typedef enum Direction {Input, Output, Local};
            typedef enum Type {Wire, Reg};
            
            virtual const std::string getName() const = 0;
            virtual Type getType() const = 0;
        protected:
            
        };
    };
    
    
    
    typedef boost::shared_ptr<Gravel::Implementation::Symbol> SymbolPtr;
    
  class Constant  {
      
  };
  
  class SymbolNotFoundException : std::exception { 
      
  };
  
  
  
    class Symbol : public Interface::Symbol { 
    private : 
        SymbolPtr symbol;
    protected : 
        Symbol();
        
      
    public : 
       Symbol(const std::string&);
        Symbol(boost::weak_ptr<Gravel::GraphNode>);
       const std::string getName() const;
         Interface::Symbol::Type getType() const;
       static unsigned getSymbolWidth(const Gravel::Symbol&);
       bool operator==(const Gravel::Symbol&) const;
        operator Gravel::Expression();
  
         GraphNode::NodePtr getOutput() const;
        GraphNode::ConstNodeRange getInputs() const;
        void setWidth(Gravel::GraphNode::NodePtr, unsigned);
        
       Gravel::Symbol operator=(const Gravel::Expression&);
       bool operator<(const Gravel::Symbol&) const;
       
       
    };
 
    class TemporarySymbol : public Gravel::Symbol { 
    public:
        TemporarySymbol();
    };
    
    class SymbolDeclaration {
    public:
        SymbolDeclaration(const Gravel::Symbol&);
             //   SymbolInterface::Type getType() const ;
        //const std::string getName() const;
        const Gravel::Symbol getSymbol() const;
    private:
        Gravel::Symbol symbol;
        
    };
    
    typedef std::pair<Gravel::Module, Gravel::Symbol::Direction> SymbolKey;
    typedef std::multimap<SymbolKey, Gravel::Symbol> SymbolMap;
    typedef std::multimap<SymbolKey, Gravel::Symbol>::const_iterator ConstSymbolMapIterator;
    std::ostream& operator<< (std::ostream& os, const Gravel::Symbol& s);
    std::ostream& operator<< (std::ostream& os, const Gravel::SymbolDeclaration& s);
    
    
    
};

#endif	/* SYMBOL_H */

