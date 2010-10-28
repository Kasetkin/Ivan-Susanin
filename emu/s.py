# -*- coding: utf-8 -*-
import math

world = grid(1000, 40)

rx = 0
rz = 300

dx = 0
dy = 0

def get_pos():
  x = robo.destination(rx, 0, rz).x()
  y = robo.destination(rx, 0, rz).z()
  
  return x, y

def rotate_to(x, y):
    pass

def go_to(x, y):
    return 0

fail = 0
while (1):
  mx = -robo.destination(rx, 0, rz).x()
  my = -robo.destination(rx, 0, rz).z()
  print "FROM", mx, my, " TO ", 0, 0
  path = world.make_path(mx, my, 0, 0)
  print "NEW PATH"
  for node in path:
    print node.first, node.second
    if (not go_to(node.first, node.second)):
      fail = 1
      break
  if (fail):
    break
    