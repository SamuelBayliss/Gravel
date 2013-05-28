/* 
 * File:   Definitions.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 12:31 PM
 */

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <cloog/cloog.h>
#include <utility>
 struct  clast_seq {
  struct clast_stmt stmt;
  clast_stmt * next;
};


namespace Potholes { 

    namespace Generator { 
   
        typedef enum {C, Verilog} Target_t;
        
        typedef enum 
        {
        stmt_ass_t,
        stmt_for_t, 
        stmt_root_t,
        stmt_guard_t,
        stmt_user_t,
        stmt_seq_t,
        stmt_null_t,
        other_t
        } clast_stmt_type;
        
         clast_stmt_type find_type(clast_stmt * s);
    //   extern const struct clast_stmt_op stmt_seq;
       clast_stmt_type find_type(clast_stmt * s);
       
       typedef std::pair<cloog_int_t, cloog_int_t> interval;
       typedef std::pair<clast_expr *, clast_expr *> interval_expressions;
       
       void init_interval(Potholes::Generator::interval & interval);
       
    };
    
   
};



#endif	/* DEFINITIONS_H */

