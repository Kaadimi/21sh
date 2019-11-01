/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:58:24 by ikadimi           #+#    #+#             */
/*   Updated: 2019/08/16 18:37:13 by mmostafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include "../libft/libft.h"
# define BUFF_SIZ 4
# define RIGHT (buf[2] == 67 && buf[1] == 91 && buf[0] == 27)
# define LEFT (buf[2] == 68 && buf[1] == 91 && buf[0] == 27)
# define UP (buf[2] == 65 && buf[1] == 91 && buf[0] == 27)
# define DOWN (buf[2] == 66 && buf[1] == 91 && buf[0] == 27)
# define HOME (buf[2] == 72 && buf[1] == 91 && buf[0] == 27)
# define END (buf[2] == 70 && buf[1] == 91 && buf[0] == 27)
# define DEL (buf[0] == 127)
# define COUNT (t->index + t->diff_index)
# define EDGE ((COUNT % tgetnum("co")) == 0 && t->index > 0)
# define MID t->index < ft_intlen(t->str)
# define INSERT (ft_isprint(buf[0]) && MID && t->ret == 1)
# define LINE ((t->index + t->diff_index) / tgetnum("co"))
# define ESC (buf[1] == 27 && buf[0] == 27)
# define PREV_WORD (buf[3] == 68 && buf[2] == 91 && ESC)
# define PREV_LINE (buf[3] == 65 && buf[2] == 91 && ESC)
# define NEXT_LINE (buf[3] == 66 && buf[2] == 91 && ESC)
# define NEXT_WORD (buf[3] == 67 && buf[2] == 91 && ESC)
# define FIN (t->index == ft_intlen(t->str))
# define OUTPUT (ft_isprint(buf[0]) && t->ret == 1 && FIN)

# define CMD                 	0b100000000000000
# define OPR                 	0b10000000000000
# define RUT                 	0b1000000000000
# define RUA                 	0b100000000000
# define HRD                 	0b10000000000
# define RI                  	0b1000000000
# define REU                 	0b100000000
# define DFD_AND_STDIN       	0b10000000
# define RFD_OR_FILE         	0b1000000
# define S_CASE              	0b100000
# define FD_FOR_AFTER_OPR       0b10000
# define FD_FOR_BEFORE_OPR		0b1000
# define OPS_FOR_CMD         	0b100
# define FILE_FOR_OPR			0b10
# define MENAS 	             	0b1

typedef struct			s_pids
{
	int					pid;
	int					wait;
	struct s_pids		*next;
}						t_pids;

typedef struct			s_org
{
	char				*vl;
	short				flags;
	struct s_org		*next;
	struct s_org		*prev;
}						t_org;

typedef struct			s_nodes
{
	char				*n_var;
	char				*content;
	char				sign;
	char				colrs;
	struct s_nodes		*next;
	struct s_nodes		*next2;
}						t_nodes;

typedef struct			s_history
{
	char				*command;
	int					placement;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_materials
{
	char				*coped;
	char				*edited_command;
	char				*hrd_content;
	char				*hrd_content_lite;
	char				*oldpwd;
	char				*tmp;
	char				*av;
	char				*err;
	t_history			*history_head;
	t_history			*added;
	t_nodes				*start;
	t_org				*head;
	t_org				*save;
	t_nodes				*save_env;
	t_list				*list;
	t_pids				*pidnode;
	char				**env;
	char				**env_c;
	char				**test;
	char				**ops_c;
	char				**semi_colum;
	char				**pipe;
	int					is_pipe_exist;
	int					save_ior[3];
	int					pipe_var[2];
	int					save_inpipe;
	int					ops[1];
	pid_t				pid;
}						t_materials;

typedef struct			s_counters
{
	int					actions;
	int					save;
	int					error;
	int					index;
	int					inline_index;
	int					diff_index;
	int					back_up_index;
	int					node_counter;
	char				*str;
	char				*tmp;
	int					ret;
	t_history			*start;
	int					bakara;
	int					quote;
	int					ttyfd;
	int					status;
	char				*copy_str;
	int					herdoc;
	int					autoc;
}						t_counters;

int						g_wait;

int						args_check(char **tmp1);
int						delete_qout_agent(char *vl, int i, char ch);
void					remember_qout_sp(int i, char *res, char mode);
int						verif_pipe(char *cmd);
int						verif_semi_colum(char **semi_colum);
int						check_semi_colum(t_materials *mt);
void					null(t_org **head, char ***ops_c, char **hr,
						char **tmp);
void					repare_env_c(char **env_c);
void					free_rlist(t_org *head);
void					ft_mt_init(t_materials *mt, char **env, char **env_c);
void					free_t(char **ptr);
void					ft_exit(t_materials *mt);
void					str_to_lower(char **str);
char					*find_replace(char *haystack, char *find,
		char *replace);
char					*ft_new_stack(char *haystack, char *replace,
		size_t a, size_t j);
char					*ft_home2(char *cmd);
char					*mini_remove_strinstr(char *str, int size, int start);
void					ft_aff_nodes_assi2(char *content, char *n_var,
		char colrs);
void					ft_aff_nodes_assi(t_nodes *trash);
int						add_var_assi(char **tmp1);
void					ft_go_home(char *oldpwd, char *cwd);
int						ft_go_dir(char **tmp0, char *oldpwd);
int						ft_go_back(char **tmp0, char *cwd, char *oldpwd);
char					*verf_cmd_ass(char *content, char *tmp1, char colrs);
int						search_assist2(char *tmp1, int *in);
char					*search_assi(char **tmp, char *tmp1,
		char **tmp6, int *in);
char					*sar2(char *tmp1, char *tmp2, char *line, int *in);
void					ft_init(int type, int *in, t_nodes *start,
		t_nodes *head);
int						dlr(char *line, char *tmp1, t_nodes *head,
		t_nodes *start);
char					*dollar_agent(int *in, char *line);
void					main2(char *oldpwd, t_nodes **st, char **env,
		t_nodes *he);
char					*d_h(char *line, t_nodes *start);
char					*check_ql_ws(char *line);
char					*ft_get_home(void);
void					ft_cd(char **tmp0, char *oldpwd);
void					repare_env(char **env, char c, char b);
char					*search_in_path2(char *tmp1, char **tmp6);
char					*verf_cmd(char *tmp1, t_nodes *start);
void					ft_echo(char **line);
char					*sar(char *serched, char *replaced,
		char *modified, int k);
char					*verf_var(char *to_find, t_nodes *start);
char					*replace_serched(char *line, int l, int k);
char					*give_serched(char *line, char c,
		t_nodes *star, int *in);
void					ft_replace(char *s1, char c);
char					*ft_strjoin2(char const *s1, char const *s2);
int						find_var(char **tmp1, t_nodes *start);
t_nodes					*add_var_env(t_nodes **start, char **tmp1);
t_nodes					*rm_var_env(t_nodes **start, char **tmp1);
void					out(char **tmp0, t_nodes *head, char *line,
		char *oldpwd);
void					test_s(int i);
char					*read_cmd(int fd);
void					ft_env_add2(t_nodes **start, t_nodes *new);
void					ft_free2(char **tmp1);
t_nodes					*add_var_env(t_nodes **start, char **tmp1);
t_nodes					*ft_aff_nodes(t_nodes *start, int i);
void					ft_free_nodes(t_nodes *start2);
int						t_cmd(char **tmp1, t_nodes **start,
		char *oldpwd, t_materials *mt);
t_nodes					*ft_env_gen(char	**env);
void					ft_env_add(t_nodes **start, t_nodes *new);

char					*get_hrd_content(t_org *head, char **hrd_content);
void					executing_manager(t_materials *mt);
char					**pipe_function(char **cmd);
char					**semi_colum_function(char **full_cmd);
t_org					*ft_fill_list(char **test, int *ops);
char					**ft_ops_collector(t_org *head2, int *ops);
int						redirection_input_hrd(t_org *head, char *hrd_content);
int						redirection_output(t_org *beguin);
int						redirection_input(t_org *head, int fd_after,
		int fd_before);
int						st_minion_for_oprs(t_org *org, t_org *new_org);
int						nd_minion_for_oprs(t_org *org, t_org *new_org);
int						rd_minion_for_oprs(t_org *org, t_org *new_org);
int						th_minion_for_oprs(t_org *org, t_org *new_org);
int						st_minion_for_non_oprs(t_org *org,
		t_org *new_org, int *ops);
void					nd_minion_for_non_oprs(t_org *org,
		t_org *new_org, int *ops);
t_org					*minions_manager(t_org *org, int *ops, char *vl);
int						ignore_quot(char *res, int i);
int						find_index_to_insert_sp(char **res, int i);
int						ft_intlen(char *str);
t_org					*org_function(char *vl, t_org *org, int sign, int *ops);
char					*ft_prepare(char *av);
char					**ft_split(char *res);
char					*ft_strjoin2(char const *s1, char const *s2);
char					*read_cmd(int fd);
int						ft_isnum(char *vl);
int						search_in_str(char *str);
char					*delete_qout(char *vl);
void					find_hrd_content(char *cmd, t_materials *mt);
int						redirect_and_execute(t_materials *mt);
int						redis_assist(t_org *head, char *hrd_content);
int						fd_duplicating1(t_org *beguin, int fd_before);
int						redirecting_input(t_org *head, int fd_after,
		int fd_before);
int						fd_duplicating2(t_org *beguin, int fd_before,
		int fd_after);
int						fd_closing(t_org *beguin, int fd_before,
		int fd_after, int *cls);
void					fd_initializer(t_org *beguin, int *fd_after,
		int *fd_before, int *cls);
void					struct_initialiser(t_counters *t);
int						ft_intlen(char *str);
char					*ft_freejoin(char *s1, char *s2);
int						ft_outc(int c);
char					*index_remover(char *str, int index);
char					*insert_char(char *str, char c, int index);
void					set_input_mode();
void					up_to_right();
void					home_button(int index, int diff_index);
void					clear_all(int index, int diff_index);
void					end_button(int index);
void					delete_and_left(t_counters *t, char *buf);
void					insert_and_right(t_counters *t, char *buf);
void					edge_warden(t_counters *t, char *buf);
void					clear_quote(t_counters t);
void					up_key(t_history **head, t_counters *t,
		char *buf, int nb_nodes);
void					down_key(t_history **head, t_counters *t, char *buf);
void					home_and_print(t_counters *t, char *buf);
bool					space_before(t_counters t);
void					prev_next_line(t_counters *t, char *buf);
void					backword_march(t_counters *t);
void					forword_march(t_counters *t);
void					prev_next_word(t_counters *t, char *buf);
int						quote_checker(t_counters *t);
void					cursor_clear(t_counters t);
char					*ft_read_line(t_history **head, t_counters *t,
		char **env);
t_history				*create_list(char *command, int placement);
void					node_to_list(t_history **list, t_history *node);
void					quote_edge(t_counters *t, char *buf);
int						line_lenght(char *str);
void					start_position_quote(t_counters *t);
void					q_delete_and_left(t_counters *t, char *buf);
void					q_insert_and_right(t_counters *t, char *buf);
void					up_to_edge(t_counters *t);
int						index_finder(char *find, char *str, int diff);
int						line_nb_in_quote(char *str, int index, int diff);
int						line_lenght(char *str);
void					q_home_and_print(t_counters *t, char *buf);
void					q_prev_next_word(t_counters *t, char *buf);
void					copy_past(t_counters *t, char *buf);
void					q_prev_next_line(t_counters *t, char *buf);
void					ctl_copy(t_counters *t, int start, int direction,
		int zero);
void					q_copy_past(t_counters *t, char *buf);
char					*add_str_in_str(t_counters *t);
char					*remove_str_in_str(t_counters *t, int direction,
		int start, int zero);
void					ctl_copy(t_counters *t, int start, int direction,
		int zero);
void					reverse_position(int index, int diff_index, int len);
void					ctl_past(t_counters *t);
void					ctl_cut(t_counters *t, int direction,
		int start, int zero);
void					selection_remover(t_counters *t, int *direction,
		int *start);
void					q_home_button(int index, int diff_index);
void					q_end_button(int index);
int						str_print(int c);
void					tab_remover(t_counters *t, char *buf);
void					q_reverse_position(int len, t_counters *t);
void					q_home_clear(t_counters t);
void					q_backword_march(t_counters *t);
void					q_forword_march(t_counters *t);
char					*prepare_for_hrd(char **cmd);
int						str_is_print(char *buf);
int						auto_complete(t_counters *t, char **env);
t_counters				*getset(t_counters *t);
void					prompt_printer(t_counters *t, int k);
void					tab_free(char **tabs);
void					*my_malloc(size_t size);
char					*my_strdup(const char *s1);
void					copy_actions(t_counters *t, char *buf);
void					old_left_selection(t_counters *t, int *direction);
void					new_left_selection(t_counters *t, int *direction,
		int *start, int *zero);
void					q_ctl_past(t_counters *t);
void					q_selection_remover(t_counters *t, int *direction,
		int *start);
void					q_ctl_cut(t_counters *t, int direction, int start,
		int zero);
void					q_new_right_s(t_counters *t, int *direction,
		int *start);
void					q_new_left_s(t_counters *t, int *start, int *direction,
		int *zero);
bool					q_line_before(t_counters t);
int						herdoc_checker(t_counters *t, int j);
void					avoid_quote(char *str, int *i);
char					*end_of_doc(int index, char *str);
int						ignore_quote(t_counters *t, int *i);
int						ft_ctrl_d(t_counters *t, int *nb_nodes,
		t_history **head);
void					prompt_printer(t_counters *t, int k);
int						escape_or_not(t_counters *t, char *buf, int *nb_nodes,
		t_history **head);
void					calling_center(t_counters *t, char *buf);
void					doc_quote_printers(t_counters *t);
void					siginthandler(int signal);
void					norme_chokran(t_counters *t);
void					engine_start(t_counters *t, struct termios *term,
		t_history **head);
char					*ft_getpath(char **env);
int						path_counter(char **path, char *str);
char					*path_getter(char **path, char *str);
char					*string_mashup(char *str1, char *str2);
bool					space_before(t_counters t);
void					q_outside_copy(t_counters *t, char *buf);
void					term_putstr(char *str, int index);
void					q_term_putstr(char *str, int index);

#endif
