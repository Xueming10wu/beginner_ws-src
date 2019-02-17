#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import rospy
from std_msgs.msg import Float32

def gen_number():
    rospy.init_node("random_number_generator", log_level=rospy.INFO , anonymous = True)
    pub = rospy.Publisher("/random_number", Float32, queue_size = 10)
    rospy.loginfo("Generating random numbers")

    loop_rate = rospy.Rate(20)
    while not rospy.is_shutdown():
        pub.publish(Float32( np.random.normal( 5, 1, size=None)))
        #rospy.sleep(0.05)
        loop_rate.sleep()
    
if __name__ == '__main__':
    try:
        gen_number()
    except Exception, e:
        print ("Exception and Done")