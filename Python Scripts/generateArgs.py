
output=open("output.txt","w")
for i in range(23,74):
	output.write('0 5 4 {}\n'.format(i))
for i in range(15,418):
	output.write('0 5 5 {}\n'.format(i))