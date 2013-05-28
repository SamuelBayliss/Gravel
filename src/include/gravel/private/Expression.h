
#include <gravel/Expression.h>

#include <gravel/Symbol.h>

namespace Gravel { 
    

    namespace Implementation { 
        
        typedef std::map<Gravel::Constant, Gravel::Symbol> MuxInputMapping;
        
        class Expression : public virtual Gravel::Interface::Expression { 
              virtual const Gravel::Symbol getSymbol();
              void setPipelineDepth(unsigned);
        };
        
        class MuxExpression : public virtual Gravel::Actor , public Gravel::Implementation::Expression { 
        public:
            MuxExpression(Gravel::Symbol sym);
            std::ostream& emit(std::ostream& ) const;
        private:
            MuxInputMapping mim;
        };
        
        class TermExpression : public virtual Gravel::Actor, public Gravel::Implementation::Expression { 
        public:
                TermExpression(Gravel::Symbol sym);
                std::ostream& emit(std::ostream&) const;
                const Gravel::Symbol getSymbol();
                
        private:
            const Gravel::Symbol symbol;
        };
        
        class BinaryExpression : public virtual Gravel::Actor, public Gravel::Implementation::Expression { 
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