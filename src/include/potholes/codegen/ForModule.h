/* 
 * File:   SeqModule.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 12:06 PM
 */

#ifndef SEQMODULE_H
#define	SEQMODULE_H

#include <potholes/codegen/Module.h>

namespace Potholes { 
    namespace Generator { 
        class ForModule : public Potholes::Generator::Module { 
        public:
            ForModule(clast_stmt *);
            void register_symbols();
            void build_chain();
        };

    }

};

#endif	/* SEQMODULE_H */

