import os
import subprocess
import string
import math
import sys

def main():

    output = subprocess.Popen('source ./run.sh', stdout=subprocess.PIPE,shell=True).communicate();
    collection = output[0].split('\n');
    
    t = 0;
    for st in collection:
        #if(t%3==0):   
        print st;
        
    output = subprocess.Popen('source ./run_bdd.sh', stdout=subprocess.PIPE,shell=True).communicate();
    collectionbdd = output[0].split('\n');
    
    t = 0;
    for st in collectionbdd:
        #if(t%3==0):   
        print st;
        
    print '[robdd] vs [buddy]';
    print '----------------------------------------------'
    for idx in range(len(collection)):
        if(idx % 2 == 1):
            print '[robdd]:' + collection[idx] + ' vs [buddy]:' + collectionbdd[idx];
            print '----------------------------------------------'
        else:
            print collection[idx];
            print '';
    print '[scale] [robdd] [buddy]'
    for idx in range(len(collection)):
        if(idx % 2 == 1):
            print collection[idx][:-3] + ' ' +collectionbdd[idx][:-3];
        else:
            pos = collection[idx].rfind(',')
            rpos = len(collection[idx])-pos;
            sys.stdout.write(collection[idx][:-rpos] + ' ')
            
    
if __name__ == "__main__":
    main()