
#include <potholes/codegen/Definitions.h>

namespace PG =  Potholes::Generator;

void free_clast_seq(struct clast_stmt *);

static const struct clast_stmt_op stmt_seq = { free_clast_seq };

void free_clast_seq(struct clast_stmt *s)
{
    struct clast_seq *f = (struct clast_seq *)s;
    assert(CLAST_STMT_IS_A(s, stmt_seq));
    free(f);
}



Potholes::Generator::clast_stmt_type Potholes::Generator::find_type(clast_stmt * s) {
 
  if (CLAST_STMT_IS_A(s, stmt_root)) return PG::stmt_root_t;
  if (CLAST_STMT_IS_A(s, stmt_ass)) return PG::stmt_ass_t;
  if (CLAST_STMT_IS_A(s, stmt_for)) return PG::stmt_for_t;
  if (CLAST_STMT_IS_A(s, stmt_guard)) return PG::stmt_guard_t;
  if (CLAST_STMT_IS_A(s, stmt_user)) return PG::stmt_user_t; 
  if (CLAST_STMT_IS_A(s, stmt_seq)) return PG::stmt_seq_t;
  return PG::other_t;
}

void Potholes::Generator::init_interval(PG::interval & interval) { 
    mpz_init(interval.first);
    mpz_init(interval.second);
    
}