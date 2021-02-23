import numpy as np
import re
import csv
import glob

if __name__ == '__main__':
    for i in glob.glob("*.txt"):
        times=[]
        time_info = open(i,"r")
        count=0
        num=0
        temp=[]
        for line in time_info:
            match=re.search("\d+\.\d+",line)
            if match:
                temp.append((match.group()))
                count+=1
            if(count==7):
                count=0
                num+=1
                times.append(temp)
                temp=[]
        with open(i[0:-4]+'.csv', mode='w') as time_file:
            time_write = csv.writer(time_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
            for i in range(7):
                row=[]
                for j in range(num):
                    row.append(times[j][i])
                time_write.writerow(row)
                      
