#
# EPITECH PROJECT, 2023
# roles.py
# File description:
# Roles functions
#

from typing import Callable
from zappy import putstr, EX_OK, EX_ERR
from zappy.ai_bot import AiBot
import random
from colorama import Fore


def regular_role_strat(my_ai: AiBot) -> None:
    print(my_ai.player_role)
    if my_ai.egg_drop_standby:
        while True:
            print("while stansby", my_ai.player_role)
            my_ai.handle_message()
            if my_ai.egg_drop:
                break
    if my_ai.inventory["food"] > 25 and (
        not my_ai.egg_drop and
        not my_ai.egg_drop_standby
    ):
        my_ai.command_fork()
    elif my_ai.inventory["food"] <= 25 and (
        not my_ai.egg_drop and
        not my_ai.egg_drop_standby
    ):
        my_ai.take_food_simple((30 - my_ai.inventory["food"]))
    # -- start --
    my_ai.do_objectif()
    # ------------
    if my_ai.level == 1 and my_ai.check_incantation(my_ai.level):
        my_ai.command_incantation()
        my_ai.take_all_item(True)
    if my_ai.full_team and my_ai.check_incantation(my_ai.level):
        my_ai.go_to_coords((0, 0))
        my_ai.command_broadcast("ICT|READY")
        while my_ai.count_ready != 5:
            my_ai.handle_message()
        my_ai.count_ready = 0


def defensive_strat(my_ai: AiBot) -> None:
    pass


def offensive_strat(my_ai: AiBot) -> None:
    pass


def unknown_role(my_ai: AiBot) -> int:
    putstr("[*] Unknown role\n")
    if my_ai.inventory["food"] < 25:
        my_ai.take_food_simple((30 - my_ai.inventory["food"]))

    if my_ai.level == 1:
        while True:
            my_ai.take_some_item("linemate", 1)
            if my_ai.inventory["linemate"] >= 1:
                if my_ai.inventory["food"] < 25:
                    my_ai.take_food_simple((50 - my_ai.inventory["food"]))
                my_ai.command_incantation()
                my_ai.take_all_item(True)
                break

    if my_ai.inventory["food"] > 20 and not my_ai.egg_drop and not my_ai.egg_drop_standby:
        my_ai.command_fork()
        my_ai.player_role = "alpha"
        my_ai.player_role_index = 0
    return EX_OK


def alpha_role(my_ai: AiBot) -> int:
    # putstr(f"{Fore.CYAN} [*] Alpha role {my_ai.level} {my_ai.my_count_msg}{Fore.RESET}\n")
    # --- strat ---
    if not my_ai.check_incantation(my_ai.level):
        my_ai.do_objectif()
    else:
        my_ai.command_forward()
        my_ai.take_all_item(True)
        if random.randint(0, 5) == 1:
            my_ai.command_right()
    # -----------------
    if my_ai.full_team and my_ai.check_incantation(my_ai.level):
        my_ai.go_to_coords((0, 0))
        while my_ai.count_ready != 5:
            my_ai.handle_message()
        my_ai.command_incantation()
        my_ai.take_all_item(True)
        my_ai.count_ready = 0
    # --
    return EX_OK


def beta_role(my_ai: AiBot) -> int:
    putstr(f"{Fore.GREEN} [*] Beta role {my_ai.level} {my_ai.my_count_msg}\nFOOD ====\n{my_ai.inventory['food']}{Fore.RESET}\n")
    regular_role_strat(my_ai)
    return EX_OK


def charlie_role(my_ai: AiBot) -> int:
    putstr(f"{Fore.CYAN} [*] Charlie role {my_ai.level} {my_ai.my_count_msg}{Fore.RESET}\n")
    regular_role_strat(my_ai)
    return EX_OK


def delta_role(my_ai: AiBot) -> int:
    putstr(f"[*] Delta role {my_ai.level} {my_ai.my_count_msg}\n")
    regular_role_strat(my_ai)
    return EX_OK


def echo_role(my_ai: AiBot) -> int:
    putstr("[*] Echo role\n")
    regular_role_strat(my_ai)
    return EX_OK

def foxtrot_role(my_ai: AiBot) -> int:
    putstr("[*] Foxtrot role\n")
    if not my_ai.full_team:
        my_ai.full_team = True
    if my_ai.full_team and my_ai.level > 1:
        my_ai.command_broadcast("TEAM|FULL")
    regular_role_strat(my_ai)
    return EX_OK

def geux_role(my_ai: AiBot) -> int:
    putstr(f"[*] Geux role\n")
    # TODO: Stratégie offensive si pas d'incantation ou de fork en cours
    return EX_OK

ROLE_STRAT: dict[str, Callable] = {
    "alpha": alpha_role,
    "beta": beta_role,
    "charlie": charlie_role,
    "delta": delta_role,
    "echo": echo_role,
    "foxtrot": foxtrot_role,
    "geux": geux_role,
    "unknown": unknown_role,
}
