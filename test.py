import os
import subprocess
import string
import math
import sys

def command_line(m, n):
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
    init += '\tRobdd *bdd = new Robdd(' + str(n) + ');\n\tbdd->InitVars(' + str(n) + ');\n'

    
    for i in range(1, n+1):
        exp += 'x' + str(i) + ' ';
        init += '\tx' + str(i) + '.robdd = bdd;\n\tx' + str(i)+'.GetIthvar(' + str(i) + ');\n'
    
    ###print exp;
    
    cmd =  'randltl -B -n 1 --tree-size=' + str(m) +' --simplify=0 --boolean-priorities=\'equiv=0\' ' + exp;
    
    output = subprocess.Popen(cmd, stdout = subprocess.PIPE,shell=True).communicate();
    
    res = output[0];
    res = string.replace(res, "->",  ">");
    res = string.replace(res, "xor", "^");
    res = string.replace(res, "\n", "");
    init += '\ts.robdd=bdd;\n\ts=';
    init += res + ';\n\n';
    init += '\tfinish = clock();\n\tduration = (double)(finish - start) / CLOCKS_PER_SEC *1000;\n';
    init += '\tprintf( \"%f ms\\n\", duration);\n';
    init += '\tprintf( \"m=%d n=%d\\n'+res+'\\n\", '+str(m)+','+str(n)+');\n';
    init += '\treturn 0;\n}\n';
    
    return init;

def main():
    t = 0;
    limitm = 3;
    limitn = 3;
    if(sys.argv >= 1):
        limitm = int(sys.argv[1]);
    
    if(sys.argv>=2):
        limitm = int(sys.argv[2]);
   
    retstr = '';

    cplfile = 'compile.sh';
    runfile = 'run.sh';
    cpath = os.getcwd() + '/' + cplfile;
    rpath = os.getcwd() + '/' + runfile;
    if os.path.exists(cpath):
        os.remove(cplfile)
    if os.path.exists(rpath):
        os.remove(runfile)
    
    file_c = open(cplfile, 'w');
    file_r = open(runfile, 'w')

    for j in range(1,limitn):
        for i in range(1,limitm):
            n = pow(7, j);
            m = 10 * i;
            t = t + 1;
        
            print 'n=' + str(n) + ' m=' + str(m);
            ret = command_line(n, m);
            ###print ret;
        
            filename = 'test' + str(t);
            filecpp = filename + '.cpp';
            ###print filecpp;
        
            fpath = os.getcwd() + "/" + filecpp;
            if os.path.exists(fpath):
                os.remove(filecpp);
            if os.path.exists(filename):
                os.remove(filename);
            if os.path.exists(filename+'.o'):
                os.remove(filename+".o");
        
            file_object = open(filecpp, 'w');
            file_object.write(ret);
        
            cplstr = 'g++ -c '+filename+'.cpp -o ' + filename + '.o\n';
            lnkstr = 'g++ '+filename+'.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o ' + filename + '\n'; 
            runstr = './'+filename+'\n';
        
            file_c.write(cplstr);
            file_c.write(lnkstr);
            file_r.write(runstr);
        
            ###print runret[0];
            file_object.close();
    file_c.close();
    file_r.close();

    output = subprocess.Popen('source ./compile.sh', stdout=subprocess.PIPE,shell=True).communicate();
    #output = subprocess.Popen('source ./run.sh', stdout=subprocess.PIPE,shell=True).communicate();
    
if __name__ == "__main__":
    main()