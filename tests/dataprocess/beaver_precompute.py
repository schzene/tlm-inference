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

def generate_z(i):
    pass
def generate_u(i):
    pass
def gemerate_v(i):
    pass

def gen_beaver(inputdata):
    inputdata = np.array(inputdata)
    u_A = np.zeros_like(inputdata)
    v_A = np.zeros_like(inputdata)
    u_B = np.zeros_like(inputdata)
    v_B = np.zeros_like(inputdata)
    z_A = np.zeros_like(inputdata)
    z_B = np.zeros_like(inputdata)
    
    iters = 0
    for i in inputdata:

        if i > 0:
            u_A[iters] = random.uniform(0, i)
            v_A[iters] = random.uniform(0, i)
            u_B[iters] = random.uniform(0, i)
            v_B[iters] = random.uniform(0, i)
            
            z_A[iters] = (u_A[iters] * v_A[iters])  +  (u_A[iters] *v_B[iters])
            z_B[iters] = (u_B[iters] * v_A[iters])  +  (u_B[iters] *v_B[iters])

        else:
            
            u_A[iters] = np.random.uniform(i, 0)
            v_A[iters] = np.random.uniform(i, 0)
            u_B[iters] = np.random.uniform(i, 0)
            v_B[iters] = np.random.uniform(i, 0)
            
            z_A[iters] = (u_A[iters] * v_A[iters])  +  (u_A[iters] *v_B[iters])
            z_B[iters] = (u_B[iters] * v_A[iters])  +  (u_B[iters] *v_B[iters])
        iters = iters+1 
    print("Beaver generated success!")
    return z_A, z_B, u_A, u_B, v_A, v_B



def main():
    fileutils = file_utils.file_utils()
    
    file = "test_ring_beaver.inp"

    data = fileutils.read_inpdata(file)
    

    Z_A, Z_B, U_A, U_B, V_A, V_B =gen_beaver(data)
    
    data_lists = [Z_A, Z_B, U_A, U_B, V_A, V_B]
    
    filenames = ["data/beaver_z_A.inp", "data/beaver_z_B.inp", "data/beaver_u_A.inp", "data/beaver_u_B.inp", "data/beaver_v_A.inp","beaver_v_B.inp"]

    fileutils.write_thread(data_list=data_lists, filenames= filenames)


if __name__ == "__main__":
    main()
