

set (GRAVEL_SRC Context Module Object Symbol)
set (CODEGEN_SRC codegen/Generator
        codegen/Definitions
        codegen/SequentialModule
        codegen/AssignmentModule
        codegen/GuardModule 
        codegen/ForModule
        codegen/CodegenModule)


add_library(gravel ${GRAVEL_SRC} ${CODEGEN_SRC})
target_link_libraries(gravel ${CLOOG_LIBRARY})
target_link_libraries(gravel ${OSL_LIBRARY})
target_link_libraries(gravel ${GMP_LIBRARY})