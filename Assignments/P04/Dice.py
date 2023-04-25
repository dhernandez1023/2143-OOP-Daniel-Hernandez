#######################################################################
#                    
#  Author:           Daniel Hernandez
#  Email:            dhernandez1023@my.msutexas.edu
#  Label:            P04
#  Title:            Roll Them Bones!
#  Course:           CMPS 2143
#  Semester:         Spring 2023
# 
#  Description:
#        This program will implement a Die and a Dice class. The Die
#  class will produce a number in the range of the die. The Dice class
#  has various methods that use the Die class to find different
#  values.
# 
#  Files:            
#      main.py
#      Dice.py
#######################################################################
import sys
from rich import print
import random

###
# Die
# 
# Description:
#      This class creates a Die that can be rolled to get
#    a random value within its sides
# 
# Methods:
#    def __init__(self, sides = None)
#    def roll(self)
#    def __str__(self):
#
# Usage: 
#     d1 = Die()
#      
###
class Die(object):
  def __init__(self, sides = None):
    #if !sides
    if not sides:
      self.sides = 6
    else:
      if not isinstance(sides, int):
        print("error: sides is not an integer!")
        sys.exit()
      self.sides = sides

  def roll(self):
    # shuffles the range of the die
    # adds 1 b/c there's no 0 on a die
    values = [x for x in range(self.sides)]
    random.shuffle(values)
    return values[0] + 1

  def __str__(self):
    return f"[sides: {self.sides}]"
    
###
# Dice
# 
# Description:
#      This class creates multiple Die and can find
#  different values of the dice.
# 
# Methods:
#    def __init__(self, sides = None)
#    def __init__(self, diceString)
#    def sum(self)
#    def max(self)
#    def min(self)
#    def avg(self)
#    def roll(self, rollType=None)
#    def __str__(self)
#
# Usage: 
#   d3 = Dice(10, 5)
#   d4 = Dice("8.d.20")
#      
###
class Dice:
  def __init__(self, sides=None, num_dice=1):
    if not sides:
      print("Need to pass in sides!")
      sys.exit()

    self.dice = []
    self.sides = sides
    
    for die in range(num_dice):
      self.dice.append(Die(sides))

  # def __init__(self, diceString):
  #   numDie, filler, numSides = diceString.split('.')
  #   num_dice, sides = int(numDie), int(numSides)
    
  #   self.dice = []
  #   self.sides = sides
    
  #   for die in range(num_dice):
  #     self.dice.append(Die(sides))
    
  def sum(self):
    total = 0
    for d in self.dice:
      total += d.roll()
    return total

  def max(self):
    return max(d.roll() for d in self.dice)
  
  def min(self):
    return min(d.roll() for d in self.dice)
  
  def avg(self):
    return sum(d.roll() for d in self.dice)/len(self.dice)
  
  def roll(self, rollType=None):
    if rollType == 'max':
      return self.max()
    elif rollType == 'min':
      return self.min()
    elif rollType == 'avg':
      return self.avg()
    else:
      return self.sum()
      
  def __str__(self):
    s = "Dice:[\n    "
    for d in self.dice:
      s = s + str(d) # casting a class as a string, invokes the __str__ method!!
    s = s + "\n]\n"
    return s

# dieTester
# 
# Description:
#      Tests a single die and the methods within dice
#  Params:
#      die
#      runs
#      testType

def dieTester(die, runs=10, testType="sum"):
    """Example function to test a die or dice.
    """
    if isinstance(die, Die):
      print(f"Testing {die.sides} sided die for {runs} rolls:")
      print("    [ ", end="")
      for i in range(runs):
          print(die.roll(), end=" ")
    else:
      print(f"Rolling {len(die.dice)} {die.sides} sided die {runs} times to get the {testType} value:")
      print("    [ ", end="")
      for i in range(runs):
        if testType == "avg":
          print(die.avg(), end=" ")
        elif testType == "min":
          print(die.min(), end=" ")
        elif testType == "max":
          print(die.max(), end=" ")
        else:
          print(die.sum(), end=" ")
    print("]")

if __name__ == '__main__':

  d1 = Die()
  d2 = Die(20)
  d3 = Dice(10, 5)
  # d4 = Dice("8.d.20")
  
  dieTester(d1, 10)
  dieTester(d2, 20)
  dieTester(d3, 10, "max")
  dieTester(d3, 10, "min")
  dieTester(d3, 10, "avg")
  # dieTester(d4, 20, "max")