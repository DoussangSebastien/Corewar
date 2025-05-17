/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** test_corewar.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corewar.h"

Test(corewar, standard_case)
{
    const char *argv[3] = {"./corewar", "tests/abel.cor", "tests/abel.cor"};
    const int argc = 3;
    cr_expect_eq(corewar(argc, argv), SUCCESS);
}

Test(corewar, NULL_argv)
{
    const char *argv[2] = {"./corewar", NULL};
    const int argc = 2;
    cr_expect_eq(corewar(argc, argv), FAILURE);
}

Test(corewar, incorrect_champion)
{
    const char *argv[3] = {"./corewar", "tests/abel.cor", "tests/incorrect.cor"};
    const int argc = 3;
    cr_expect_eq(corewar(argc, argv), FAILURE);
}

Test(corewar, many_champion)
{
    const char *argv[6] = {"./corewar", "tests/abel.cor", "tests/bill.cor", "tests/champions/CoreWar/42.cor", "tests/champions/CoreWar/SuperBob.cor", "tests/abel.cor"};
    const int argc = 6;
    cr_expect_eq(corewar(argc, argv), SUCCESS);
}

Test(corewar, many_champion_with_flag)
{
    const char *argv[10] = {"./corewar", "tests/abel.cor", "-n", "8", "tests/bill.cor", "tests/champions/CoreWar/42.cor", "-a", "33", "tests/champions/CoreWar/SuperBob.cor", "tests/abel.cor"};
    const int argc = 10;
    cr_expect_eq(corewar(argc, argv), SUCCESS);
}

Test(corewar, dump_flag_case)
{
    const char *argv[5] = {"./corewar", "-dump", "15", "tests/abel.cor", "tests/abel.cor"};
    const int argc = 5;
    cr_expect_eq(corewar(argc, argv), SUCCESS);
}
