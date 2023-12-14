add_library(SCI-FixedPoint fixed-point.cpp bool-data.cpp)
target_link_libraries(SCI-FixedPoint
    PUBLIC SCI-BuildingBlocks SCI-Math
)
