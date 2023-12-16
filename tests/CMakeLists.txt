set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
# find_package(MPFR 2.3.0 REQUIRED) # 高精度 Float计算库

macro (add_test_Float _name)
	add_executable(${_name}-Float "test_float_${_name}.cpp")
    target_link_libraries(${_name}-Float SCI-TLM) 
endmacro()

macro (add_test_Ring _name)
	add_executable(${_name}-Ring "test_ring_${_name}.cpp")
    target_link_libraries(${_name}-Ring SCI-TLM) 
endmacro()
 

macro (add_test_Cleartext _name)
	add_executable(${_name}-Cleartext "test_cleartext_${_name}.cpp")
    target_link_libraries(${_name}-Cleartext SCI-TLM) 
endmacro()

macro (add_test_HE _name)
    add_executable(${_name}-HE "test_field_${_name}.cpp")
    target_link_libraries(${_name}-HE SCI-HE) 
endmacro()


add_test_Ring(truncation) #
add_test_Ring(beaver)
add_test_Cleartext(math)