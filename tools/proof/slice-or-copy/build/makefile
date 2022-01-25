# 
# author        Oliver Blaser
# date          25.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser
# 

cxx = g++
link = g++

cflags = -c -Wall -Wextra -pedantic
lflags = -Wall -Wextra -pedantic

objs = main.o
exe = slice-or-copy

$(exe): $(objs)
	$(link) $(lflags) -o $(exe) $(objs)

main.o: ../main.cpp
	$(cxx) $(cflags) ../main.cpp

run: $(exe)
	@echo ""
	@echo "--================# run #================--"
	@./$(exe)

clean:
	@rm $(objs)
	@rm $(exe)
