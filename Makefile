all: assembler processor clean

#windows flags
#flag = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

#linux flags
flag = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

#--------------------------------------------------------------------------------------#

#run assembler
assembler: assembler

assembler: assembler.o StrFilesC_Dtor.o
	g++ assembler.o StrFilesC_Dtor.o $(flag) -o assembler

assembler.o: assembler.cpp
	g++ -c $(flag) assembler.cpp

StrFilesC_Dtor.o: StrFilesC_Dtor.cpp
	g++ -c $(flag) StrFilesC_Dtor.cpp

#--------------------------------------------------------------------------------------#

#run processor
processor: processor

processor: processor.o stackfuncs.o SpuC_Dtor.o ReadByteFile.o C_Dtors.o
	g++ processor.o stackfuncs.o SpuC_Dtor.o ReadByteFile.o C_Dtors.o $(flag) -o processor

processor.o: processor.cpp
	g++ -c $(flag) processor.cpp

stackfuncs.o: stackfuncs.cpp
	g++ -c $(flag) stackfuncs.cpp

SpuC_Dtor.o: SpuC_Dtor.cpp
	g++ -c $(flag) SpuC_Dtor.cpp

ReadByteFile.o: ReadByteFile.cpp
	g++ -c $(flag) ReadByteFile.cpp

C_Dtors.o: C_Dtors.cpp
	g++ -c $(flag) C_Dtors.cpp
	
#--------------------------------------------------------------------------------------#

#clean
clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp
