set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
# find_package(MPFR 2.3.0 REQUIRED) # 高精度 Float计算库

macro (add_test_TLM _name)
	add_executable(${_name}-TLM "test_ring_${_name}.cpp")
    target_link_libraries(${_name}-TLM SCI-TLM) 
endmacro()

macro (add_test_HE _name)
    add_executable(${_name}-HE "test_field_${_name}.cpp")
    target_link_libraries(${_name}-HE SCI-HE) 
endmacro()


add_test_TLM(truncation) #