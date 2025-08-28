add_library(libquant OBJECT
    Dimension.cpp           Dimension.h
                            OrderedDimension.h
                            UnorderedDimension.h
    Calendar.cpp            Calendar.h
    Unit.cpp                Unit.h
    UnitImpl.cpp            UnitImpl.h
                            OrderedUnit.h
                            UnorderedUnit.h
    BaseQuantity.cpp        BaseQuantity.h
    Dimensionality.cpp      Dimensionality.h
    DimFactor.cpp           DimFactor.h
                            OrderedDimFactor.h
    Exponent.cpp            Exponent.h
                            UnitFactor.h
    )
