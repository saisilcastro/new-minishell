NAME = minishell
VPATH = src: ./src src: ./src/builtin src: ./src/command src: ./src/variable
OBJ = obj
BUILTIN = echo.c cd.c pwd.c export.c unset.c env.c exit.c
COMMAND = command.c command-break.c command-parse.c command-expand.c
VARIABLE = variable.c variable-change.c variable-tree.c variable-show.c variable-pop.c
SRC = 	main.c minishell.c minishell-signal.c minishell-execute.c minishell-pop.c $(COMMAND) \
		util.c $(VARIABLE) $(BUILTIN)
INCLUDE = -I./include
SRCOBJ = $(SRC:%.c=${OBJ}/%.o)
CREATE = mkdir -p ${1}
REMOVE = rm -rf $(1)
CC = gcc
LIB = -lreadline

all: ${NAME}
${NAME} : ${SRCOBJ}
	@$(CC) $^ $(LIB) -o ${NAME}
	@echo "done"
${OBJ}/%.o : %.c
	@$(call CREATE,${OBJ})
	@$(CC) -c $< -o $@ $(INCLUDE)
clean:
	@$(call REMOVE,${OBJ})
fclean: clean
	@$(call REMOVE,${NAME})
re: fclean all
leak:
	@valgrind --leak-check=full -q ./$(NAME) -fanalyzer e -fsanitize=address