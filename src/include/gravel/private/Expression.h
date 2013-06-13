
#include <gravel/Expression.h>

#include <gravel/Symbol.h>
#include <gravel/private/Symbol.h>

namespace Gravel { 
    

    namespace Implementation { 
        
        typedef std::map<Gravel::Implementation::Constant, Gravel::Symbol> MuxInputMapping;
        
        
        
        class Expression :  public virtual Gravel::Actor, public virtual Gravel::Interface::Expression { 
        public:
              virtual const Gravel::Pointer::Symbol getSymbol() const ;
              void setPipelineDepth(unsigned);
        };
        
        class NullExpression : public Gravel::Implementation::Expression { 
             public:
                 NullExpression();
              std::ostream& emit(std::ostream&) const;
        };
        
        class RelativeExpression :  public Gravel::Implementation::Expression {
        public : 
        RelativeExpression(const Gravel::Expression, const Gravel::Expression, const Gravel::RelativeExpressionType);
           std::ostream& emit(std::ostream& ) const;
        };
        
        class MuxExpression :  public Gravel::Implementation::Expression { 
        public:
            MuxExpression(Gravel::Symbol sym);
            std::ostream& emit(std::ostream& ) const;
        private:
            MuxInputMapping mim;
        };
        
        class TermExpression :  public Gravel::Implementation::Expression { 
        public:
                TermExpression(Gravel::Pointer::Symbol);
                TermExpression(Gravel::Pointer::Constant);
                std::ostream& emit(std::ostream&) const;
                const Gravel::Pointer::Symbol getSymbol() const ; // This is output symbol of term expression
                
        private:
            //const Gravel::Symbol symbol;
        };
        
        class BinaryExpression :  public Gravel::Implementation::Expression { 
        public : 
        const Gravel::Expression& getLHS();
        const Gravel::Expression& getRHS();
        std::ostream& emit(std::ostream& ) const;
       BinaryExpression(const Gravel::Expression, const Gravel::Expression, const Gravel::BinaryExpressionType);
       
        
        private : 
               const Gravel::BinaryExpressionType binop;
               const Gravel::Expression lhs;
               const Gravel::Expression rhs;
        };
        
        
        
    };

    


};