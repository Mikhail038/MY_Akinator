
CXX_FLAGS = -D _DEBUG -g -ggdb3 -std=c++17 -O0

ASSAN = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

DOP = -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE

CXX_FLAGS += $(ASSAN)

DIR_FLAGS = -IAKINATOR -IEXTRA

CXX_FLAGS += $(DIR_FLAGS)

CXX_FLAGS += $(DOP)


DO: DO_AKINATOR

DO_AKINATOR: OBJECTS OBJECTS/akinator.o OBJECTS/main_akinator.o
	g++ OBJECTS/akinator.o OBJECTS/main_akinator.o -o akinator $(CXX_FLAGS)

OBJECTS/akinator.o: AKINATOR/akinator.cpp
	g++ -c -o  OBJECTS/akinator.o AKINATOR/akinator.cpp $(CXX_FLAGS)

OBJECTS/main_akinator.o: AKINATOR/main_akinator.cpp
	g++ -c -o OBJECTS/main_akinator.o AKINATOR/main_akinator.cpp $(CXX_FLAGS)

OBJECTS:
	mkdir -p OBJECTS
