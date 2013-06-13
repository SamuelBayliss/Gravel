/* 
 * File:   SeqModule.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 12:06 PM
 */

#ifndef SEQMODULE_H
#define	SEQMODULE_H


#include <gravel/Expression.h>

#include <potholes/codegen/Module.h>



namespace Potholes { 
    
    class BoundExpression : public Gravel::Expression { 
    public:
        BoundExpression(clast_expr *);
    };
    
    namespace Generator { 
        class ForModule : public Potholes::Generator::Module { 
        public:
            ForModule(clast_stmt *);
            void register_symbols();
            void build_chain();
        private:
            clast_for * for_stmt;
            Gravel::Symbol fill_counter;
            Potholes::BoundExpression upper_bound;
            Potholes::BoundExpression lower_bound;
        };

    }

};

#endif	/* SEQMODULE_H */

