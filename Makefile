# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2025/02/24 23:22:38 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SRCS		:=	pipex.c	\
				pipex_utils.c

SRCS_BONUS	:=	pipex_bonus.c	\
				pipex_utils_bonus.c

#*------------------------------------------------------------------------------*

SRCS_D		:=	sources/

OBJS_D		:=	objs/

OBJS_B_D	:=	objs_bonus/

#*------------------------------------------------------------------------------*

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

OBJS_B		:=	$(SRCS_BONUS:%.c=$(OBJS_B_D)%.o)

#*------------------------------------------------------------------------------*

HEAD		:=	include/pipex.h	\

HEAD_BONUS	:=	include/pipex_bonus.h \

HEAD_D		:=	.

#*------------------------------------------------------------------------------*

CFLAGS		:=	-Wall -Wextra -Werror -g3

CC			:=	gcc

#*------------------------------------------------------------------------------*

NAME		:=	pipex

NAME_B		:=	pipex_bonus

#*------------------------------------------------------------------------------*

LIBFT		=	Libft/

LIBFT_A		=	$(addprefix $(LIBFT), libft_ex.a)

#*------------------------------------------------------------------------------*

all			:
				@$(MAKE) --no-print-directory $(NAME)

bonus		:
				@$(MAKE) --no-print-directory $(NAME_B)

#*------------------------------------------------------------------------------*

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIBFT_A) $(HEAD)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)  -Lft_ex $(LIBFT_A)
				@echo "$(YELLOW)$(NAME) successfully built!$(NC)"

$(NAME_B)	:	$(OBJS_B_D) $(OBJS_B) $(LIBFT_A) $(HEAD_BONUS)
				@$(CC) $(CFLAGS) -o $(NAME_B) $(OBJS_B)  -Lft_ex $(LIBFT_A)
				@echo "$(YELLOW)$(NAME_B) successfully built!$(NC)"

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_BONUS)
				@echo "$(YELLOW)Compiling $<, depends on $(HEAD)...$(NC)"
				@$(CC) $(CFLAGS) -Iinclude -I$(LIBFT)/includes -c $< -o $@

$(OBJS_B)	:	$(OBJS_B_D)%.o: $(SRCS_D)%.c $(HEAD)
				@echo "$(YELLOW)Compiling $<, depends on $(HEAD_BONUS)...$(NC)"
				@$(CC) $(CFLAGS) -Iinclude -I$(LIBFT)/includes -c $< -o $@

$(LIBFT_A):
				@$(MAKE) -s --no-print-directory -C $(LIBFT)

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

$(OBJS_B_D)	:
				@mkdir -p $(OBJS_B_D)

#*------------------------------------------------------------------------------*

clean		:
				@$(RM) -r $(OBJS) $(OBJS_D) $(OBJS_B) $(OBJS_B_D)
				@$(MAKE) clean -s --no-print-directory -C $(LIBFT)
				@echo "$(YELLOW)Clean complete$(NC)"

fclean		:	clean
				@$(RM) $(NAME) $(NAME_B)
				@$(MAKE) fclean -s --no-print-directory -C $(LIBFT)
				@echo "$(YELLOW)Full clean complete$(NC)"

re			:	fclean all

re_bonus	:	fclean bonus

.PHONY: all bonus clean fclean re re_bonus
