#!/usr/bin/env python      
# -*- coding: utf-8 -*-

import rospy
from beginner_tutorials.msg import Song

def callback(data):
    print ('name:%s',data.name)
    print ('singger:%s',data.singger)
    print ('%s',data.lyrics)
    print ("")

def listener():
    rospy.init_node('listener', anonymous = False)
    sub = rospy.Subscriber("chatter", Song, callback)
    rospy.spin()


if __name__ == '__main__':
    listener()


