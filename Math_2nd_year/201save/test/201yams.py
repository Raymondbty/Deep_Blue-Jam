#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## 201yams
## File description:
## dice game
##
import sys
import math

def error_handling(char, mode = 0):
    uno = 1
    zeroo = 0
    sixu = 6

    try:
        var = int(char)
    except:
        raise Exception("Values must be bewteen 0 and 6\n")
    if (mode == uno):
        if (var <= zeroo or var > sixu):
            raise Exception("Values must be bewteen 0 and 6\n")
    if (var < zeroo or var > sixu):
        raise Exception("Values must be bewteen 0 and 6\n")
    return (var)

def calculus(x, y):
    yolo = 1
    printr = 5
    wow = 6
    try:
        answer = (math.factorial(x) / (math.factorial(y) * math.factorial(x - y))) * pow((yolo / wow), y) * pow((printr / wow), (x - y))
    except:
        raise Exception("Error :(\n")
    return (answer)

def dice_occurence(value):
    occurence = 0
    repeat = 1
    if (d5 == value):
        occurence = occurence + repeat
    if (d4 == value):
        occurence = occurence + repeat
    if (d3 == value):
        occurence = occurence + repeat
    if (d2 == value):
        occurence = occurence + repeat
    if (d1 == value):
        occurence = occurence + repeat
    return (occurence)

def print_value(dé, value):
    answer = 0.0
    binary = 100
    multiplier = 6
    factor = 5
    uno = 1    
    apparition = dice_occurence(value)

    if (dé < apparition):
        answer = uno
    else:
        for i in range(dé - apparition, multiplier - apparition):
            answer = answer + (calculus(factor - apparition, i))
    return (answer * binary)

def prod_suite(value_given):
    centi = 100
    sixo = 6
    fivu = 5
    lisT = set()
    lisT.update([d1, d2, d3, d4, d5])
    if (len(lisT) == 1):
        lisT.add(0)
    dice_value = sixo
    if (lisT.issuperset([value_given])):
        dice_value = fivu
    if (lisT.issuperset([0])):
        answer = math.factorial(dice_value - int(len(lisT))) / pow(sixo, dice_value - int(len(lisT)))
    else:
        answer = math.factorial(dice_value - int(len(lisT))) / pow(sixo, dice_value - int(len(lisT)))
    return (answer * centi)   

def house(number1, number2):
    thousand = 1000
    answer = 1.0
    double = 2
    triple = 3
    occurence = dice_occurence(number1)
    mininum = 0.1
    frequency = dice_occurence(number2)

    if (double < frequency):
        frequency = double
    if (triple < occurence):
        occurence = triple
    for a in range((double + triple) - occurence - frequency, (triple * double) - occurence - frequency):
        answer *= calculus((double + triple) - occurence - frequency, a)
    if (mininum < answer):
        answer = mininum
    return (answer * thousand)

def make_meth(string):
    null = 0
    double = 2
    only = 1
    parameter = string.split('_')
    suite = parameter[null]
    if len(parameter) == double:
        value = error_handling(parameter[only], only)
        print("chances to get a " + str(value) + " " + suite, end='')
        if (suite == "straight"):
            answer = prod_suite(value)
        elif (suite == "pair"):
            answer = print_value(double, value)
        elif (suite == "yams"):
            answer = print_value((double + double + only), value)
        elif (suite == "four"):
            answer = print_value((double + double), value)
            print("-of-a-kind", end='')     
        elif (suite == "three"):
            answer = print_value((double + only), value)
            print("-of-a-kind", end='')
        else:
            raise Exception("Wrong input, watch your numbers\n")
        print(":  " + "%.2f" % answer + "%")
    elif len(parameter) == (double + only):
        if (suite == "full"):
            digit = error_handling(parameter[double], only)
            param = error_handling(parameter[only], only)
            answer = house(param, digit)
        print("chances to get a " + str(param) + " full of " + str(digit) + ":  " + "%.2f" % answer + "%")
    else:
        raise Exception("Wrong input, watch your numbers\n")

try:
    double = 2
    only = 1
    if len(sys.argv) == (double + double + only + double):
        answer = 0.0
        suite = ""
        d5 = error_handling(sys.argv[(only + double + double)])
        d4 = error_handling(sys.argv[(double + only + only)])  
        d3 = error_handling(sys.argv[(only + double)]) 
        d2 = error_handling(sys.argv[double])
        d1 = error_handling(sys.argv[only])
        make_meth(sys.argv[(double + double + double)])
    else:
        raise Exception("Wrong input, watch your numbers\n")
except Exception as error:
    sys.stdout.write(str(error))
    exit(84)



