##############################################
###LIBS									######
##############################################

LIBFTDIR		=	libft
LIBFTINC		=	-I$(LIBFTDIR)/includes/
LIBFTLD			=	-L$(LIBFTDIR) -lft
LIBFT			=	$(LIBFTDIR)/libft.a

UNAME			=	$(shell uname)
ifeq ($(UNAME), Darwin)
	MLXDIR		=	libmlx_macos
	MLXLD		=	-lmlx -L$(MLXDIR) -framework OpenGL -framework AppKit
else
	MLXDIR		=	libmlx
	MLXLD		=	-lmlx -L$(MLXDIR) -lXext -lX11 -lm -lz
endif

MLX			=	$(MLXDIR)/libmlx.a
MLXINC			=	-I$(MLXDIR)

##############################################
###HEADERS								######
##############################################

HDRDIR			=	includes/
HDRINC			=	-I$(HDRDIR)


##############################################
###SRCS									######
##############################################

SRCDIR			=	srcs/
# Auto-detect all .c files in srcdir and subdirectories
SRCS			=	$(shell find $(SRCDIR) -name "*.c")


##############################################
###OBJS									######
##############################################

OBJDIR			=	objs/
OBJS			=	$(subst $(SRCDIR), $(OBJDIR), $(subst .c,.o,$(SRCS)))
OBJDIRS			=	$(sort $(dir $(OBJS)))


##############################################
###FLAGS								######
##############################################

NAME			=	miniRT
CC			=	cc
#FSANITIZE		=	-fsanitize=address -g
CFLAGS			=	-Wall -Wextra -Werror$(if $(FSANITIZE), $(FSANITIZE))

ifeq ($(UNAME), Darwin)
	CFLAGS		+=	-DDARWIN
endif

IFLAGS			=	$(HDRINC) $(LIBFTINC) $(MLXINC)
LFLAGS			=	$(LIBFTLD) $(MLXLD)

RM			=	rm -rf
MAKE			=	make
MAKE_C			=	$(MAKE) -C

UP			=	\033[1A
FLUSH			=	\033[2K


##############################################
###RULES								######
##############################################

run: all
	./$(NAME) scenes/sample2.rt

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(MLX) $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJS) $(LFLAGS)

$(LIBFT):
	$(MAKE_C) $(LIBFTDIR)

$(MLX):
	$(MAKE_C) $(MLXDIR)

$(OBJDIRS):
	mkdir -p $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)
	$(MAKE_C) $(LIBFTDIR) $@
	$(MAKE_C) $(MLXDIR) $@

fclean: clean
	$(RM) $(NAME)
	$(MAKE_C) $(LIBFTDIR) $@

re: fclean all

.PHONY: all bonus clean fclean re
