add_library(libquant OBJECT
    Dimension.cpp           Dimension.h
                            OrderedDimension.h
                            UnorderedDimension.h
    Calendar.cpp            Calendar.h
    Unit.cpp                Unit.h
                            UnitImpl.h
                            OrderedUnit.h
                            UnorderedUnit.h
    BaseUnit.cpp            BaseUnit.h
    AffineUnit.cpp          AffineUnit.h
    AffineUnitImpl.cpp      AffineUnitImpl.h
    BaseQuantity.cpp        BaseQuantity.h
    Dimensionality.cpp      Dimensionality.h
                            OrderedDimFactor.h
    DimFactor.cpp           DimFactor.h
    )
