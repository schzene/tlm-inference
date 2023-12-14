add_library(SCI-LinearBeaver linear-beaver.cpp)

target_link_libraries(SCI-LinearBeaver 
            PUBLIC
            SCI-utils
            Eigen3::Eigen
)