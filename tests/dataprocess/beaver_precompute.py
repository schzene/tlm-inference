import numpy as np
import random
import file_utils
import threading

'''
This function generate the beaver triple 
    Z_a, Z_b
    U_a, U_b
    V_a, V_b
'''


def gen_beaver(inputdata):

    u = []
    v = []
    z = []

    u_A = []
    u_B = []
    
    v_A = []
    v_B = []
    for i in inputdata:
        if i > 0:
            ran_u_a = random.uniform(0, inputdata)
            ran_v_a = random.uniform(0, inputdata)
            ran_u_b = random.uniform(0, inputdata)
            ran_v_b = random.uniform(0, inputdata)
            u_B.append(ran_u_b)
            v_B.append(ran_v_b)
            
            u_A.append(ran_u_a)
            v_A.append(ran_v_a)
            
            u.append(ran_u_a + ran_u_b)
            v.append(ran_v_a + ran_v_b)
        else:
            ran_u_a = random.uniform(inputdata, 0)
            ran_v_a = random.uniform(inputdata, 0)
            ran_u_b = random.uniform(inputdata, 0)
            ran_v_b = random.uniform(inputdata, 0)

            u_B.append(ran_u_b)
            v_B.append(ran_v_b)
            
            u_A.append(ran_u_a)
            v_A.append(ran_v_a)
            
            u.append(ran_u_a + ran_u_b)
            v.append(ran_v_a + ran_v_b)
            
    z = np.multiply(u, v)
    z_A = []
    z_B = []
    for j in z:
        if j > 0:
            ran = random.uniform(0, z)
            z_B.append(ran)
            z_A.append(j - ran)
        else:
            ran = random.uniform(z, 0)
            z_B.append(ran) 
            z_A.append(j - ran)
    
    Z_A = np.array([float(line) for line in z_A])
    Z_B = np.array([float(line) for line in z_B])
    U_A = np.array([float(line) for line in u_A])
    U_B = np.array([float(line) for line in u_B])
    V_A = np.array([float(line) for line in v_A])
    V_B = np.array([float(line) for line in v_B])
    
    print("Beaver generated success!")
    return Z_A, Z_B, U_A, U_B, V_A, V_B



def main():
    fileutils = file_utils.file_utils()
    
    file = "../test_ring_beaver.inp"

    data = fileutils.read_inpdata(file)
    
    Z_A, Z_B, U_A, U_B, V_A, V_B =gen_beaver(data)
    
    data_lists = [Z_A, Z_B, U_A, U_B, V_A, V_B]
    
    filenames = ["data/beaver_Z_A.inp", "data/beaver_Z_B.inp", "data/beaver_U_A.inp", "data/beaver_U_B.inp", "data/beaver_V_A.inp","beaver_V_B.inp"]

    fileutils.write_thread(data_list=data_lists, filenames= filenames)


if __name__ == "__main__":
    main()
