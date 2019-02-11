#!/usr/bin/env python      
# -*- coding: utf-8 -*-

import rospy
from beginner_tutorials.srv import addTwoInt,addTwoIntRequest,addTwoIntResponse

def serverFunction(req):
    res = addTwoIntResponse()
    res.sum = req.a + req.b
    res.mul = req.a * req.b
    return res


def main():
    rospy.init_node("addTwoInt_server", anonymous = False)
    server = rospy.Service("add_two_ints",addTwoInt, serverFunction )
    rospy.spin()

if __name__ == '__main__':
    main()
