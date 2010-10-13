# -*- coding: utf-8 -*-
import math

dx = 300
dz = 0



rad = 40


def finish():
    d = robo.destination(dx, 0, dz)
    return (d.x() * d.x() + d.z() * d.z()) <= rad

def d_angle():
   d = robo.destination(dx, 0, dz)
   return math.acos(d.x() / math.sqrt(d.x() * d.x() + d.z() * d.z()))

def target_dst():
  d = robo.destination(dx, 0, dz)
  return d.x() * d.x() + d.z() * d.z()

def rotate_target():
    robo.set_speed(0, 0.1)
    while(abs(d_angle()) >= 3.14 * 2 / 180):
      pass
    robo.set_speed(0, 0)

def rotate_wall():
    robo.set_speed(0, 0.1)
    while (not (robo.ray_distance(1,0,0) >= rad and robo.ray_distance(1,0,1) >= rad and robo.ray_distance(1,0,-1) >= rad and robo.ray_distance(0,0,1) <= 2 * rad)):
      pass
    robo.set_speed(0, 0)

def go_to_wall():
    robo.set_speed(1, 1)
    while (robo.ray_distance(1,0,0) >= rad and robo.ray_distance(1,0,1) >= rad and robo.ray_distance(1,0,-1) >= rad and not finish()):
      pass
    robo.set_speed(0, 0)

def go_near_wall():
    robo.set_speed(1, 1)
    while (robo.ray_distance(1,0,0) >= rad and robo.ray_distance(1,0,1) >= rad and robo.ray_distance(1,0,-1) >= rad and not finish() and robo.ray_distance(0,0,1) <= 2 * rad):
      pass
    robo.set_speed(0, 0)


last_dst = -1

rotate_target()
go_to_wall()

while(1):
    print "next step"
    if (finish()):
      print "finish"
      break
    if (last_dst >= 0):
        if (target_dst() < last_dst):
            print "going to target"
            last_dst = -1
            rotate_target()
            go_to_wall()
        else:
            print "continue going near wall"
            rotate_wall()
            go_near_wall()
    else:
        print "start going near wall"
        last_dst = target_dst()
        rotate_wall()
        go_near_wall()

