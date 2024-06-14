import numpy as np
import threading

class file_utils:
    
    def __init__(self):
        ""
        
        
    def read_inpdata(self, inputfile):
        with open(inputfile, "r") as f:
            data = f.readlines() 
        data = [line for line in data if line.split()]
        datas = np.array([float(line) for line in data])
        print("File reded success!")
        return datas
    
        
    def write_to_file(self, data, outfilename):

        biglength = len(str(float(np.max(data)))) - len(str(float(np.max(data))).split(".")[0])
        datalen = len(data)
        count = 0
        for i in data:
            try:
                with open(outfilename, 'a') as f:
                    f.write(format(i, "."+str(biglength)+"f") + "\n")
            except:
                "error when write file!"
            if count % 50 == 0:
                self.print_progress_bar(count, datalen) 
            count += 1
        f.close()
        print("\n" )
        print("Write file success!")
        
        
    def write_thread(self, data_list, filenames):
    
        threads = []
        
        for filename, data in zip(filenames, data_list):
            thread = threading.Thread(target= self.write_to_file, args=(data, filename))
            threads.append(thread) 
            
        print("Thread started!")    
        for thread in threads:
            thread.start()
            
        for thread in threads:
            thread.join()
            
        print("Thread finished!")
        
    def print_progress_bar(self, progress, total):

        bar_length = 50
        filled_length = int(progress * bar_length / total)
        percent = round(progress * 100 / total, 2)
        
        print("\r%s%% |%s| %s/%s" % (percent, "█" * filled_length, filled_length, bar_length), end="")
        if progress == total:
            print()