def power_helper(base, exponent):
  if (exponent == 0):
    return 1
  
  return base * power_helper(base, exponent - 1)

def power( x,  y):
  return power_helper(x, y)

