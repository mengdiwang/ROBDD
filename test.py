import os
import subprocess
import string
import math
import sys

initsize = '10000';
cachsize = '100';

def randFomula(m, n):
    exp = '';
    for i in range(1, n+1):
        exp += 'x' + str(i) + ' ';
    
    cmd =  'randltl -B -n 1 --tree-size=' + str(m) +' --boolean-priorities=\'equiv=0\' ' + exp;
    output = subprocess.Popen(cmd, stdout = subprocess.PIPE,shell=True).communicate();
    res = output[0];
    res = string.replace(res, "->",  ">");
    res = string.replace(res, "xor", "^");
    res = string.replace(res, "\n", "");
    return res;

def robddGen(m, n, formula):
    exp = '';
    init = '';

    init += '#include \"../robdd.h\"\n';
    init += '#include \"../bdd.h\"\n';
    init += '#include <stdio.h>\n';
    init += '#include <string.h>\n';
    init += 'int main()\n{\n';
    init += '\tfloat duration;\n';
    init += '\tclock_t start, finish;\n\tstart = clock();\n\n';
    init += '\tbdd ';
    
    for i in range(1, n+1):
        init += 'x' + str(i) + ','
    
    init += 's;\n'
#    init += '\tRobdd *bdd = new Robdd(' + str(n) + ');\n';
    init += '\tRobdd *bdd = new Robdd(' + initsize + ',' + cachsize + ');\n';
    init += '\tbdd->InitVars(' + str(n) + ');\n';

    
    for i in range(1, n+1):
#        exp += 'x' + str(i) + ' ';
        init += '\tx' + str(i) + '.robdd = bdd;\n\tx' + str(i)+'.GetIthvar(' + str(i) + ');\n'

    
    init += '\ts.robdd=bdd;\n\ts=';
    init += formula + ';\n\n';
    init += '\tfinish = clock();\n\tduration = (double)(finish - start) / CLOCKS_PER_SEC *1000;\n';
    init += '\tprintf( \"m=%d,n=%d,' + formula + '\\n\", '+str(m)+','+str(n)+');\n';
    init += '\tprintf( \"%f ms\\n\", duration);\n';
    init += '\treturn 0;\n}\n';
    
    return init;
def buddyGen(m, n, formula):
    exp = '';
    init = '';
    
    init += '#include <bdd.h>\n';
    init += '#include <stdio.h>\n';
    init += '#include <string.h>\n';
    init += 'int main()\n{\n';
    init += '\tfloat duration;\n';
    init += '\tclock_t start, finish;\n\tstart = clock();\n\n';
    init += '\tbdd ';
    
    for i in range(1, n+1):
        init += 'x' + str(i) + ','
    init += 's;\n'
    
    init += '\tbdd_init(' + initsize + ',' + cachsize + ');\n'
    init += '\tbdd_setvarnum(' + str(n) + ');\n'
    
    for i in range(1, n+1):
#        exp += 'x' + str(i) + ' ';
        init += '\tx' + str(i) + ' = bdd_ithvar(' + str(i-1) + ');\n'
    
    init += '\ts=' + formula + ';\n\n';
    init += '\tfinish = clock();\n\tduration = (double)(finish - start) / CLOCKS_PER_SEC *1000;\n';
    init += '\tprintf( \"m=%d,n=%d,' + formula + '\\n\", '+str(m)+','+str(n)+');\n';
    init += '\tprintf( \"%f ms\\n\", duration);\n';
    init += '\treturn 0;\n}\n';
    
    return init;

def main():
    t = 0;
    stepm = 15;
    stepn = 20;
    limitm = 3;
    limitn = 3;
    if len(sys.argv)<3:
        sys.exit('Usage: %s m n' % sys.argv[0])
        
    if(sys.argv >= 2):
        limitm = int(sys.argv[1]);
    
    if(sys.argv >= 3):
        limitn = int(sys.argv[2]);
   
    retstr = '';

    cplfile = 'compile.sh';
    runfile = 'run.sh';
    runfile2 = 'run_bdd.sh';
    clrfile = 'clear.sh'
    
    cpath = os.getcwd() + '/' + cplfile;
    rpath = os.getcwd() + '/' + runfile;
    rpath2 = os.getcwd() + '/' + runfile2;
    cpath = os.getcwd() + '/' + clrfile;
    
    if os.path.exists(cpath):
        os.remove(cplfile)
    if os.path.exists(rpath):
        os.remove(runfile)
    if os.path.exists(rpath2):
        os.remove(runfile2)
    if os.path.exists(cpath):
        os.remove(clrfile)
    
    file_c = open(cplfile, 'w');
    file_r = open(runfile, 'w')
    file_r2 = open(runfile2, 'w')
    file_clr = open(clrfile, 'w')
    file_clr.write('rm *.o\nrm *.cpp\n');
    file_clr.write('rm *.o\nrm *.cpp\n');
    
    for j in range(1,limitn):
        for i in range(1,limitm):
            m = stepm * i;
            n = stepn * j;
            t = t + 1;
        
            print 'm=' + str(m) + ' n=' + str(n);
            
            formula = randFomula(m, n)
            ret = robddGen(m, n, formula);
            #New File Test_t.cpp, write string into file        
            filename = 'test' + str(t);
            filecpp = filename + '.cpp';
            fpath = os.getcwd() + "/" + filecpp;
            #if os.path.exists(fpath):
            #    os.remove(filecpp);
            #if os.path.exists(filename):
            #    os.remove(filename);
            #if os.path.exists(filename+'.o'):
            #    os.remove(filename+".o");
            file_object = open(filecpp, 'w');
            file_object.write(ret);
            
            #Generate compile and link script
            cplstr = 'g++ -c '+filename+'.cpp -o ' + filename + '.o\n';
            lnkstr = 'g++ '+filename+'.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o ' + filename + '\n'; 
            runstr = './'+filename+'\n';
            clrstr = 'rm '+filename+'\n';
            
            file_c.write(cplstr);
            file_c.write(lnkstr);
            file_r.write(runstr);
            file_clr.write(clrstr);
        
            ############# BDD GENERATION ##################
            ret = buddyGen(m, n, formula);
            filename = 'bddtest' + str(t);
            filecpp = filename + '.cpp';
            fpath = os.getcwd() + "/" + filecpp;
            #if os.path.exists(fpath):
            #    os.remove(filecpp);
            #if os.path.exists(filename):
            #    os.remove(filename);
            #if os.path.exists(filename+'.o'):
            #    os.remove(filename+".o");
            file_object = open(filecpp, 'w');
            file_object.write(ret);
            
            cplstr = 'g++ '+filename+'.cpp -o ' + filename + ' -lbdd\n';
            runstr = './'+filename+'\n';
            clrstr = 'rm '+filename+'\n';
            
            file_c.write(cplstr);
            file_r2.write(runstr);
            file_clr.write(clrstr);
            
            ###print runret[0];
            file_object.close();
    file_c.close();
    file_r.close();
    file_r2.close();
    file_clr.close();

    output = subprocess.Popen('source ./compile.sh', stdout=subprocess.PIPE,shell=True).communicate();
    #output = subprocess.Popen('source ./run.sh', stdout=subprocess.PIPE,shell=True).communicate();
    
if __name__ == "__main__":
    main()