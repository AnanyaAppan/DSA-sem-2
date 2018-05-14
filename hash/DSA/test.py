# reading input

strings = []
lengths = []

fname = 'small_input1'

with open(fname, 'r') as f:
	text = f.read().split()
	
	for line in text:
		strings.append(line)
		lengths.append(len(line))

n = len(strings)

# TODO write YOUR code here
# n is the total number of strings
# strings[i] is the i'th string
# lengths[i] is the length of the i'th string
