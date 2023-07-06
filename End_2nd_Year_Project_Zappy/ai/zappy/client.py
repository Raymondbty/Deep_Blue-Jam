#
# EPITECH PROJECT, 2023
# client.py
# File description:
# Client class definition
#

from zappy import EX_ERR, puterr

import socket


class Client:
    def __init__(self, host: str, port: int, team: str) -> None:
        self.__is_log: bool = False
        self.__debug: bool = True
        self.__client_remaining: int = 0
        self.teamname: str = team
        self.hostname: str = host
        self.port: int = port

        self.socket: socket.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        try:
            if self.socket.connect((self.hostname, self.port)) == -1:
                exit(EX_ERR)
            self.is_log = True
        except socket.error:
            puterr(
                f"[!] Connection failed, check the port number and the \
                machine name.\nUnable to connect to \
                {self.hostname}:{self.port}\n"
            )
            exit(EX_ERR)

    def __del__(self) -> None:
        self.socket.close()

    def send(self, message) -> None:
        self.socket.send(str(message).encode("utf-8"))

    def recv(self, size) -> str:
        buffer: str = self.socket.recv(size).decode("utf-8")
        if not buffer:
            puterr("[!] Connection closed by server.\n")
            exit(EX_ERR)
        return buffer
