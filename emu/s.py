# -*- coding: utf-8 -*-
print "file"
print robo.ray_distance(0, 0, 1)
robo.set_speed(10, 10)
while (robo.ray_distance(0, 0, 1) < 1) or (robo.ray_distance(0, 0, 1) > 10):
  print "go", robo.ray_distance(0, 0, 1)
#robo.set_speed(0, 0)

