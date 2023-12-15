add_library(SCI-FloatPoint fp-math.cpp floating-point.cpp)
target_link_libraries(SCI-FloatPoint
    PUBLIC SCI-BuildingBlocks SCI-Math SCI-FixedPoint
)
