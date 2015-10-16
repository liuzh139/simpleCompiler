from subprocess import call
import os

files = ["tests/" + f for f in os.listdir('tests') if os.path.isfile("tests/" + f) and f.endswith(".lang")]

for f in files:
    newf = f + ".s"
    assembly = call("./lang < " + f + " > " + newf, shell=True)
    if not (assembly == 0):
        call("rm -f " + newf, shell=True)
        continue
    compiled = call("gcc -m32 -o tests/exec tester.c " + newf, shell=True)
    call("rm " + newf, shell=True)
    if not (compiled == 0):
        continue
    call("echo " + f + ":", shell=True)
    call("tests/exec", shell=True)
    call("rm tests/exec", shell=True)
