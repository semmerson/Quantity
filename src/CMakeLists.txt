add_library(libquant OBJECT
    Dimension.cpp           Dimension.h
    Calendar.cpp            Calendar.h
    Unit.cpp                Unit.h
                            OrderedUnit.h
                            UnorderedUnit.h
    BaseUnit.cpp            BaseUnit.h
    DerivedUnit.cpp         DerivedUnit.h
    AffineUnit.cpp          AffineUnit.h
    Exponent.cpp            Exponent.h
    )
