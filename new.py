file = open('out')

first_line = file.readline()

print(all(first_line == line for line in file))
