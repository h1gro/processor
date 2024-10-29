all: assembler

#linux flags
flag = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

#--------------------------------------------------------------------------------------------------------------------------

#run assembler
assembler: assembler # remove clean from building

assembler: assembler.o StructAssmC_Dtor.o label_table.o CompileCommands.o
	g++ assembler.o StructAssmC_Dtor.o label_table.o CompileCommands.o $(flag) -o assembler

assembler.o: assembler.cpp
	g++ -c $(flag) assembler.cpp

StructAssmC_Dtor.o: StructAssmC_Dtor.cpp
	g++ -c $(flag) StructAssmC_Dtor.cpp

label_table.o: label_table.cpp
	g++ -c $(flag) label_table.cpp

CompileCommands.o: CompileCommands.cpp
	g++ -c $(flag) CompileCommands.cpp

#--------------------------------------------------------------------------------------------------------------------------

#clean
clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp
