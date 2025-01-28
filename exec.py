import sys

def readFile(filename):
   "Read input file"
   linesList = list(open(filename, 'r').read().splitlines())
   instances = []
   for i in range(len(linesList)):
      instance_str = linesList[i].split(' ')
      instance_int = [ int(instance_str[j]) for j in range(len(instance_str)) ]
      instances.append(instance_int)
   return instances


def check(instance):
   if len(instance) < 3:
      return False
   return True

def solve(instance):
   if not check(instance):
      return -1

   k = instance[0]
   cards = instance[1:]

   diff = []
   for i in range(len(cards)):
      for j in range(i + 1, len(cards)):
         if i == j:
            continue
         else:
            diff.append(abs(cards[i] - cards[j]))

   diff.sort()
   return diff[k - 1]


def writeResult(filename, solutions):
   "Write output file"
   file = open(filename, 'w', encoding = 'UTF-8')
   for i in range(len(solutions)):
      if i > 0:
         file.write('\r\n')
      file.write(str(solutions[i]))
   file.close()


if __name__ == '__main__':

   # Command line
   if len(sys.argv) == 1:
      infilename = 'input.txt'
      outfilename = 'output.txt'
   elif len(sys.argv) == 3:
      infilename = sys.argv[1]
      outfilename = sys.argv[2]
   else:
      print("Usage: python3 exec.py [<inputfile> <outputfile>]")
      assert False

   # Read input file
   instances = readFile(infilename)

   # Execute
   solutions = [ solve(instance) for instance in instances ]

   # Output result
   writeResult(outfilename, solutions)