.PHONY: all clean install uninstall

NAME = pathfinder

SRCD = src
INCD = inc
OBJD = obj
LIBD = libmx

CC = clang
CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic)

MV = mv
MK = mkdir -p
RM = rm -rf

SRC = $(wildcard $(SRCD)/*.c)
INC = $(wildcard $(INCD)/*.h)
OBJ = $(addprefix $(OBJD)/, $(notdir $(SRC:%.c=%.o)))
LIB = libmx.a

all:    $(NAME)

$(NAME):        $(OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L. $(LIBD)/$(LIB)

$(OBJ): |       $(OBJD)

$(LIB):
	$(MAKE) -C $(LIBD)

$(OBJD)/%.o: $(SRCD)/%.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCD)

$(OBJD):
	@$(MK) $@

clean:
	@$(RM) $(OBJD)
	$(MAKE) clean -C $(LIBD)

uninstall: clean
		@$(RM) $(NAME)
		$(MAKE) uninstall -C $(LIBD)

reinstall: uninstall all
