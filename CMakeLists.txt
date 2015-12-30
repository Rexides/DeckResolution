cmake_minimum_required (VERSION 3.0)
project (DeckResolution)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_STATIC_RUNTIME OFF) 
FIND_PACKAGE( Boost 1.40 REQUIRED COMPONENTS program_options )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(SRCS main.cpp)

add_executable(DeckResolution ${SRCS})
TARGET_LINK_LIBRARIES( DeckResolution ${Boost_LIBRARIES} )