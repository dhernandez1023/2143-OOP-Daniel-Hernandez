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
from Dice import Die, Dice, dieTester

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