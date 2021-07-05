# Makefile  BOCA 2016
########################################################################

FLAGS = -std=c++11 -static -O2 -lm

.FORCE :

default : 
	@echo "Para compilar prog.c diga make prog"
	@echo ""

% : %.cpp .FORCE
	@echo "-------"
	g++ $(FLAGS) $< -o $@
	@echo "-------"
	@echo ""

