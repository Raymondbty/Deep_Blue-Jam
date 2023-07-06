##
## EPITECH PROJECT, 2023
## __init__.py
## File description:
## Zappy module init file
##

from sys import stdout, stderr
from typing import Callable

putstr: Callable = stdout.write
puterr: Callable = stderr.write

EX_ERR: int = 84
EX_OK: int = 0
