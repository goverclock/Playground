#!env python3
from name_func import get_formatted_name

while True:
    first = input('first?')
    last = input('last?')

    formatted = get_formatted_name(first, last)
    print(f"you are {formatted}")
