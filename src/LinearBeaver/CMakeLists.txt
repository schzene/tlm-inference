add_library(SCI-LinearBeaver INTERFACE)

target_link_libraries(SCI-LinearBeaver INTERFACE
            SCI-utils
            Eigen3::Eigen
)
