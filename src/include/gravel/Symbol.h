/* 
 * File:   Symbol.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 4:53 PM
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <map>
#include <set>

#include <boost/shared_ptr.hpp>



namespace Gravel { 
    
    class Expression;
    class TermExpression;
    class BinaryExpression;
    class Module;
    class Assignment;
    class Symbol;
   
    
    namespace Implementation {
        class Symbol;
        class Constant;
    };

     namespace Pointer{
        typedef boost::shared_ptr<Gravel::Implementation::Symbol> Symbol;
        typedef boost::shared_ptr<Gravel::Implementation::Constant> Constant;
    };
    
     namespace Collection { 
        typedef std::set<Gravel::Pointer::Symbol> Symbol;
    };
    
    
};

    #include <gravel/private/Actor.h>
    #include <gravel/Assignment.h>

namespace Gravel { 

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
    
     
  
     
    



namespace Implementation { 
  class Constant : public virtual Gravel::Actor {
  public:
      Constant(int);
         Gravel::Pointer::GraphNode getOutput() const;
         GraphNode::ConstNodeRange getInputs() const;
      // set width
         void setWidth(Gravel::Pointer::GraphNode, unsigned);
  protected:
      int value;
  };
  
};
  
  class SymbolNotFoundException : std::exception { 
      
  };
  

  
    class Symbol : public Interface::Symbol, public Interface::ActorHandle { 
    private : 
        Gravel::Pointer::Symbol symbol;
    protected : 
        Symbol();
        
      
    public : 
       Symbol(const std::string&);
        Symbol(Gravel::Pointer::Actor);
        Symbol(Gravel::Pointer::Symbol);
        ~Symbol();
       const std::string getName() const;
         Interface::Symbol::Type getType() const;
           static boost::shared_ptr<Gravel::Symbol> Create(const std::string&);
           
       static unsigned getSymbolWidth(const Gravel::Symbol&);
       
       static bool Owned(const Gravel::Symbol&);    
       
       //static void Attach(const Gravel::Symbol&, const Gravel::Module&, const Gravel::Interface::Symbol::Direction&); 
   
       void attach(const Gravel::Pointer::Module&) const;
       void attach(Gravel::Pointer::Module&, const Gravel::Interface::Symbol::Direction&) const ;
       Gravel::Module getOwner() const;
       
       bool operator==(const Gravel::Symbol&) const;
        operator const Gravel::Expression() const;
  
         Gravel::Pointer::GraphNode getOutput() const;
        GraphNode::ConstNodeRange getInputs() const;
        void setWidth(Gravel::Pointer::GraphNode, unsigned);
        
       Gravel::Assignment operator=(const Gravel::Expression&);
       bool operator<(const Gravel::Symbol&) const;
       
       friend Gravel::Assignment Assignment::Create(const Gravel::Symbol&, const Gravel::Expression&, unsigned delay);
    };
 
   class RegisteredSymbol : public Gravel::Symbol {
 
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
    
    typedef std::pair<Gravel::Pointer::Module, Gravel::Pointer::Symbol> SymbolKey;
    typedef std::multimap<SymbolKey, Gravel::Symbol::Direction> SymbolMap;

    
    typedef std::set<Gravel::Symbol> SymbolSet;
 
    typedef SymbolMap::const_iterator ConstSymbolMapIterator;
    std::ostream& operator<< (std::ostream& os, const Gravel::Symbol& s);
    std::ostream& operator<< (std::ostream& os, const Gravel::SymbolDeclaration& s);
    
    
    
};


#endif	/* SYMBOL_H */

