#!/usr/bin/env python      
# -*- coding: utf-8 -*-

import rospy
from beginner_tutorials.msg import Song

def talker():
    rospy.init_node('talker', anonymous = False )
    pub = rospy.Publisher("chatter", Song, queue_size=10)

    lyrics = ['A','AB','ABC']
    count = 0

    msg = Song()
    msg.name = 'HJ'
    msg.singger = 'JL'

    loop_rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        msg.lyrics = lyrics[count % 3]
        count += 1
        pub.publish(msg)
        loop_rate.sleep()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass