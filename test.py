import os
import subprocess
def command_line():
    os.system('randltl -B -n 2 --tree-size=100 --boolean-priorities=\'equiv=0 \' x1 x2 x3');

command_line();