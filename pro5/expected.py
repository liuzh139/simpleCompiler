from subprocess import call
import os

files = ["tests/" + f for f in os.listdir('tests') if os.path.isfile("tests/" + f) and f.endswith(".lang")]

for f in files:
    newf = f + ".c"
    intro = "\"#include <stdio.h>\nint main() {\n\""
    call("echo " + intro + " > " + newf, shell=True)
    command = "egrep \"(^int.*)|(.*=.*)|(return.*)\" " + f + " | sed \"s/return \\(.*\\)/printf(\\\"%d\\\",\\1)/g\" | sed \"s/$/;/g\" >> " + newf
    call(command, shell=True)
    end = "\"return 0;\n}\n\""
    call("echo " + end + " >> " + newf, shell=True)
    call("gcc -o tests/refexec " + newf, shell=True)
    call("rm " + newf, shell=True)
    call("echo " + f + ":", shell=True)
    call("tests/refexec", shell=True)
    call("rm tests/refexec", shell=True)
    call("echo", shell=True)
