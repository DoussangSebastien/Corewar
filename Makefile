##
## EPITECH PROJECT, 2024
## Project
## File description:
## Makefile
##

.PHONY: all clean fclean re lib unit_tests tests_run coverage

SRC =	src/main.c \
		src/dyna_champ.c \
		src/destroy_champ.c \
		src/dump.c \
		src/dyna_process.c \
		src/destroy_process.c \
		src/destroy_corewar.c \
		src/get_champ_index.c \
		src/get_value.c \
		src/get_value_mod.c \
		src/op.c \
		src/sort_champs_by_id.c \
		src/commands/add.c \
		src/commands/aff.c \
		src/commands/and.c \
		src/commands/fork.c \
		src/commands/lfork.c \
		src/commands/ld.c \
		src/commands/ldi.c \
		src/commands/live.c \
		src/commands/lld.c \
		src/commands/lldi.c \
		src/commands/or.c \
		src/commands/st.c \
		src/commands/sti.c \
		src/commands/sub.c \
		src/commands/xor.c \
		src/commands/zjump.c \
		src/opcode/opcode.c \
		src/parser/check_collisions.c \
		src/parser/get_default_corewar.c \
		src/parser/multiple_free_areas.c \
		src/parser/one_free_area.c \
		src/parser/parse_file.c \
		src/parser/parser.c \
		src/parser/set_champs_pc.c \
		src/parser/sort_free_areas.c \
		src/parser/sort_unset_champs.c \
		src/parser/write_champs_in_arena.c \


NO_BONUS_SRC = src/corewar.c

BONUS_SRC =	bonus/display.c \
			bonus/bonus_corewar.c

TEST_SRC =	src/dyna_champ.c \
			src/destroy_champ.c \
			src/dump.c \
			src/dyna_process.c \
			src/destroy_process.c \
			src/destroy_corewar.c \
			src/get_champ_index.c \
			src/get_value.c \
			src/get_value_mod.c \
			src/op.c \
			src/sort_champs_by_id.c \
			src/commands/add.c \
			src/commands/aff.c \
			src/commands/and.c \
			src/commands/fork.c \
			src/commands/lfork.c \
			src/commands/ld.c \
			src/commands/ldi.c \
			src/commands/live.c \
			src/commands/lld.c \
			src/commands/lldi.c \
			src/commands/or.c \
			src/commands/st.c \
			src/commands/sti.c \
			src/commands/sub.c \
			src/commands/xor.c \
			src/commands/zjump.c \
			src/opcode/opcode.c \
			src/parser/check_collisions.c \
			src/parser/get_default_corewar.c \
			src/parser/multiple_free_areas.c \
			src/parser/one_free_area.c \
			src/parser/parse_file.c \
			src/parser/parser.c \
			src/parser/set_champs_pc.c \
			src/parser/sort_free_areas.c \
			src/parser/sort_unset_champs.c \
			src/parser/write_champs_in_arena.c \
			src/corewar.c

TEST_FILE = tests/test_corewar.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

NO_BONUS_OBJ = $(NO_BONUS_SRC:.c=.o) $(OBJ)

NAME = corewar

CFLAGS = -I./include

LIBS = -L lib/my -lmy

BONUS_LIBS = -L lib/my -lmy -lncurses

ERRORSFLAGS = -W -Wall -Werror -Wextra

all: lib $(NAME)

lib:
	$(MAKE) -C lib/my

$(NAME): $(NO_BONUS_OBJ)
	gcc $(ERRORSFLAGS) -o $(NAME) $(CFLAGS) $(NO_BONUS_OBJ) $(LIBS)

bonus: lib $(OBJ) $(BONUS_OBJ)
	gcc $(ERRORSFLAGS) -o $(NAME) $(CFLAGS) $(OBJ) $(BONUS_OBJ) $(BONUS_LIBS)

unit_tests: lib
	gcc -o unit_tests $(CFLAGS) $(TEST_SRC) $(TEST_FILE) $(LIBS) \
		--coverage -lcriterion

tests_run: unit_tests
	./unit_tests

coverage: tests_run
	gcovr --exclude ./tests
	gcovr --exclude ./tests --txt-metric=branch

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	rm -f $(NO_BONUS_OBJ)
	rm -f *.gcno
	rm -f *.gcda
	rm -f unit_tests

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C lib/my fclean

re: fclean all
