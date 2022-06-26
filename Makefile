S		= srcs/
O		= objs/
I		= incs/
D		= deps/

NAME	= containers

SRCS	= vector.cpp

CC		= c++

CFLAGS	+= -std=c++98

CFLAGS	+= -I$I

SRCS	:= $(foreach file,$(SRCS),$S$(file))
OBJS	= $(SRCS:$S%=$O%.o)
DEPS	= $(SRCS:$S%=$D%.d)

RM		= /bin/rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
	$(CC) $(CFLAGS) -c $< -o $@

$D:
	@mkdir $@

$(DEPS): | $D

$(DEPS): $D%.d: $S%
	@$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $^ -o $@

clean:
	@$(RM) $D $O

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEPS)
