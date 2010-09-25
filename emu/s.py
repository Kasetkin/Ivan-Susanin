# -*- coding: utf-8 -*-
robo.set_speed(5, 5)
while (robo.ray_distance(1, 0, 0) > 20):
  pass
robo.set_speed(0, 0)

while (1):
  if (robo.ray_distance(1, 0, 0) < 20):
    robo.set_speed(1,0)
    while (robo.ray_distance(1, 0, 0) < 20):
      pass
  robo.set_speed(5, 5)
  while (robo.ray_distance(1, 0, 0) > 20 and robo.ray_distance(0, 0, 1) < 60):
    pass
  robo.set_speed(0, 0)
  if (robo.ray_distance(0, 0, 1) > 60):
    robo.set_speed(0, 1)
    while (robo.ray_distance(1, 0, 0) >= 60):
      pass
    robo.set_speed(0, 0)
  