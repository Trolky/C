# Pojďme si zjistit velikost našich zásobníků.
add_executable(stack_size
    stack_size.c
)

# Můžem vypnout warning upozoňující na nekonečnou rekurzi -- to ovšem nikdy dělat nechceme!
if (CMAKE_C_COMPILER_ID STREQUAL "GNU") # pro GCC překladač (u jiných překladačů budou jiné přepínače)
    set_target_properties(stack_size PROPERTIES COMPILE_FLAGS "-Wno-infinite-recursion")
endif()

# Požádáme CMake, aby nám k cíly `stack_size` vygeneroval i její assembly kód.
# pro GCC překladač (u jiných překladačů budou jiné přepínače)
if (CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(STACK_ASSEMBLY_COMPILER_FLAGS "-O3")
endif()

add_custom_target(stack_size_assembly
    COMMAND ${CMAKE_C_COMPILER} ${STACK_ASSEMBLY_COMPILER_FLAGS} -S stack_size.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating assembly code from stack_size.c"
    VERBATIM
)
# přidáme assembly jako závislost pro `stack_size` cíl. Assembly bude tedy vždy vygenerováno.
add_dependencies(stack_size stack_size_assembly)
