import re

def luhn_checksum(card_number):
    def digits_of(n):
        return [int(d) for d in str(n)]
    digits = digits_of(card_number)
    odd_digits = digits[-1::-2]
    even_digits = digits[-2::-2]
    checksum = 0
    checksum += sum(odd_digits)
    for d in even_digits:
        checksum += sum(digits_of(d*2))
    return checksum % 10

def is_luhn_valid(card_number):
    return luhn_checksum(card_number) == 0

ascii_num_pattern = re.compile("[0-9]+")

def is_mastercard(card_number: str):
    start_num = int(card_number[0:2])
    if (start_num >= 51 and start_num <= 55):
        return True
    else:
        start_num = int(card_number[0:4])
        if (start_num >= 2221 and start_num < 2720):
            return True
    return False

def is_american_express(card_number: str):
    return bool(card_number.startswith("34") or card_number.startswith("37"))

def validate(card_number: str):
    """
    Validates whether or not a card_number represents a potentially valid
    credit card number.
    Card numbers must be strings composed of ASCII numbers (0-9) meeting these
    rules:
      - Visa cards: starts with the digit 4, length 16
      - Mastercard: starts with 51-55  and 2221-2720, length 16
      - American Express:  starts with 34 or 37, length 15
      - Number must pass the Luhn checksum
    Args:
    card_number(str): credit card number to validate
    returns:
    True if the card_number is valid, False others
    """

    if ascii_num_pattern.fullmatch(card_number) is None:
        return False
    if not (15 <= len(card_number) <= 16):
        return False

    length = -1
    if card_number.startswith("4") or is_mastercard(card_number):
        length = 16
    elif is_american_express(card_number):
        length = 15

    if length == -1:   # not a valid type
        return False

    if len(card_number) != length:     # card is an invalid length
        return False

    return is_luhn_valid(card_number)

