#*******************************  VARIABLES  **********************************#

NAME			=	interfaceAndRecap

# --------------- FILES --------------- #

LIST_SRC		=	main.cpp		\
					Ice.cpp			\
					AMateria.cpp	\
					utils.cpp \
					Character.cpp	\
					Cure.cpp		\
					MateriaSource.cpp

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_SRC 		=	./
DIR_INCLUDE		=	./

# ------------- SHORTCUTS ------------- #

OBJ				=	$(patsubst %.cpp, $(DIR_BUILD)%.o, $(SRC))
DEP				=	$(patsubst %.cpp, $(DIR_BUILD)%.d, $(SRC))
SRC				=	$(addprefix $(DIR_SRC),$(LIST_SRC))

# ------------ COMPILATION ------------ #

CPPFLAGS		=	-Wall -Wextra -Werror -std=c++98

DEP_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

#***********************************  RULES  **********************************#

.PHONY: all
all:			$(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		$(OBJ)
				$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJ)

# ---------- COMPILED RULES ----------- #

-include $(DEP)

$(DIR_BUILD)%.o: %.cpp
				mkdir -p $(shell dirname $@)
				$(CXX) $(CPPFLAGS) $(DEP_FLAGS) -I $(DIR_INCLUDE) -c $< -o $@

.PHONY: clean
clean:
				$(RM) $(DIR_BUILD)

.PHONY: fclean
fclean: clean
				$(RM) $(NAME)

.PHONY: re
re:				fclean
				$(MAKE) all
