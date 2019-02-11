#!/usr/bin/env python      
# -*- coding: utf-8 -*-

import sys
import rospy
from beginner_tutorials.srv import addTwoInt,addTwoIntRequest,addTwoIntResponse

def add_two_ints_client(x, y):
    rospy.wait_for_service('add_two_ints')
    try:
        add_two_ints = rospy.ServiceProxy('add_two_ints', addTwoInt)
        #此处使用的是委托服务
        res = add_two_ints(x, y)
        return res
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def usage():
    return "%s [x y]" % sys.argv[0]

if __name__ == '__main__':
    rospy.init_node("addTwoInt_client", anonymous=True)
    
    if len(sys.argv) == 3:
        x = int(sys.argv[1])
        y = int(sys.argv[2])
    else:
        print usage()
        sys.exit(1)

    print "Requesting %s %s"%(x, y)
    r = add_two_ints_client(x, y)
    print ("sum:%d", r.sum)
    print ("mul:%d", r.mul)
