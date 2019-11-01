# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmostafa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/05 17:14:47 by mmostafa          #+#    #+#              #
#    Updated: 2019/08/16 17:53:07 by mmostafa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

LIBSRC = libft/libft.a
LIBPATH = libft/

OBJ = src/termcap/auto_complete.o\
src/termcap/auto_complete_2.o\
src/termcap/auto_special_mash.o\
src/termcap/copy_past.o\
src/termcap/copy_past_2.o\
src/termcap/copy_past_3.o\
src/termcap/copy_past_4.o\
src/termcap/ctrlc_handle.o\
src/termcap/ctrld_handle.o\
src/termcap/edge_and_helping_functions.o\
src/termcap/herdoc_check.o\
src/termcap/home_end_buttons.o\
src/termcap/main_and_list.o\
src/termcap/main_helpers.o\
src/termcap/movements.o\
src/termcap/quote_checker.o\
src/termcap/quote_copy_past.o\
src/termcap/quote_copy_past_2.o\
src/termcap/quote_copy_past_3.o\
src/termcap/quote_home_end.o\
src/termcap/quote_mode.o\
src/termcap/quote_movements.o\
src/termcap/quote_special_moves.o\
src/termcap/read_line.o\
src/termcap/special_moves.o\
src/termcap/string_modifiers.o\
src/termcap/string_modifiers2.o\
src/redirections_and_execution_manager/cleaning.o\
src/redirections_and_execution_manager/deviding_and_gethome.o\
src/redirections_and_execution_manager/executing_manager_fatehrd.o\
src/redirections_and_execution_manager/fill_rlist.o\
src/redirections_and_execution_manager/just_for_thenorme.o\
src/redirections_and_execution_manager/minish.o\
src/redirections_and_execution_manager/minish2.o\
src/redirections_and_execution_manager/minish3.o\
src/redirections_and_execution_manager/minish4.o\
src/redirections_and_execution_manager/minish5.o\
src/redirections_and_execution_manager/minish6.o\
src/redirections_and_execution_manager/minish7.o\
src/redirections_and_execution_manager/preapre_for_redirections.o\
src/redirections_and_execution_manager/qout_hrd.o\
src/redirections_and_execution_manager/redirect_execute_exit.o\
src/redirections_and_execution_manager/some_others_functions.o\
src/redirections_and_execution_manager/start_redirect.o\
src/redirections_and_execution_manager/start_rediret_assist.o\
src/redirections_and_execution_manager/treating_cmd.o\
src/redirections_and_execution_manager/qout_editing.o\
src/redirections_and_execution_manager/check_semi_solum_and_pipe.o

INC = inc/
FLAG = -Wall -Werror -Wextra
TERM_LIB = -ltermcap

all: $(NAME)

$(NAME): $(LIBSRC) $(OBJ)
	gcc $(FLAG) $(OBJ) -I $(INC) $(LIBSRC) $(TERM_LIB) -o $(NAME)

%.o : %.c
	gcc $(FLAG) -I $(INC) -c $< -o $@
$(LIBSRC):
	make -C $(LIBPATH)

clean:
	make clean -C $(LIBPATH)
	/bin/rm -f $(OBJ)
fclean: clean
	make fclean -C $(LIBPATH)
	/bin/rm -f $(NAME)
re: fclean all
