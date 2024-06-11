
############################## varaibles section #######################

#Mandatory directory

MANDATORY 				=	./mandatory

#Mandatory source files names.

SRCS                    =	$(MANDATORY)/main.c \
							$(MANDATORY)/ft_parsing.c \
							$(MANDATORY)/ft_create_thr.c \
							$(MANDATORY)/ft_routing.c \
							$(MANDATORY)/ft_action.c \
							$(MANDATORY)/ft_mutex.c

OBJS                    =	$(SRCS:%c=%o)

#Bonus directory

BONUS 					=	./bonus

#Bonus source files names.

SRCS_BONUS              =	$(BONUS)/main_bonus.c \
							$(BONUS)/ft_parsing_bonus.c \
							$(BONUS)/ft_create_philos_bonus.c \
							$(BONUS)/ft_initiate_smphr_bonus.c \
							$(BONUS)/ft_generate_name_bonus.c \
							$(BONUS)/ft_routing_bonus.c \
							$(BONUS)/ft_action_bonus.c \
							$(BONUS)/ft_smphr_bonus.c

#Bonus object files name.

OBJS_BONUS              =	$(SRCS_BONUS:%c=%o)

FLAGS                   =	-Wall -Wextra -Werror -g -fsanitize=thread

NAME                    =	philo

#########################################################################

############################ Rules Section ##############################

all                     :	$(NAME)

$(BONUS)/%o           	:	$(BONUS)/%c $(BONUS)/philosopher_bonus.h
	gcc  -c $(FLAGS) $< -o $@

%o                      :	%c $(MANDATORY)/philosopher.h
	gcc  -c $(FLAGS) $< -o $@

$(NAME)                 :	$(OBJS)
	gcc  $(FLAGS) $(OBJS) -o $(NAME) -pthread

bonus                   :	$(OBJS_BONUS)
	gcc  $(FLAGS) $(OBJS_BONUS) -o philo_bonus -pthread

clean                   :
	rm -f $(MANDATORY)/*.o
	rm -f $(BONUS)/*.o

fclean                  :	clean
	rm -f $(NAME) philo_bonus

re                      :	fclean all

.PHONY                  :	clean