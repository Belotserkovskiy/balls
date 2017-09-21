SOURCES += ../googletest/googlemock/src/gmock_main.cc \ # to gmock_main.cc

INCLUDEPATH += \
               ../googletest/googletest/include \  # to gtets and gmain
               ../googletest/googlemock/include \
               ../../ \                            # to project directory


LIBS += C:\qtprojects\balls\tests\googletest\lib\libgmock.a \   # to compailed gmock library
        C:\qtprojects\balls\tests\googletest\lib\libgmock_main.a \
