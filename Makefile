NAME = minishell
VPATH = src: ./src src: ./src/builtin src: ./src/command src: ./src/process src: ./src/variable
OBJ = obj
BUILTIN = echo.c cd.c pwd.c export.c unset.c env.c exit.c
COMMAND = command.c command-select.c command-break.c command-apostrophe.c command-quote.c command-normal.c command-special.c command-parse.c command-pop.c
VARIABLE = variable.c variable-property.c variable-change.c variable-tree.c variable-show.c variable-pop.c
PROCESS = process.c
SRC = 	main.c minishell.c minishell-string.c minishell-signal.c minishell-execute.c minishell-pop.c util.c \
		$(COMMAND) $(PROCESS) $(VARIABLE) $(BUILTIN)
INCLUDE = -I./include
SRCOBJ = $(SRC:%.c=${OBJ}/%.o)
CREATE = mkdir -p ${1}
REMOVE = rm -rf $(1)
CC = gcc
LIB = -lreadline

PURPLE = \033[1;35m

all: ${NAME}
${NAME} : ${SRCOBJ}
	@$(CC) $^ $(LIB) -o ${NAME}
	@printf "\nThe Makefile of [$(PURPLE)MINISHELL\033[0m] has been compiled!🐚\n"
${OBJ}/%.o : %.c
	@$(call CREATE,${OBJ})
	@printf "\rMinishell: building $@                      "
	@$(CC) -c $< -o $@ $(INCLUDE)
clean:
	@$(call REMOVE,${OBJ})
fclean: clean
	@$(call REMOVE,${NAME})
re: fclean all
leak:
	@valgrind --leak-check=full -q ./$(NAME) -fanalyzer e -fsanitize=address
push:
	git add .
	git commit -m ${NAME}
	git push