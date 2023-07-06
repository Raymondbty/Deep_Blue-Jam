##
## EPITECH PROJECT, 2023
## ai_bot.py
## File description:
## AiBot class definition
##

from zappy import EX_OK, EX_ERR, putstr, puterr
from zappy.client import Client
from colorama import Fore

import signal
import select
import socket
import os
import time

DEBUG_MODE = True
MAX_INVENTORY: dict[str, int] = {
    "food": 150,
    "linemate": 9,
    "deraumere": 8,
    "sibur": 10,
    "mendiane": 5,
    "phiras": 6,
    "thystame": 1
}
NB_MAX_PLAYER_NEED: int = 6
NB_PLAYER_NEED: list[int] = [0, 1, 2, 2, 4, 4, 6, 6]
MAX_LEVEL: int = 8
UNKNOWN_INDEX: int = 7
STONE_OBJECTIFS: list[dict[str, int]] = [
    {},
    {
        "linemate": 1,
        "deraumere": 0,
        "sibur": 0,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 1,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 0,
        "thystame": 0
    },
    {
        "linemate": 2,
        "deraumere": 0,
        "sibur": 1,
        "mendiane": 0,
        "phiras": 2,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 1,
        "sibur": 2,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 2,
        "sibur": 1,
        "mendiane": 3,
        "phiras": 0,
        "thystame": 0
    },
    {
        "linemate": 1,
        "deraumere": 2,
        "sibur": 3,
        "mendiane": 0,
        "phiras": 1,
        "thystame": 0
    },
    {
        "linemate": 2,
        "deraumere": 2,
        "sibur": 2,
        "mendiane": 2,
        "phiras": 2,
        "thystame": 1
    }
]
PLAYER_ROLES: list[str] = [
    "alpha",
    "beta",
    "charlie",
    "delta",
    "echo",
    "foxtrot",
    "geux",
    "unknown"
]

class AiBot:
    def __init__(self, client: Client):
        self.client: Client = client
        self.teamname: str = client.teamname
        self.level: int = 1
        self.death = False
        self.count_ready: int = 0
        self.full_team: bool = False
        self.last_role_index: int = 0
        self.queue_msg: list[str] = []
        self.slot_team_remaining: int = 0
        self.team_total_allow: int = 1
        self.player_role_index: int = UNKNOWN_INDEX
        self.player_role: str = PLAYER_ROLES[self.player_role_index]
        self.egg_drop: bool = False
        self.egg_drop_standby: bool = False
        self.msg_counter: dict[str, int] = {
            "alpha": 0,
            "beta": 0,
            "charlie": 0,
            "delta": 0,
            "echo": 0,
            "foxtrot": 0,
            "geux": 0
        }
        self.my_count_msg: int = 0
        self.map_look: list[list] = [[]]
        self.all_inventory: dict[str, dict] = {
            "alpha": {
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
            "beta": {
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
            "charlie": {
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
            "delta": {
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
            "echo": {
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            },
            "foxtrot": {
                "food": 0,
                "linemate": 0,
                "deraumere": 0,
                "sibur": 0,
                "mendiane": 0,
                "phiras": 0,
                "thystame": 0
            }
        }
        self.global_inventory: dict[str, int] = {
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.inventory: dict[str, int] = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.food: int = 1260
        # map management
        self.map_size: list[int] = [0, 0]
        self.position: list[int] = [0, 0]
        self.axe: list[str] = ["^", ">", "v", "<"]
        self.axe_size: int = 4
        self.index_axes: int = 0
        self.axes: dict[str, tuple[int, int]] = {
            "^": (0, 1),
            ">": (1, 0),
            "v": (0, -1),
            "<": (-1, 0)
        }

        signal.signal(signal.SIGINT, self.logout_handler)

    def send_command(self, command: str) -> bool:
        if DEBUG_MODE:
            if self.player_role == "unknown":
                print("[UNKNOWN][SEND] : " + command, end="")
            else:
                print("[" + self.player_role + "][SEND] : " + command, end="")

        fd_write: list[socket.socket] = [self.client.socket]

        while True:
            _, outfds, errfds = select.select([], fd_write, [], 0.5)
            if errfds:
                puterr("[!] Connection closed by server.\n")
                self.logout(EX_ERR)
            if outfds:
                self.client.send(command)
                return True

    def logout_handler(self, signal: int, _) -> None:
        self.logout(signal)

    def logout(self, exit_code: int) -> None:
        putstr(f"[!] Logout {exit_code}\n")
        self.send_command("logout\n")
        exit(exit_code)

    def recv_command(self) -> str:
        buffer: str = ""
        fd_read: list[socket.socket] = [self.client.socket]

        while True:
            infds, _, errfds = select.select(fd_read, [], [], 0.5)

            if errfds:
                puterr("[!] Connection closed by server.\n")
                self.logout(EX_ERR)

            if infds:
                character: str = self.client.recv(1)

                if character != '\n':
                    buffer += character
                    continue
                if buffer.startswith("eject: ") or buffer.startswith("message "):
                    self.queue_msg.append(buffer)
                    buffer = ""
                else:
                    break

        if buffer == "dead":
            if self.player_role == "unknow":
                print("[UNKNOWN]")
            else:
                putstr(f"[{self.player_role}]\n")
            print(Fore.RESET)
            self.death = True
            putstr("The AI Starved\n")
            self.logout(EX_OK)
        if DEBUG_MODE:
            if self.player_role == "unknown":
                putstr(f"[UNKNOWN][RECEIVE]: {buffer}\n")
            else:
                putstr(f"[{self.player_role}][RECEIVE]: {buffer}\n")
        return buffer

    def starter(self) -> None:
        if self.recv_command() != "WELCOME":
            puterr("[!] Wrong Teamname.\n")
            self.logout(EX_ERR)
        # TODO self.send_command("AI" + "\n")
        # if self.recv_command() == "ko":
        #     self.logout(EX_ERR)
        self.send_command(self.teamname + "\n")

        msg: str = self.recv_command()

        if msg == "ko":
            puterr("[!] Wrong Teamname.\n")
            self.logout(EX_ERR)
        self.slot_team_remaining = int(msg)
        msg = self.recv_command()
        self.map_size = [int(msg.split(' ')[0]), int(msg.split(' ')[1])]
        putstr(f"[SEND][{self.player_role}]: Broadcast {self.teamname};EGG\n")
        self.send_command(f"Broadcast {self.teamname};EGG\n")
        if self.recv_command() == "ko":
            puterr("[!] Wrong Teamname.\n")
            self.logout(EX_ERR)
        self.team_total_allow = self.slot_team_remaining + 1

    def sort_message(self) -> bool:
        # TODO: handle eject
        egg_done: bool = False
        for msg in self.queue_msg:
            if not msg.split(", ")[1].startswith(self.teamname):
                self.queue_msg.remove(msg)
                continue

            temp: list[str] = msg.split(", ")[1].split("|")

            if msg.endswith("EGG") and not egg_done:
                self.command_broadcast("SELF|" + PLAYER_ROLES[self.last_role_index + 1])
                self.last_role_index += 1
                self.queue_msg.remove(msg)
                egg_done = True
                continue

            if temp[1] in PLAYER_ROLES and int(temp[2]) > self.msg_counter[temp[1]]:
                self.msg_counter[temp[1]] = int(temp[2])
                self.queue_msg.remove(msg)
                continue
        return True

    def handle_message(self) -> bool:
        # DOC: (message 5, teamname|player_role|count_msg|TAG|msg)
        # for msg in self.queue_msg:
        #     if msg.split(", ")[1] == (self.teamname + ";" + "EGG"):
        #         print("\n\n\n\n\n\n--------------------- (2)\n\n\n\n\n\n\n")
        #         putstr(f"[RECEIVE][{self.player_role}] {msg}\n")
        #         self.egg_drop = True
        #         self.egg_drop_standby = False
        #         self.queue_msg.remove(msg)
        #         self.command_broadcast("SELF|" + PLAYER_ROLES[self.last_role_index + 1])
        #         return True
        self.sort_message()
        for msg in self.queue_msg:
            if msg.split(", ")[1].endswith("EGG"):
                self.queue_msg.remove(msg)
            temp_pos: str = msg.split(", ")[0].split(" ")[1]
            list_arg: list[str] = msg.split(", ")[1].split("|")
            temp_role: str = list_arg[1]
            msg_counter: int = int(list_arg[2])
            temp_tag: str = list_arg[3]
            temp_msg: str = list_arg[4]

            if self.player_role != "unknown" and temp_tag == "TEAM" and temp_msg == "FULL":
                self.full_team = True
                self.queue_msg.remove(msg)
                continue
            if self.player_role != "unknown" and temp_tag == "ICT" and temp_msg == "READY":
                self.count_ready += 1
                if self.count_ready == 5:
                    self.set_all()
                self.queue_msg.remove(msg)
                continue
            if self.player_role != "unknown" and temp_tag == "IVT":
                # parsing msg
                list_arg[4] = msg[len(
                    "message k, " +
                    self.teamname +
                    "|" +
                    temp_role +
                    "|" +
                    str(msg_counter) +
                    "|IVT|"
                ):]

                temp_msg: str = list_arg[4]
                list_inventory: list[str] = temp_msg.split("[ ")[1].split(" ]")[0].split(', ')

                for i in range(len(list_inventory)):
                    self.all_inventory[temp_role][list_inventory[i].split(' ')[0]] = int(
                        list_inventory[i].split(' ')[1])
                # add to global inventory
                self.all_inventory[self.player_role] = self.inventory
                self.global_inventory = {}
                for y in self.all_inventory:
                    for i in self.all_inventory[y]:
                        if i not in self.global_inventory:
                            self.global_inventory[i] = 0
                        self.global_inventory[i] += self.all_inventory[y][i]

                print(Fore.RED, "REMOVE 5 (", msg, ")", Fore.RESET)
                self.queue_msg.remove(msg)
                continue
            if temp_tag == "SELF" and self.player_role == "unknown":
                putstr(f"[RECEIVE][{self.player_role}] {msg}\n")
                self.player_role = temp_msg
                self.player_role_index = PLAYER_ROLES.index(self.player_role)
                self.last_role_index = self.player_role_index
                self.queue_msg.remove(msg)
        return True

    def command_broadcast(self, msg) -> bool:
        if self.player_role == "geux":
            return False
        self.my_count_msg += 1
        new_msg: str = self.teamname + \
                       "|" + \
                       self.player_role + \
                       "|" + \
                       str(self.my_count_msg) + \
                       "|" + \
                       msg
        self.send_command(f"Broadcast {new_msg}\n")
        if self.recv_command() == "ok":
            # self.food -= 7
            return True
        return False

    def command_forward(self) -> bool:
        self.send_command("Forward\n")
        if self.recv_command() != "ok":
            return False
        if self.axe[self.index_axes] == "^":
            self.position[1] += 1
            if self.position[1] == self.map_size[1]:
                self.position[1] = 0
        elif self.axe[self.index_axes] == ">":
            self.position[0] += 1
            if self.position[0] == self.map_size[0]:
                self.position[0] = 0
        elif self.axe[self.index_axes] == "v":
            self.position[1] -= 1
            if self.position[1] == -1:
                self.position[1] = self.map_size[1] - 1
        elif self.axe[self.index_axes] == "<":
            self.position[0] -= 1
            if self.position[0] == -1:
                self.position[0] = self.map_size[0] - 1
        return True

    def command_right(self) -> bool:
        self.send_command("Right\n")
        if self.recv_command() == "ok":
            self.index_axes += 1
            if self.index_axes == self.axe_size:
                self.index_axes = 0
            return True
        return False

    def command_left(self) -> bool:
        self.send_command("Left\n")
        if self.recv_command() == "ok":
            self.index_axes -= 1
            if self.index_axes == -1:
                self.index_axes = self.axe_size - 1
            return True
        return False

    def command_look(self) -> list:
        self.send_command("Look\n")
        self.food -= 7
        while True:
            msg: str = self.recv_command()

            if msg != "ok" and msg != "ko":
                break
        string = msg.strip("[]")
        string = string[1:-1]
        list_2d = []
        first_list = string.split(", ")
        for i in range(len(first_list)):
            sub_list = []
            elements = first_list[i].split(" ")
            for element in elements:
                sub_list.append(element.strip(","))
            list_2d.append(sub_list)
        return list_2d

    def command_inventory(self) -> bool:
        self.send_command("Inventory\n")
        self.food -= 1
        while True:
            msg: str = self.recv_command()

            if msg != "ok" and msg != "ko":
                break
        if self.player_role != "unknown":
            self.command_broadcast("IVT|" + msg)

        list_inventory: list[str] = msg.split("[ ")[1].split(" ]")[0].split(', ')

        if self.player_role == "unknown":
            for i in range(len(list_inventory)):
                self.inventory[list_inventory[i].split(' ')[0]] = int(list_inventory[i].split(' ')[1])
            # add to global inventory
            for i in self.inventory:
                self.global_inventory[i] += self.inventory[i]
            return True
        for i in range(len(list_inventory)):
            self.inventory[list_inventory[i].split(' ')[0]] = int(list_inventory[i].split(' ')[1])
        for i in range(len(list_inventory)):
            self.all_inventory[self.player_role][list_inventory[i].split(' ')[0]] = int(list_inventory[i].split(' ')[1])
        # add to global inventory
        if self.all_inventory[self.player_role] is None:
            return True
        for i in self.all_inventory[self.player_role]:
            self.global_inventory[i] += self.all_inventory[self.player_role][i]
        return True

    def command_connect_nbr(self) -> int:
        self.send_command("Connect_nbr\n")

        msg: str = self.recv_command()

        self.slot_team_remaining = int(msg)
        return self.slot_team_remaining

    def command_fork(self) -> bool:
        if self.player_role == "geux":
            return False
        self.go_to_coords([0, 0])
        self.send_command("Fork\n")
        if self.recv_command() != "ok":
            return False
        self.egg_drop_standby = True
        self.team_total_allow += 1
        fd: int = os.fork()

        if fd != 0:
            return True
        time.sleep(5)
        os.execve(
           "./ai/zappy_ai",
           [
               "./ai/zappy_ai",
               "-p",
               str(self.client.port),
               "-n",
               self.client.teamname,
               "-h",
               self.client.hostname
           ],
           os.environ
        )
        return True

    def command_eject(self) -> bool:
        self.send_command("Eject\n")
        if self.recv_command() == "ok":
            # self.food -= 7
            return True
        return False

    def command_take(self, obj: str) -> bool:
        # don't take food if i have 50 food
        if obj == "food" and self.inventory["food"] >= 50:
            return True
        self.send_command(f"Take {obj}\n")
        if self.recv_command() == "ok":
            # self.inventory[obj] += 1
            # self.food -= 7
            self.command_inventory()
            return True
        return False

    def command_set(self, obj: str) -> bool:
        self.send_command(f"Set {obj}\n")
        if self.recv_command() == "ok":
            # self.inventory[obj] -= 1
            # self.food -= 7
            self.command_inventory()
            return True
        return False

    def set_all(self) -> None:
        for i in self.inventory:
            if i != "food":
                if self.inventory[i] > 0:
                    self.command_set(i)
        self.command_inventory()

    def command_incantation(self) -> bool:
        if self.player_role == "geux":
            return False
        self.set_all()
        self.send_command("Incantation\n")
        if self.recv_command() == "ko":
            return False

        msg: str = self.recv_command()

        if msg.startswith("Current level"):
            self.level += 1
            return True
        return False

    def need_to_take(self, stone: str) -> bool:
        max_item_needed: int = MAX_INVENTORY[stone]

        if stone != "food":
            for _ in range(1, self.level):
                max_item_needed -= MAX_INVENTORY[stone]
        if not stone:
            return False
        if self.global_inventory[stone] < max_item_needed:
            return True
        return False

    def take_all_item(self, mode: bool) -> bool:
        stones: list[str] = self.command_look()

        if stones is None:
            return False
        for stone in stones[0]:
            if stone == "player":
                continue
            if mode or self.need_to_take(stone):
                if not self.command_take(stone):
                    return False
        return True

    def get_stone_objectif(self) -> "dict[str, int] | None":
        stones: dict[str, int] = {
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }

        for stone in (
            "linemate",
            "deraumere",
            "sibur",
            "mendiane",
            "phiras",
            "thystame"
        ):
            if STONE_OBJECTIFS[self.level][stone] > self.inventory[stone]:
                stones[stone] = STONE_OBJECTIFS[self.level][stone] - self.inventory[stone]
        if sum(stones.values()) == 0:
            return None
        return stones

    def go_to_pos(self, pos) -> None:
        # self.take_all_item(False)
        if pos == 1:
            self.command_forward()
            return
        if pos == 2:
            self.command_forward()
            self.command_left()
            self.command_forward()
            return
        if pos == 3:
            self.command_left()
            self.command_forward()
            return
        if pos == 4:
            self.command_left()
            self.command_forward()
            self.command_left()
            self.command_forward()
            return
        if pos == 5:
            self.command_left()
            self.command_left()
            self.command_forward()
            return
        if pos == 6:
            self.command_right()
            self.command_forward()
            self.command_right()
            self.command_forward()
            return
        if pos == 7:
            self.command_right()
            self.command_forward()
            return
        if pos == 8:
            self.command_forward()
            self.command_right()
            self.command_forward()

    def debug_fonction(self):
        """
        self.map_size: list[int] = [0, 0]
        self.position: list[int] = [0, 0]
        self.axe: list[str] = ["^", ">", "v", "<"]
        self.axe_size: int = 4
        self.index_axes: int = 0
        self.axes: dict[str, tuple[int, int]] = {"^": (0, 1), ">": (1, 0), "v": (0, -1), "<": (-1, 0)}
        :return:
        """
        for i in range(self.map_size[1]):
            for j in range(self.map_size[0]):
                if i == self.position[1] and j == self.position[0]:
                    putstr(self.axe[self.index_axes])
                    continue
                if i == self.position[1] or j == self.position[0]:
                    putstr("-")
                    continue
                putstr(".")
            putstr("\n")

    def turn_to_direction(self, direction: str) -> None:
        if self.axe[self.index_axes] == direction:
            return
        if self.axe[(self.index_axes + 1) % len(self.axe)] == direction:
            self.command_right()
            return
        if self.axe[self.index_axes - 1] == direction:
            self.command_left()
            return
        if self.axe[self.index_axes - 2] == direction:
            self.command_left()
            self.command_left()
            return
        if self.axe[self.index_axes - 3] == direction:
            self.command_right()
            self.command_right()
            return

    def go_to_coords(self, target: "tuple[int, int] | list[int]") -> bool:
        position_x, position_y = self.position[0], self.position[1]
        map_x, map_y = self.map_size[0], self.map_size[1]
        x, y = target

        # Gestion du mouvement selon l'axe x
        if x != position_x:
            diff_x: int = abs(x - position_x)
            if diff_x > map_x / 2:
                putstr("short cut x\n")
                if x > position_x:
                    self.turn_to_direction('<')
                else:
                    self.turn_to_direction('>')
                diff_x = map_x - diff_x
            else:
                if x > position_x:
                    self.turn_to_direction('>')
                else:
                    self.turn_to_direction('<')
            for _ in range(diff_x):
                self.command_forward()
        # Gestion du mouvement selon l'axe y
        if y != position_y:
            diff_y: int = abs(y - position_y)

            if diff_y > map_y / 2:
                if y > position_y:
                    self.turn_to_direction('^')
                else:
                    self.turn_to_direction('v')
                diff_y = map_y - diff_y
            else:
                if y > position_y:
                    self.turn_to_direction('v')
                else:
                    self.turn_to_direction('^')
            for _ in range(diff_y):
                self.command_forward()
        return True

    def check_incantation(self, level) -> bool:
        stones: dict[str, int] = STONE_OBJECTIFS[level]

        for stone in stones:
            if stones[stone] < self.global_inventory[stone]:
                return False
        return True

    def go_to_vision_coords(self, pos: int) -> bool:
        if pos == 0:
            pass
        elif pos == 1:
            self.command_forward()
            self.command_left()
            self.command_forward()
        elif pos == 2:
            self.command_forward()
        elif pos == 3:
            self.command_forward()
            self.command_right()
            self.command_forward()
        elif pos == 4:
            self.command_forward()
            self.command_forward()
            self.command_left()
            self.command_forward()
            self.command_forward()
        elif pos == 5:
            self.command_forward()
            self.command_forward()
            self.command_left()
            self.command_forward()
        elif pos == 6:
            self.command_forward()
            self.command_forward()
        elif pos == 7:
            self.command_forward()
            self.command_forward()
            self.command_right()
            self.command_forward()
        elif pos == 8:
            self.command_forward()
            self.command_forward()
            self.command_right()
            self.command_forward()
            self.command_forward()
        elif pos == 9:
            self.command_forward()
            self.command_forward()
            self.command_forward()
            self.command_left()
            self.command_forward()
            self.command_forward()
            self.command_forward()
        elif pos == 10:
            self.command_forward()
            self.command_forward()
            self.command_forward()
            self.command_left()
            self.command_forward()
            self.command_forward()
        elif pos == 11:
            self.command_forward()
            self.command_forward()
            self.command_forward()
            self.command_left()
            self.command_forward()
        elif pos == 12:
            self.command_forward()
            self.command_forward()
            self.command_forward()
        elif pos == 13:
            self.command_forward()
            self.command_forward()
            self.command_forward()
            self.command_right()
            self.command_forward()
        elif pos == 14:
            self.command_forward()
            self.command_forward()
            self.command_forward()
            self.command_right()
            self.command_forward()
            self.command_forward()
        elif pos == 15:
            self.command_forward()
            self.command_forward()
            self.command_forward()
            self.command_right()
            self.command_forward()
            self.command_forward()
            self.command_forward()
        return True

    def get_coord_of_looks(self, index):
        coord: list[int] = self.position.copy()
        directions: dict[str, dict[int, tuple[int, int]]] = {
            "^": {
                0: (0, 0),
                1: (-1, -1),
                2: (-1, 0),
                3: (-1, 1),
                4: (-2, -2),
                5: (-2, -1),
                6: (-2, 0),
                7: (-2, 1),
                8: (-2, 2),
                9: (-3, -3),
                10: (-3, -2),
                11: (-3, -1),
                12: (-3, 0),
                13: (-3, 1),
                14: (-3, 2),
                15: (-3, 3),
            },
            ">": {
                0: (0, 0),
                1: (-1, 1),
                2: (0, 1),
                3: (1, 1),
                4: (-2, 2),
                5: (-1, 2),
                6: (0, 2),
                7: (1, 2),
                8: (2, 2),
                9: (-3, 3),
                10: (-2, 3),
                11: (-1, 3),
                12: (0, 3),
                13: (1, 3),
                14: (2, 3),
                15: (3, 3),
            },
            "v": {
                0: (0, 0),
                1: (1, 1),
                2: (1, 0),
                3: (1, -1),
                4: (2, 2),
                5: (2, 1),
                6: (2, 0),
                7: (2, -1),
                8: (2, -2),
                9: (3, 3),
                10: (3, 2),
                11: (3, 1),
                12: (3, 0),
                13: (3, -1),
                14: (3, -2),
                15: (3, -3),
            },
            "<": {
                0: (0, 0),
                1: (1, -1),
                2: (0, -1),
                3: (-1, -1),
                4: (2, -2),
                5: (1, -2),
                6: (0, -2),
                7: (-1, -2),
                8: (-2, -2),
                9: (3, -3),
                10: (2, -3),
                11: (1, -3),
                12: (0, -3),
                13: (-1, -3),
                14: (-2, -3),
                15: (-3, -3),
            },
        }

        direction: tuple[int, int] = directions[self.axe[self.index_axes]][index]

        coord[0] += direction[0]
        coord[1] += direction[1]
        coord[0] = (coord[0] + self.map_size[0]) % self.map_size[0]
        coord[1] = (coord[1] + self.map_size[1]) % self.map_size[1]
        return coord

    def get_coord_of_look(self, index):
        coord = [0, 0]
        coord[0] = self.position[0]
        coord[1] = self.position[1]
        directions = {
            "^": {
                0: (0, 0),
                1: (-1, -1),
                2: (-1, 0),
                3: (-1, 1),
                4: (-2, -2),
                5: (-2, -1),
                6: (-2, 0),
                7: (-2, 1),
                8: (-2, 2),
                9: (-3, -3),
                10: (-3, -2),
                11: (-3, -1),
                12: (-3, 0),
                13: (-3, 1),
                14: (-3, 2),
                15: (-3, 3),
            },
            ">": {
                0: (0, 0),
                1: (-1, 1),
                2: (0, 1),
                3: (1, 1),
                4: (-2, 2),
                5: (-1, 2),
                6: (0, 2),
                7: (1, 2),
                8: (2, 2),
                9: (-3, 3),
                10: (-2, 3),
                11: (-1, 3),
                12: (0, 3),
                13: (1, 3),
                14: (2, 3),
                15: (3, 3),
            },
            "v": {
                0: (0, 0),
                1: (1, 1),
                2: (1, 0),
                3: (1, -1),
                4: (2, 2),
                5: (2, 1),
                6: (2, 0),
                7: (2, -1),
                8: (2, -2),
                9: (3, 3),
                10: (3, 2),
                11: (3, 1),
                12: (3, 0),
                13: (3, -1),
                14: (3, -2),
                15: (3, -3),
            },
            "<": {
                0: (0, 0),
                1: (1, -1),
                2: (0, -1),
                3: (-1, -1),
                4: (2, -2),
                5: (1, -2),
                6: (0, -2),
                7: (-1, -2),
                8: (-2, -2),
                9: (3, -3),
                10: (2, -3),
                11: (1, -3),
                12: (0, -3),
                13: (-1, -3),
                14: (-2, -3),
                15: (-3, -3),
            },
        }
        coord[0] += directions[self.axe[self.index_axes]][index][0]
        coord[1] += directions[self.axe[self.index_axes]][index][1]
        if coord[0] < 0:
            coord[0] += self.map_size[0]
        if coord[1] < 0:
            coord[1] += self.map_size[1]
        if coord[0] >= self.map_size[0]:
            coord[0] -= self.map_size[0]
        if coord[1] >= self.map_size[1]:
            coord[1] -= self.map_size[1]
        return coord

    def take_some_item(self, item: str, nb: int) -> int:
        count_rigth: int = 0
        count: int = 0

        while True:
            self.handle_message()
            if count >= nb:
                return True

            list_look: list = self.command_look()

            if list_look is None:
                return False
            if len(list_look) == 0:
                return False

            save_count: int = count
            y: int = 0

            while y < len(list_look):
                x: int = 0

                while x < len(list_look[y]):
                    if list_look[y][x] == item:
                        pos_of_item = self.get_coord_of_look(y)
                        self.go_to_coords(pos_of_item)
                        if self.command_take(item):
                            count += list_look[y].count(item)
                        break
                    x += 1
                y += 1
            if count == save_count:
                self.command_right()
                count_rigth += 1
            if count_rigth == 4:
                for _ in range(2):
                    self.command_forward()
                count_rigth = 0

    def take_food_simple(self, nb):
        count = 0
        forward = 0
        while count < nb:
            self.handle_message()
            if self.command_take("food"):
                count += 1
            self.command_forward()
            forward += 1
            if forward == 10:
                self.command_right()
                self.command_forward()
                self.command_left()
                forward = 0
        return True

    def do_objectif(self) -> bool:
        if self.inventory["food"] < 15:
            self.take_food_simple(5)

        level: int = self.level
        stones: dict[str, int] = STONE_OBJECTIFS[level]
        stones_reaming: dict[str, int] = {
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }

        for stone in stones:
            stones_reaming[stone] = stones[stone] - self.global_inventory[stone]
        for stone in stones_reaming:
            self.handle_message()
            if stones_reaming[stone] > 0:
                self.take_some_item(stone, stones_reaming[stone])
        return True
