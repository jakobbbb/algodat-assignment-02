#add_executable(helloworld
#    helloworld.cpp
#    )

add_executable(run
    run.cpp
    bst.cpp
    )
add_executable(tests
    tests.cpp
    bst.cpp
    )

# generate compile_commands.json
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
