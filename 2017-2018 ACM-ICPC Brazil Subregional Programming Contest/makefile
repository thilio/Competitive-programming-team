# Makefile 
########################################################################

STD = -std=c++17

OP1 = -Wall -Wextra -Wpedantic -Wshadow

OP2 = -Wno-unused-result -Wno-unused-function

OP3 = -Wfloat-equal -Wconversion -Wshift-overflow=2 -Wlogical-op

# para GCC >=4.8
SAN = -fsanitize=address -fsanitize=undefined -fno-sanitize-recover

#STL = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2

## otimização
# OPTM = -O0
OPTM = -O2

#GDB = -g

.FORCE :

default : 
	@echo "Para compilar prog.c diga make prog"
	@echo ""

% : %.cpp .FORCE
	@echo "-------"
	g++ $(STD) $(OP1) $(OP2) $(OP3) $(SAN) $(OPTM) $(STL) $(GDB) $< -o $@
	@echo "-------"
	@echo ""

