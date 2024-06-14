import numpy as np
import random
import math
import file_utils


def input2secret(data):
    randomdata = []
    subdata = []
    for i in range(len(data)):
        if data[i] > 0.:
            randomdata.append(random.uniform(0, data[i]))
            subdata.append(data[i] - randomdata[i])

        else:
            randomdata.append(random.uniform(data[i], 0))
            subdata.append(data[i] - randomdata[i])
        
    imput_a = np.array([float(line) for line in subdata])
    imput_b = np.array([float(line) for line in randomdata])
    
    return imput_a, imput_b   


def main():
    fileutils = file_utils.file_utils()
    
    file = "test_ring_beaver.inp"
    inputdata = fileutils.read_inpdata(file)

    x_a, x_b = input2secret(inputdata)
    
    data_lists = [x_a, x_b ]
    
    filenames = ["data/input_x_A.inp", "data/input_x_B.inp"]
    
    fileutils.write_thread(data_lists, filenames)

    print("input to secret shre sucess")


if __name__ == "__main__":
    main()