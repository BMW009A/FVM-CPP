if(EXISTS "C:/Users/QCZ/CLionProjects/Project-02-FVM/build/test_pcg[1]_tests.cmake")
  include("C:/Users/QCZ/CLionProjects/Project-02-FVM/build/test_pcg[1]_tests.cmake")
else()
  add_test(test_pcg_NOT_BUILT test_pcg_NOT_BUILT)
endif()
