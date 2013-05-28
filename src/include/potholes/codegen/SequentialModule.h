/* 
 * File:   SeqModule.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 12:06 PM
 */

#ifndef FORMODULE_H
#define	FORMODULE_H

#include <potholes/codegen/Module.h>

namespace Potholes { 
    namespace Generator { 
        class SequentialModule : public Potholes::Generator::Module { 
        public:
            SequentialModule(clast_stmt *);
            void register_symbols();
            void build_chain();
        };

    };

};

#endif	/* SEQMODULE_H */

