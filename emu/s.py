# -*- coding: utf-8 -*-

robo.set_speed(1, 1)

rad = 40

while (1):
  if (robo.ray_distance(1, 0, 0) <= rad or robo.ray_distance(1, 0, 1) <= rad or robo.ray_distance(1, 0, 1) <= rad):
      robo.set_speed(-1, 1)
      while (robo.ray_distance(1, 0, 0) <= 2 * rad or robo.ray_distance(1, 0, 1) <= 2 * rad or robo.ray_distance(1, 0, 1) <= 2 * rad):
        pass
      robo.set_speed(1, 1)


  

