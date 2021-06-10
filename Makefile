##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile <3
##

NAME		=	42sh

CC		=	cc

CFLAGS		+=	-Wall -Wextra -I inc/ -g

SRCS_PREFIX	=	src/

FILES		=	lib.c 					\
			init.c 					\
			debug.c 				\
			strings.c				\
			mysh_loop.c 				\
			format_cmd.c 				\
			replace_line_values.c			\
			str_to_word_tab.c 			\
			format_cmd_utils.c 			\
			exec/my_fork.c 				\
			exec/prep_exec.c 			\
			exec/exec_tools.c 			\
			exec/get_exec_path.c 			\
			exec/get_child_exit_status.c 		\
			built_in/my_if.c 			\
			built_in/my_cd.c 			\
			built_in/my_setprompt.c 		\
			built_in/my_env.c 			\
			built_in/my_exit.c 			\
			built_in/my_setenv.c 			\
			built_in/my_unsetenv.c 			\
			built_in/my_alias.c			\
			built_in/my_which.c			\
			built_in/my_where.c			\
			built_in/my_repeat.c			\
			built_in/main_built_in.c 		\
			built_in/my_exec_parenthesis.c 		\
			history/clean_str.c			\
			history/replace_var.c			\
			history/history.c			\
			history/int_to_str.c			\
			history/alias_complete.c		\
			history/replace_history.c		\
			history/replace_history_number.c	\
			lexer/lexer.c				\
			lexer/lexer_tools.c			\
			lexer/add_char_to_lexer.c		\
			parseur/redirs.c			\
			parseur/parseur.c			\
			parseur/process_tools.c			\
			readline/readline.c			\
			readline/get_key_readline.c		\
			readline/move_cursor_struct.c		\
			readline/verify_cursor_struct.c		\
			readline/create_result_readline.c	\

MAIN		=	$(addprefix $(SRCS_PREFIX), main.c)

SRCS		=	$(addprefix $(SRCS_PREFIX), $(FILES))

OBJ		=	$(MAIN:.c=.o) $(SRCS:.c=.o)

OBJ_T		=	$(SRCS:.c=.o) $(TESTS:.c=.o)

all:			$(NAME)


.PHONY: fclean clean all re tests_run

# sed 0 by 1 -> bold
RED		=	\033[0;31m
GREEN		=	\033[0;32m
NC		=	\033[0m
GREY		=	\033[90m
BLUE		=	\033[0;94m
PURPLE		=	\033[0;95m
BG_COLOR	=	\033[46m####\033[m
IRED		=	\033[0;91m

ifndef VERBOSE
	MAKEFLAGS += --no-print-directory
endif

$(NAME):	$(OBJ)
	@echo -e '${NC}${BG_COLOR}Libs: $(LDFLAGS)${NC}'
	@echo -e '${BG_COLOR}Flags: $(CFLAGS)${NC}'
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) 2>>errors_build.txt\
		&& echo -e '${BLUE}Create${NC}: ${GREY}./$(NAME)${NC}'\
		|| echo -e '${RED}[ FAILED ]${NC}: __Create__${GREY} ./$(NAME)${NC}'

%.o:		%.c
	@-$(CC) -o $@ -c $< $(CFLAGS) 2>>errors_build.txt\
		&& echo -e '${GREEN} [ OK ]${NC} Build $<'\
		|| echo -e '${RED}[ FAILED ]${NC} __Build__ $<'\
		&& echo -ne '${PURPLE}' && grep  $< errors_build.txt |\
		grep warning |cut -d':' -f2- |cut -d'[' -f-1\
		&& echo -ne '${IRED}' && grep  $< errors_build.txt |\
		grep error |cut -d':' -f2-\
		||:

need:		$(OBJ)
	@make && echo "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu" | ./42sh

debug:	clean
	$(eval CFLAGS += -D DEBUG)
	$(MAKE)

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_T)
	@rm -rf vgcore.*
	@rm -f gmon.out
	@rm -rf a.out
	@find . -name *.gc* -delete
	@rm -f errors_build.txt
	@echo -e '${BLUE}Clean${NC} : OK'

fclean:		clean
	@rm -rf errors_build.txt 2>/dev/null
	@rm -rf $(NAME)
	@echo -e '${BLUE}Fclean${NC}: ./$(NAME) removed'

re:	fclean all
