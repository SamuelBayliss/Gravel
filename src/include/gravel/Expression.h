/* 
 * File:   Expression.h
 * Author: sb1708
 *
 * Created on May 20, 2013, 11:29 AM
 */

#ifndef EXPRESSION_H
#define	EXPRESSION_H


#include <boost/shared_ptr.hpp>


#include <gravel/private/Actor.h>


#include <gravel/Assignment.h>
 

namespace Gravel {

    class Expression;
    
    namespace Implementation { 
        class Symbol;
    };
    
   namespace Pointer {
        typedef boost::shared_ptr<Gravel::Implementation::Symbol> Symbol;
    };
    
      typedef enum RelativeExpressionType {LessThan, MoreThan, Equals, LessThanEquals, MoreThanEquals};
      typedef enum UnaryExpressionType {Negate, Invert, Floor, Ceil};
      typedef enum BinaryExpressionType {Multiply, Add, Sub, XOR};
      typedef enum ReductionExpressionType {Min, Max};
      
    namespace Interface { 
        class Expression : public virtual  Gravel::Interface::Actor { 
        public:
            virtual std::ostream& emit(std::ostream&) const = 0;
            virtual const Gravel::Pointer::Symbol getSymbol() const = 0;     
        };
        
      /*  class TermExpression : public Gravel::Interface::Expression { 
              void register_input_symbol();
        };
        class BinaryExpression : public Gravel::Interface::Expression {
        public:
            Gravel::Expression& getLHS();
            Gravel::Expression& getRHS();
            
            void setLHS(Gravel::Expression&);
            void setRHS(Gravel::Expression&);
            
         
        };
        class UnaryExpression : public Gravel::Interface::Expression { 
            
        };
        
        class RangeExpression : public Gravel::Interface::Expression {
            
        };
        
        class MuxExpression : public Gravel::Interface::Expression { 
            
        };
        
        class ReductionExpression : public Gravel::Interface::Expression { 
           public:
             
        };
        
        class RelativeExpression : public Gravel::Interface::Expression { 
          public:
           
        };
        */
    }
    
    
    
    namespace Implementation { 
         class TermExpression;
         class Expression;
         class BinaryExpression; // Relative Expressions are special cases
         class RangeExpression; // 
         class UnaryExpression;
         class MuxExpression;
         class ReductionExpression;
         class RelativeExpression;
  
    }
   
    namespace Pointer { 
        typedef boost::shared_ptr<Gravel::Actor> Actor; 
        typedef boost::shared_ptr<Gravel::Implementation::Expression> Expression; 
    }
    
    class Expression : public Gravel::Interface::Actor { 
    public:
        Expression(int); // promotion of int, creates constant
        bool operator==(const Gravel::Expression&) const;
        bool operator<(const Gravel::Expression &) const;
        virtual Gravel::Pointer::GraphNode getOutput() const;
        virtual Gravel::Collection::GraphNode getInputs() const;
        void setWidth(Gravel::Pointer::GraphNode, unsigned);
        Expression(const Gravel::Pointer::Expression);
        std::ostream& emit(std::ostream&) const;
        const Gravel::Pointer::Symbol getSymbol() const;
        void setPipelineDepth(unsigned);
        static bool Owned(const Gravel::Expression& e);
        Gravel::Module getOwner() const;
        void attach(const Gravel::Pointer::Module&) const;
        ~Expression();
        friend Gravel::Assignment Assignment::Create(const Gravel::Symbol&, const Gravel::Expression&, unsigned delay);
    private : 
        Gravel::Pointer::Expression ptr;
    };
       
    class RelativeExpression : public Expression { 
    public:
             RelativeExpression(const Gravel::Pointer::Expression);
    };
    
  /*  class TermExpression : public Gravel::Expression, public Gravel::Interface::TermExpression {
    public: 
        TermExpression(const Gravel::Symbol);
        
    private:
        Gravel::Pointer::TermExpression ptr;
 
    };
    
    class BinaryExpression :  public Gravel::Expression, public Gravel::Interface::BinaryExpression { 
    public:  
        BinaryExpression(const Gravel::Expression& a, const Gravel::Expression& b, const Gravel::BinaryExpression::BinaryExpressionType& );
     
        const Gravel::Expression& getLHS();
        const Gravel::Expression& getRHS();
            
    private : 
        Gravel::Pointer::BinaryExpression ptr;    
    };
    */
    
    /*template<class N, class NextExpressionType > 
    struct List { 
        typedef N type;
        typedef NextExpressionType nxt;
    };
    
    struct Nil{};
    
    typedef List<
        TermExpression, List< 
        BinaryExpression, Nil> > TypeList;
    
    
    template <class L>
   */ 
   
    
    // use template metaprogramming to get over the "Single transformation per variable" limitation
    
    Gravel::Expression operator*(const Gravel::Expression&, const Gravel::Expression&);
    
    Gravel::Expression operator+(const Gravel::Expression&, const Gravel::Expression&);
    
    
    std::ostream& operator<<(std::ostream& os, const Gravel::Expression& expression);
    
    Gravel::RelativeExpression operator==(const Gravel::Symbol&, const Gravel::Expression&);
   // Gravel::RelativeExpression operator==(const Gravel::Symbol&, const Gravel::Constant&);
    
    
    /* Symbols implicitly turned into TermExpressions or Constants implicitly turned into TermExpressions*/
    
    
    
}

#endif	/* EXPRESSION_H */

