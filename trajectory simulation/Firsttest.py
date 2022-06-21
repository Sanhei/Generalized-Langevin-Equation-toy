#!/usr/bin/env python
# coding: utf-8

# In[5]:

import time
import math
import numpy as np
import matplotlib.pyplot as plt
import random
class DBEular():
    def __init__(self, tau_D, tau_m, gamma, tau, h):
        self.tau_D = tau_D
        self.tau_m = tau_m
        self.tau   = tau
        self.gamma = gamma
        self.h     = h
        return
    def potential(self, x):
        U0 = 3
        return -U0*(4*math.pow(x, 3)-4*x)
    
    def xupdate(self, x, xp, y):
        return  2*x - xp + self.tau_D/self.tau_m*self.potential(x)*self.h**2+ self.tau_D**2/self.tau_m/self.tau*(y-x)*self.h**2

    def yupdata(self, y,  x):
        return y-self.tau_D*(y-x)*self.h/self.tau + math.sqrt(2*self.h)*random.gauss(0.0, 1.0)
    
    
    
    
    def run(self):
        temp = 0.0
        x = -1
        xp = -1
        y = 0

        t_list = []
        x_list = []
        st = time.time()
        with open('traj.npy', 'w') as my_file:
            for i in range(150000000):
                temp = x
                x = self.xupdate(x, xp, y)
                y = self.yupdata(y, temp)
                xp = temp
                np.savetxt(my_file,[x])
        et = time.time()
        elapsed_time = et - st
        print('Execution time:', elapsed_time, 'seconds')
        
        return 0


# In[6]:


tau_D, tau_m, gamma, tau, h = [50, 0.02, 10, 25, 0.0001]
test = DBEular(tau_D, tau_m, gamma, tau, h)
test.run()

