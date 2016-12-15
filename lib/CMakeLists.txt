include_directories (${ptabenevalaa_SOURCE_DIR}/include)

set (ptabenevalaaSourceCodes
  PTABenEvalAAPass.cpp
)
add_library (ptabenevalaaObj OBJECT ${ptabenevalaaSourceCodes})
add_library (ptabenevalaa SHARED $<TARGET_OBJECTS:ptabenevalaaObj>)
add_library (ptabenevalaaStatic STATIC $<TARGET_OBJECTS:ptabenevalaaObj>)
target_link_libraries (ptabenevalaaStatic LLVMCore LLVMSupport)