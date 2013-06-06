import os
import subprocess
import string

def command_line(m, n):
    exp = '';
    init = '';
    
    init += '#include \"robdd.h\"\n';
    init += '#include \"bdd.h\"\n';
    init += '#include <stdio.h>\n';
    init += '#include <string.h>\n';
    init += 'int main()\n{\n';
    init += '\tfloat duration;\n';
    init += '\tclock_t start, finish;\n\tstart = clock();\n\n';
    init += '\tbdd ';
    
    for i in range(1, n+1):
        init += 'x'+str(i) + ','
    
    init += 's;\n'
    init += '\tRobdd *bdd = new Robdd('+str(n)+');\n\tbdd->InitVars('+str(n)+');\n'

    
    for i in range(1, n+1):
        exp += 'x'+ str(i)+' ';
        init += '\tx' + str(i) + '.robdd = bdd;\n\tx'+str(i)+'.GetIthvar('+str(i)+');\n'
    
#    print exp;
    
    cmd =  'randltl -B -n 1 --tree-size='+ str(m) +' --boolean-priorities=\'equiv=0\' ' + exp;
    
    output = subprocess.Popen(cmd, stdout=subprocess.PIPE,shell=True).communicate();
    
    res = output[0];
    res = string.replace(res, "->",  ">");
    res = string.replace(res, "xor", "^");
    res = string.replace(res, "\n", "");
#    print res;
    init += '\ts.robdd=bdd;\n\ts=';
    init += res + ';\n\n';
    init += '\tfinish = clock();\n\tduration = (double)(finish - start) / CLOCKS_PER_SEC *1000;\n';
    init += '\tprintf( \"%f ms\\n\", duration);\n\treturn 0;\n}\n';
    print init;


command_line(30, 4);