# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 00:25:03 by tsaby             #+#    #+#              #
#    Updated: 2025/02/20 18:42:14 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		:=	pipex.c	\
				pipex_utils.c

SRCS_D		:=	sources/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD		:=	include/pipex.h	\

HEAD_D		:=	.

CFLAGS		:=	-Wall -Wextra -Werror -g3

CC			:=	gcc

NAME		:=	pipex

LIBFT		=	Libft/

LIBFT_A		=	$(addprefix $(LIBFT), libft_ex.a)

all			:
				$(MAKE) $(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIBFT_A) $(HEAD)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)  -Lft_ex $(LIBFT_A)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD)
				$(CC) $(CFLAGS) -Iinclude -I$(LIBFT)/includes -c $< -o $@

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

clean		:
				$(RM) -r $(OBJS) $(OBJS_D) $(OBJS_B) $(OBJS_B_D)
				$(MAKE) clean -s -C $(LIBFT)

fclean		:	clean
				$(RM) $(NAME) $(NAME_B)
				$(MAKE) fclean -s -C $(LIBFT)

re			:	fclean all


.PHONY: all bonus clean fclean re
