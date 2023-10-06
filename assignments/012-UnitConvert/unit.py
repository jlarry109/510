def convert_mass(value, current, target):
    """
    This function converts quantities from any of the given units 
    (KILOGRAM, POUND, STONE, JIN, SEER, GRAM, OKA) to another.
    The function takes in the "value" of the quantity, its "current" unit,
    and the "target" unit of conversion. It returns the value of the mass in the target unit.
    """
    # if current equals target, no conversion needed
    if current == target:
        return value
    # A dictionary for mass unit conversions
    mass_units = {
        'KILOGRAM': 1.0,
        'POUND': 0.453592,
        'STONE': 6.35029,
        'JIN': 0.5,
        'SEER': 1.25,
        'GRAM': 0.001,
        'OKA': 1.2829
    }
    # Check if current and target units are in the dictionary
    if current.upper() in mass_units and target.upper() in mass_units:
        # Convert the value to kilograms ( could exclude this if curr is already in Kg 
        # but I'll just leave it)
        temp_kg = value * mass_units[current.upper()]
        # Convert to the target unit
        target_value = temp_kg / mass_units[target.upper()]

        return target_value
    else:
        return "Invalid units"
    